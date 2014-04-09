#include"Vote.h"

double getAngle(const Vec3d &v1,const Vec3d &v2)
{
	double d=v1.dot(v2)/norm(v1)/norm(v2);
	if(d>1.0) d=1.0;
	if(d<-1.0) d=-1.0;
	return acos(d);
}

StickVote::StickVote(const Vec3d &p)
{
	position=p;
	for(int i=0;i<3;i++)
		direction[i]=0;
}

void TensorVote::InitialTensor()
{
	tensorsum=Matx33d::zeros();
	Matx33d lamda=Matx33d::zeros();
	for(int i=0;i<3;i++)
		lamda(i,i)=eigenValues[i];
	tensor=eigenVectors*lamda*eigenVectors.t();
}

void TensorVote::InitialBall()
{
	for(int i=0;i<3;i++)
		eigenValues[i]=1;
	for(int i=0;i<2;i++)
		saliency[i]=eigenValues[i]-eigenValues[i+1];
	saliency[2]=eigenValues[2];
	eigenVectors=Matx33d::eye();
}

void TensorVote::InitialStick(const Vec3d &normal)
{
	Vec3d N=normal/norm(normal);
	Vec3d Y(N[1],-N[0],0.0);
	Y=Y/norm(Y);
	Vec3d Z=N.cross(Y);
	Z=Z/norm(Z);
	eigenValues[0]=1;eigenValues[1]=0;eigenValues[2]=0;
	for(int i=0;i<2;i++)
		saliency[i]=eigenValues[i]-eigenValues[i+1];
	saliency[2]=eigenValues[2];
	for(int i=0;i<3;i++)
	{
		eigenVectors(i,0)=N[i];
		eigenVectors(i,1)=Y[i];
		eigenVectors(i,2)=Z[i];
	}
	direction=N;
}

void TensorVote::InitialStick()
{
	eigenValues[0]=1;eigenValues[1]=0;eigenValues[2]=0;
	for(int i=0;i<2;i++)
		saliency[i]=eigenValues[i]-eigenValues[i+1];
	saliency[2]=eigenValues[2];
	eigenVectors=Matx33d::eye();
	direction[0]=1;direction[1]=0;direction[2]=0;
}

void TensorVote::InitialPlate(const Vec3d &tangent)
{
	Vec3d T=tangent/norm(tangent);
	Vec3d X(T[1],-T[0],0.0);
	X=X/norm(X);
	Vec3d Y=T.cross(X);
	Y=Y/norm(Y);
	eigenValues[0]=1;eigenValues[1]=1;eigenValues[2]=0;
	for(int i=0;i<2;i++)
		saliency[i]=eigenValues[i]-eigenValues[i+1];
	saliency[2]=eigenValues[2];
	for(int i=0;i<3;i++)
	{
		eigenVectors(i,0)=X[i];
		eigenVectors(i,1)=Y[i];
		eigenVectors(i,2)=T[i];
	}
}

void TensorVote::InitialPlate()
{
	eigenValues[0]=1;eigenValues[1]=1;eigenValues[2]=0;
	for(int i=0;i<2;i++)
		saliency[i]=eigenValues[i]-eigenValues[i+1];
	saliency[2]=eigenValues[2];
	eigenVectors=Matx33d::eye();
}

TensorVote::TensorVote(const Vec3d &p):StickVote(p)
{
	InitialBall();
	InitialTensor();
}

TensorVote::TensorVote(const Vec3d &p,Type type,const Vec3d &normal):StickVote(p)
{
	if(type==STICK)
		InitialStick(normal);
	else if(type==PLATE)
		InitialPlate(normal);
	else
		InitialBall();
	InitialTensor();
}

TensorVote::TensorVote(const Vec3d &p,Type type):StickVote(p)
{
	if(type==STICK)
		InitialStick();
	else if(type==PLATE)
		InitialPlate();
	else
		InitialBall();
	InitialTensor();
}

void TensorVote::Combine(const StickVote &sv,double weight)
{
	tensorsum+=weight*(Matx31d(sv.direction)*Matx31d(sv.direction).t());
}

