#include "mvm.h"
#include "graph.h"
#include "define.h"

void errorInformation(const char* str)
{
    cout<<str<<endl;
}

MVM::MVM()
{
}

void MVM::initialNormal(int NSAMPLE, const string &folder, const string &outPrefix)
{
    //LIU BO
	bool is_readfile = this->normal.read_file(folder);
	
	if(!is_readfile)
		return;

    normal.uniform_division(1,NSAMPLE);
	normal.find_denominator(0.7, 0.9);
	normal.get_normal();

	this->width = normal.norm_width;
	this->height = normal.norm_height;
	this->pixels = normal.pixels;

	this->outPutNormal(outPrefix);
	this->outPutSlantTilt(outPrefix);
}

void MVM::Refinement(int NSAMPLE, double sigma, double lamda,int itermax,double thred)
{
    generateSphereSamples(NSAMPLE,samples);
	setInitialLabel();
	preCompEnergy(sigma,lamda);
    GRAPH graph(2+width*height+(width-1)*height+(height-1)*width,
                2*width*height+2*((width-1)*height+(height-1)*width),
                errorInformation);
    int nsample=samples.size();
    double m=DBL_MAX;
	int count=0;
    while(count<itermax)
    {
        cout<<"iteration "<<count++<<": Energy="<<m<<endl;
		double tmpm=m;
        for(int i=0;i<nsample;i++)
        {
            if(i%(nsample/50)==0)
				cout<<i<<endl;
			double energy=alphaExpansion(i,graph,sigma,lamda);
            if(energy<tmpm)
            {
                tmpm=energy;
                assignTmpLabel(graph,i);
            }
        }
		double md=m-tmpm;
		cout<<"decrease="<<md<<", percent="<<md/tmpm<<endl;
        if(tmpm<m)
        {
            m=tmpm;
            assignLabel();
			if(md/m<thred)
				break;
        }
        else
            break;
    }
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            pixels[i][j].setNormal(samples[pixels[i][j].label]);
}

double MVM::alphaExpansion(int label, GRAPH &graph,double sigma,double lamda)
{
    constructGraph(label,graph,sigma,lamda);
    return graph.maxflow();
}

//vertex id: 0-w*h-1: pixels, w*h & w*h+1: a, abar, w*h+2...:auxi
void MVM::constructGraph(int label, GRAPH &graph,double sigma,double lamda)
{
    graph.reset();
    graph.add_node(width*height+2);
    int count=width*height+1;
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
		{
			double source=DE[i][j][label];
            double sink;
            if(pixels[i][j].label==label)
                sink=1000000;
            else
				sink=DE[i][j][pixels[i][j].label];
            graph.add_tweights(width*i+j,source,sink);
            if(i+1<height)
            {
                if(pixels[i][j].label!=pixels[i+1][j].label)
                {
                    graph.add_node();
                    count++;
					sink=SE[pixels[i][j].label][pixels[i+1][j].label];
                    graph.add_tweights(count,0,sink);
                    double e=SE[pixels[i][j].label][label];
                    graph.add_edge(width*i+j,count,e,e);
                    e=SE[pixels[i+1][j].label][label];
                    graph.add_edge(count,width*(i+1)+j,e,e);
                }
                else
                {
                    double e=SE[pixels[i][j].label][label];
                    graph.add_edge(width*i+j,width*(i+1)+j,e,e);
                }
            }
            if(j+1<width)
            {
                if(pixels[i][j].label!=pixels[i][j+1].label)
                {
                    graph.add_node();
                    count++;
                    sink=SE[pixels[i][j].label][pixels[i][j+1].label];
                    graph.add_tweights(count,0,sink);
                    double e=SE[pixels[i][j].label][label];
                    graph.add_edge(width*i+j,count,e,e);
                    e=SE[pixels[i][j+1].label][label];
                    graph.add_edge(count,width*i+j+1,e,e);
                }
                else
                {
                    double e=SE[pixels[i][j].label][label];
                    graph.add_edge(width*i+j,width*i+j+1,e,e);
                }
            }
        }

}

double MVM::dataEnergy(int r, int c)
{
    Vec3d n1=pixels[r][c].Normal();
    Vec3d n2=samples[pixels[r][c].label];
    return cv::norm(n1-n2);
}

double MVM::dataEnergy(int r, int c,int label)
{
    Vec3d n1=pixels[r][c].Normal();
    Vec3d n2=samples[label];
    return cv::norm(n1-n2);
}

double MVM::smoothEnergy(int r1, int c1, int r2, int c2, double lamda, double sigma)
{
    Vec3d n1=samples[pixels[r1][c1].label];
	Vec3d n2=samples[pixels[r2][c2].label];
    double d=cv::norm(n1-n2);
    return lamda*log(1.0+d/2.0/sigma/sigma);
}

double MVM::smoothEnergy(int r, int c, int label, double lamda, double sigma)
{
    Vec3d n1=samples[label];
    Vec3d n2=samples[pixels[r][c].label];
    double d=cv::norm(n1-n2);
    return lamda*log(1.0+d/2.0/sigma/sigma);
}