StickVote TensorVote::genStickVote(const TensorVote &voter,double sigma,double c)
{
	Vec3d v=position-voter.position;
	double angle=getAngle(voter.direction,v);
	StickVote sv(position);
	if(angle<CV_PI/4.0||angle>CV_PI/4.0*3.0)
		return sv;
	if(abs(angle-CV_PI/2)<0.00001||position==voter.position)
	{
		sv.direction=voter.direction;
		double arc=norm(v);
		double l=exp(-arc*arc/sigma/sigma);
		sv.direction=sv.direction/norm(sv.direction)*l;
		return sv;
	}
	double r=v.dot(v)/2.0/v.dot(voter.direction);
	Vec3d center=voter.position+r*voter.direction;
	sv.direction=center-position;
	double arcangle=getAngle(sv.direction,voter.direction);
	if(arcangle>CV_PI/2.0)
		arcangle=CV_PI-arcangle;
	double arc=arcangle*r;
	double curva=1.0/r;
	double l=exp(-(arc*arc+c*curva*curva)/sigma/sigma);
	sv.direction=sv.direction/norm(sv.direction)*l;
	return sv;
}

void TensorVote::genTensorVote(const TensorVote &voter,double sigma,double c
				,const vector<Vec3d> &sphereSamples,const vector<Vec3d> &circleSamples)
{
	Vec3d r=position-voter.position;
	if(norm(r)>3*sigma)
		return;
	if(voter.saliency[0]>0)
	{
		StickVote vecVote=genStickVote(voter,sigma,c);
		Combine(vecVote,voter.saliency[0]);
	}
	TensorVote transformVoter=voter;
	if(voter.saliency[1]>0)
	{
		int ns=circleSamples.size();
		for(int i=0;i<ns;i++)
		{
			transformVoter.direction=eigenVectors*circleSamples[i];
			StickVote vecVote=genStickVote(transformVoter,sigma,c);
			Combine(vecVote,voter.saliency[1]);
		}
	}
	if(voter.saliency[2]>0)
	{
		int ns=sphereSamples.size();
		for(int i=0;i<ns;i++)
		{
			transformVoter.direction=sphereSamples[i];
			StickVote vecVote=genStickVote(transformVoter,sigma,c);
			Combine(vecVote,voter.saliency[2]);
		}
	}
}

void TensorVote::CloseFormVote(const TensorVote &voter,double sigma)
{
	Vec3d r=position-voter.position;
	if(norm(r)>3*sigma)
		return;
	double c=exp(-r.dot(r)/sigma);
	r=r/norm(r);
	Matx31d rij=Matx31d(r);
	Matx33d R=Matx33d::eye()-2*(rij*rij.t());
	Matx33d Rp=(Matx33d::eye()-0.5*(rij*rij.t()))*R;
	tensorsum+=c*(R*tensor*Rp);
}

double TensorVote::Interpretation(vector<Vec3d> &eigens)
{
	Mat Ev;
	vector<double> E;
	eigen(Mat(tensorsum),E,Ev);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			eigens[i][j]=E[i]*Ev.at<double>(i,j);
	double sum=0;
	for(int i=0;i<3;i++)
		sum+=E[i]*E[i];
	return sqrt(sum);
}

TensorVoting::TensorVoting()
{
}

void TensorVoting::readFile(const string &fname,bool normal)
{
	ifstream ifile(fname.c_str());
	Vec3d v;
	int type;
	while(ifile>>v[0])
	{
		for(int i=1;i<3;i++)
			ifile>>v[i];
		ifile>>type;
		if(type==2) tensors.push_back(TensorVote(v));
		if(type==0)
		{
			Vec3d norm;
			for(int i=0;i<3;i++)
				ifile>>norm[i];
			ifile>>type;
			if(normal)
				tensors.push_back(TensorVote(v,TensorVote::STICK,norm));
			else
				tensors.push_back(TensorVote(v,TensorVote::PLATE,norm));
		}
	}
}

void TensorVoting::CloseFormVoting(double sigma)
{
	int n=tensors.size();
	for(int i=0;i<n;i++)
	{
		if(i%(n/100)==0)
			cout<<i<<" is voted"<<endl;
		for(int j=0;j<n;j++)
			if(i!=j)
				tensors[i].CloseFormVote(tensors[j],sigma);
	}
}

void TensorVoting::OutPut(const string &prefix,double thred)
{
	int n=tensors.size();
	vector<vector<Vec3d> > eigens;
	vector<double> saliency;
	eigens.resize(n);
	saliency.resize(n);
	double m=0;//the max saliency
	double scale=getBoundingBoxScale();
	//get eigenvectors and saliency of each tensors
	for(int i=0;i<n;i++)
	{
		eigens[i].resize(3);
		saliency[i]=tensors[i].Interpretation(eigens[i]);
		if(saliency[i]>m)
			m=saliency[i];
	}
	//scaling to visualize better
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<3;j++)
			eigens[i][j]*=scale/m*0.05;
		saliency[i]*=scale/m*0.05;
	}
	m*=scale/m*0.05;
	//output tensor file
	string fname=prefix+"_tensor.vw";
	ofstream ofile(fname.c_str());
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<3;j++)
			ofile<<tensors[i].position[j]<<" ";
		ofile<<19<<"\n";
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
				ofile<<tensors[i].position[k]<<" ";
			ofile<<"15 ";
			for(int k=0;k<2;k++)
				ofile<<eigens[i][j][k]<<" ";
			ofile<<eigens[i][j][2]<<"\n";
		}
	}
	ofile.close();
	//output inlier file
	fname=prefix+"_inlier.vw";
	ofile.open(fname.c_str());
	for(int i=0;i<n;i++)
		if(saliency[i]>m*thred)
		{
			for(int j=0;j<3;j++)
				ofile<<tensors[i].position[j]<<" ";
			ofile<<2<<"\n";
		}
	ofile.close();
	//output max eigenvectors
	fname=prefix+"_EMax.vw";
	ofile.open(fname.c_str());
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<3;k++)
			ofile<<tensors[i].position[k]<<" ";
		ofile<<"15 ";
		for(int k=0;k<2;k++)
			ofile<<eigens[i][0][k]<<" ";
		ofile<<eigens[i][0][2]<<"\n";
	}
	ofile.close();
	//output mid eigenvectors
	fname=prefix+"_EMid.vw";
	ofile.open(fname.c_str());
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<3;k++)
			ofile<<tensors[i].position[k]<<" ";
		ofile<<"15 ";
		for(int k=0;k<2;k++)
			ofile<<eigens[i][1][k]<<" ";
		ofile<<eigens[i][1][2]<<"\n";
	}
	ofile.close();
	////output min eigenvectors
	fname=prefix+"_EMin.vw";
	ofile.open(fname.c_str());
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<3;k++)
			ofile<<tensors[i].position[k]<<" ";
		ofile<<"15 ";
		for(int k=0;k<2;k++)
			ofile<<eigens[i][2][k]<<" ";
		ofile<<eigens[i][2][2]<<"\n";
	}
}

void TensorVoting::generateSphereSamples(int NSAMPLE)
{
	double t=(1.0+sqrt(5))/2.0;
	double a=sqrt(t)/pow(5.0,0.25);
	double b=1.0/(sqrt(t)*pow(5.0,0.25));
	double vertexs[12][3]={{-a,0,b},{0,b,-a},{0,b,a},{a,0,-b},
	{-b,-a,0},{-b,a,0},{0,-b,a},{b,a,0},
	{0,-b,-a},{a,0,b},{b,-a,0},{-a,0,-b}};//vertexs coordinate
	int faces[20][3]={{9,2,6},{1,5,11},{11,1,8},{0,11,4},{3,7,1},
	{3,1,8},{9,3,7},{0,2,6},{4,6,10},{1,7,5},
	{7,2,5},{8,10,3},{4,11,8},{9,2,7},{10,6,9},
	{0,11,5},{0,2,5},{8,10,4},{3,9,10},{6,4,0}};//faces with vertexs index
	double nsamplepertri=NSAMPLE/12.0;//number of samples in per triangle
	int level=ceil(log(nsamplepertri)/log(4.0));//levels of sampling in per triangle
	for(int i=0;i<20;i++)
	{
		vector<Vec3d> tri;
		tri.resize(3);
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				tri[j][k]=vertexs[faces[i][j]][k];
		subdivideTriangle(tri,level);
	}
	cout<<"Have Generated Sphere Samples!"<<endl;
	/*ofstream ofile("sphereSample.vw");
	for(int i=0;i<sphereSamples.size();i++)
	{
		for(int j=0;j<3;j++)
			ofile<<sphereSamples[i][j]<<" ";
		ofile<<2<<endl;
	}
	ofile.close();*/
}

void TensorVoting::subdivideTriangle(const vector<Vec3d> &tri,int level)
{
	queue<vector<Vec3d> > vertexs;
	//the queue to store subdivided triangles
	queue<bool> check;
	//whether the triangle corresponding in vertexs is in the middle of its father
	vertexs.push(tri);
	check.push(true);
	int count=pow(4,level);//number of samples
	while(count>0)
	{
		vector<Vec3d> t=vertexs.front();vertexs.pop();
		if(check.front())
		//if the triangle corresponding in vertexs is not in the middle of its father,
		//add its middle point to the samples
		{
			Vec3d mid=(t[0]+t[1]+t[2])/3.0;
			sphereSamples.push_back(mid/norm(mid));
			count--;
		}
		check.pop();
		Vec3d mid01=(t[0]+t[1])/2.0;
		Vec3d mid02=(t[0]+t[2])/2.0;
		Vec3d mid12=(t[1]+t[2])/2.0;
		vector<Vec3d> t1,t2,t3,t4;
		//push four subdivided triangles in the queue
		t1.push_back(t[0]);t1.push_back(mid01);t1.push_back(mid02);
		vertexs.push(t1);check.push(true);
		t2.push_back(t[1]);t2.push_back(mid01);t2.push_back(mid12);
		vertexs.push(t2);check.push(true);
		t3.push_back(t[2]);t3.push_back(mid02);t3.push_back(mid12);
		vertexs.push(t3);check.push(true);
		t4.push_back(mid01);t4.push_back(mid02);t4.push_back(mid12);
		vertexs.push(t4);check.push(false);
	}
}