void MVM::assignTmpLabel(GRAPH &graph, int label)
{
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
			GRAPH::termtype type=graph.what_segment(i*width+j);
            if(type==GRAPH::SINK)
                pixels[i][j].tmplabel=label;
			else
				pixels[i][j].tmplabel=pixels[i][j].label;
        }
}

void MVM::assignLabel()
{
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			//if(pixels[i][j].tmplabel<0||pixels[i][j].tmplabel>=samples.size())
			//	cout<<"bug:"<<i<<" "<<j<<" "<<pixels[i][j].tmplabel<<endl;
			pixels[i][j].label=pixels[i][j].tmplabel;
		}
}

void MVM::outPutNormal(const string &prefix)
{
    string xname=prefix+"_x.txt";
    string yname=prefix+"_y.txt";
	string zname = prefix +"_z.txt";
	string confname=prefix+"_conf.txt";
    ofstream xif(xname.c_str());
    ofstream yif(yname.c_str());
	ofstream zif(zname.c_str());
	ofstream conf(confname.c_str());
	conf<<height<<" "<<width;
	conf.close();

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            Vec3d normal=pixels[i][j].Normal();
            //double cossl=abs(normal[2]);
			//if(cossl>1.0) cossl=1.0;
			//double slant=acos(cossl);
			//double slant = sqrt(normal[0] * normal[0] + normal[1] * normal[1]);
			//slant = -atan(slant / normal[2]);
			double x = normal[0];
			xif<<x<<" ";
			//double costi=normal[0]/sqrt(normal[0]*normal[0]+normal[1]*normal[1]);
			//if(costi>1.0) costi=1.0;
			//if(costi<-1.0) costi=-1.0;
			//double tilt=acos(costi);
			double y = normal[1];
			//if(normal[1]<0)
			//  tilt=CV_PI*2-tilt;
			yif<<y<<" ";

			zif<<normal[2]<<" ";
		}
		xif<<endl;
		yif<<endl;
		zif<<endl;
	}
	xif.close();
	yif.close();
	zif.close();
}


void MVM::outPutSlantTilt(const string &prefix)
{
    string slname=prefix+"_slant.txt";
    string tiname=prefix+"_tilt.txt";
    ofstream slf(slname.c_str());
    ofstream tif(tiname.c_str());

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            Vec3d normal=pixels[i][j].Normal();
            double cossl=abs(normal[2]);
            if(cossl>1.0) cossl=1.0;
            double slant=acos(cossl);
            //double slant = sqrt(normal[0] * normal[0] + normal[1] * normal[1]);
			//slant = -atan(slant / normal[2]);
			slf<<slant<<" ";
            double costi=normal[0]/sqrt(normal[0]*normal[0]+normal[1]*normal[1]);
            if(costi>1.0) costi=1.0;
            if(costi<-1.0) costi=-1.0;
            double tilt=acos(costi);
			if(normal[1]<0)
                tilt=CV_PI*2-tilt;
			tif<<tilt<<" ";

        }
		slf<<endl;
		tif<<endl;
    }
	slf.close();
	tif.close();
}


bool MVM::readInitialNormal(const string &prefix)
{
	string xname=prefix+"_x.txt";
    string yname=prefix+"_y.txt";
	string zname = prefix +"_z.txt";
	string confname=prefix+"_conf.txt";
    ifstream xif(xname.c_str());
    ifstream yif(yname.c_str());
	ifstream zif(zname.c_str());
	ifstream conf(confname.c_str());
	if(!conf.is_open()||!xif.is_open()||!yif.is_open()||!zif.is_open())
		return false;
	conf>>height>>width;
	pixels.resize(height);
	for(int i=0;i<height;i++)
	{
		pixels[i].resize(width);
		for(int j=0;j<width;j++)
		{
			Vec3d n;
			xif>>n[0];
			yif>>n[1];
			zif>>n[2];
			pixels[i][j].setNormal(n);
		}
	}
	return true;
}

void MVM::setInitialLabel()
{
	int i,j,k,m,index;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			m=cv::norm(pixels[i][j].Normal()-samples[0]);
			index=0;
			for(k=1;k<samples.size();k++)
			{
				double d=cv::norm(pixels[i][j].Normal()-samples[k]);
				if(d<m)
				{
					m=d;
					index=k;
				}
			}
			pixels[i][j].label=index;
			pixels[i][j].tmplabel=index;
		}
}

void MVM::preCompEnergy(double sigma,double lamda)
{
	int i,j,k,ns=samples.size();
	DE.resize(height);
	for(i=0;i<height;i++)
	{
		DE[i].resize(width);
		for(j=0;j<width;j++)
		{
			DE[i][j].resize(ns);
			for(k=0;k<ns;k++)
				DE[i][j][k]=dataEnergy(i,j,k);
		}
	}
	SE.resize(ns);
	for(i=0;i<ns;i++)
	{
		SE[i].resize(ns);
		for(j=0;j<ns;j++)
		{
			Vec3d n1=samples[i];
			Vec3d n2=samples[j];
			double d=cv::norm(n1-n2);
			SE[i][j]=lamda*log(1.0+d/2.0/sigma/sigma);
		}
	}
}