void TensorVoting::generateCircleSamples(int NSAMPLE)
{
	double gap=2*CV_PI/NSAMPLE;
	for(double angle=0;angle<2*CV_PI;angle+=gap)
		circleSamples.push_back(Vec3d(cos(angle),sin(angle),0));
	cout<<"Have Generated Circle Samples!"<<endl;
}

void TensorVoting::VotingWithField(double sigma,double constant,double nsample)
{
	generateCircleSamples(nsample);
	generateSphereSamples(nsample);
	int n=tensors.size();
	for(int i=0;i<n;i++)
	{
		if(i%(n/100)==0)
			cout<<i<<" is voted"<<endl;
		for(int j=0;j<n;j++)
			if(i!=j)
				tensors[i].genTensorVote(tensors[j],sigma,constant,sphereSamples,circleSamples);
	}
}

double TensorVoting::getBoundingBoxScale()
{
	Vec3d pmax(DBL_MIN,DBL_MIN,DBL_MIN);
	Vec3d pmin(DBL_MAX,DBL_MAX,DBL_MAX);
	int n=tensors.size();
	for(int i=0;i<n;i++)
		for(int j=0;j<3;j++)
		{
			if(tensors[i].position[j]>pmax[j])
				pmax[j]=tensors[i].position[j];
			if(tensors[i].position[j]<pmin[j])
				pmin[j]=tensors[i].position[j];
		}
	return norm(pmax-pmin);
}

void TensorVoting::generateFieldFile(const string &prefix,int K,double sigma,double constant,double nsample)
{
	generateCircleSamples(nsample);
	generateSphereSamples(nsample);
	//obtain point around the voter
	for(int i=0;i<K;i++)
		for(int j=0;j<K;j++)
			for(int k=0;k<K;k++)
			{
				Vec3d p(6*(i-K/2.0)*sigma/K,6*(j-K/2.0)*sigma/K,6*(k-K/2.0)*sigma/K);
				tensors.push_back(TensorVote(p));
			}
	string fname=prefix+".fld";
	ofstream ofile(fname.c_str());
	ofile<<sigma<<" "<<constant<<" "<<K<<endl;
	//generate stick voting field
	TensorVote stickvoter(Vec3d(0,0,0),TensorVote::STICK);
	for(int i=0;i<tensors.size();i++)
	{
		if(i%(K*K)==0)
			cout<<i<<endl;
		tensors[i].genTensorVote(stickvoter,sigma,constant,sphereSamples,circleSamples);
		Matx33d outtensor=tensors[i].getOutTensor();
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				ofile<<outtensor(j,k)<<" ";
		ofile<<endl;
	}
	ofile<<endl;
	OutPut(prefix+"_stickField",0);
	cout<<"Stick field complete!"<<endl;
	//generate plate voting field
	TensorVote platevoter(Vec3d(0,0,0),TensorVote::PLATE);
	for(int i=0;i<tensors.size();i++)
	{
		if(i%(K*K)==0)
			cout<<i<<endl;
		tensors[i].resetOutTensor();
		tensors[i].genTensorVote(platevoter,sigma,constant,sphereSamples,circleSamples);
		Matx33d outtensor=tensors[i].getOutTensor();
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				ofile<<outtensor(j,k)<<" ";
		ofile<<endl;
	}
	ofile<<endl;
	OutPut(prefix+"_plateField",0);
	cout<<"Plate field complete!"<<endl;

	/*tensors.clear();
	for(int i=0;i<K;i++)
	{
		Vec3d p(3*i*sigma/K,0,0);
		tensors.push_back(TensorVote(p));
	}
	TensorVote sphereVoter(Vec3d(0,0,0));
	for(int i=0;i<tensors.size();i++)
	{
		cout<<i<<endl;
		tensors[i].genTensorVote(sphereVoter,sigma,constant,sphereSamples,circleSamples);
		Matx33d outtensor=tensors[i].getOutTensor();
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				ofile<<outtensor(j,k)<<" ";
		ofile<<endl;
	}*/
	//generate sphere voting field
	TensorVote spherevoter(Vec3d(0,0,0));
	for(int i=0;i<tensors.size();i++)
	{
		if(i%(K*K)==0)
			cout<<i<<endl;
		tensors[i].resetOutTensor();
		tensors[i].genTensorVote(spherevoter,sigma,constant,sphereSamples,circleSamples);
		Matx33d outtensor=tensors[i].getOutTensor();
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				ofile<<outtensor(j,k)<<" ";
		ofile<<endl;
	}
	OutPut(prefix+"_sphereField",0);
	cout<<"Sphere field complete!"<<endl;
	ofile.close();
}

Matx33d TensorVote::getOutTensor()
{
	return tensorsum;
}

void TensorVote::resetOutTensor()
{
	tensorsum=Matx33d::zeros();
}

double TensorVoting::readFieldFile(const string &fname)
{
	ifstream ifile(fname.c_str());
	double sigma,constant;
	int K;
	ifile>>sigma>>constant>>K;
	stickField.resize(K);
	cout<<"Begin to read stick field!"<<endl;
	for(int i=0;i<K;i++)
	{
		cout<<i<<endl;
		stickField[i].resize(K);
		for(int j=0;j<K;j++)
		{
			stickField[i][j].resize(K);
			for(int k=0;k<K;k++)
				for(int r=0;r<3;r++)
					for(int l=0;l<3;l++)
						ifile>>stickField[i][j][k](r,l);
		}
	}
	plateField.resize(K);
	cout<<"Begin to read plate field!"<<endl;
	for(int i=0;i<K;i++)
	{
		cout<<i<<endl;
		plateField[i].resize(K);
		for(int j=0;j<K;j++)
		{
			plateField[i][j].resize(K);
			for(int k=0;k<K;k++)
				for(int r=0;r<3;r++)
					for(int l=0;l<3;l++)
						ifile>>plateField[i][j][k](r,l);
		}
	}
	sphereField.resize(K);
	cout<<"Begin to read sphere field!"<<endl;
	for(int i=0;i<K;i++)
	{
		cout<<i<<endl;
		sphereField[i].resize(K);
		for(int j=0;j<K;j++)
		{
			sphereField[i][j].resize(K);
			for(int k=0;k<K;k++)
				for(int r=0;r<3;r++)
					for(int l=0;l<3;l++)
						ifile>>sphereField[i][j][k](r,l);
		}
	}
	return sigma;
}

/*void TensorVote::combineTensorFromField(const TensorVote &voter,double sigma,const vector<Matx33d> &field)
{
	double d=norm(position-voter.position);
	int K=field.size();
	int index=d/(3.0*sigma)*K+0.5;
	if(index>=K)
		return;
	tensorsum+=field[index];
	return;
}*/

void TensorVote::combineTensorFromField(const TensorVote &voter,double sigma,const vector<vector<vector<Matx33d> > > &field)
{
	int K=field.size();
	Vec3d pn=voter.eigenVectors.t()*(position-voter.position);
	int x=pn[0]*K/(6.0*sigma)+K/2.0+0.5;
	int y=pn[1]*K/(6.0*sigma)+K/2.0+0.5;
	int z=pn[2]*K/(6.0*sigma)+K/2.0+0.5;
	if(x<0||x>=K||y<0||y>=K||z<0||z>=K)
		return;
	tensorsum+=voter.eigenVectors*field[x][y][z]*voter.eigenVectors.t();
}

void TensorVote::genTensorVote(const TensorVote &voter,double sigma,
		const vector<vector<vector<Matx33d> > > &stickField,
		const vector<vector<vector<Matx33d> > > &plateField,
		const vector<vector<vector<Matx33d> > > &sphereField)
{
	Vec3d r=position-voter.position;
	if(norm(r)>3*sigma)
		return;
	if(voter.saliency[0]>0)
		combineTensorFromField(voter,sigma,stickField);
	if(voter.saliency[1]>0)
		combineTensorFromField(voter,sigma,plateField);
	if(voter.saliency[2]>0)
		combineTensorFromField(voter,sigma,sphereField);
}

void TensorVoting::VotingWithField(const string &fname)
{
	double sigma=readFieldFile(fname);
	int n=tensors.size();
	for(int i=0;i<n;i++)
	{
		if(i%(n/100)==0)
			cout<<i<<" is voted"<<endl;
		for(int j=0;j<n;j++)
			if(i!=j)
				tensors[i].genTensorVote(tensors[j],sigma,stickField,plateField,sphereField);
	}
}