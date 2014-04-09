#include"Vote.h"

void closeFormVoting(int argc, char *argv[])
{
	if(argc<7)
	{
		cout<<"Bad Input!"<<endl;
		return;
	}
	string ifname(argv[2]);
	string ofname(argv[3]);
	double sigma;
	sscanf(argv[4],"%lf",&sigma);
	double thred;
	sscanf(argv[5],"%lf",&thred);
	TensorVoting tv;
	string vectortype(argv[6]);
	if(vectortype.compare("NORMAL")==0)
		tv.readFile(ifname);
	else if(vectortype.compare("TANGENT")==0)
		tv.readFile(ifname,false);
	tv.CloseFormVoting(sigma);
	tv.OutPut(ofname,thred);
}

void votingWithField(int argc, char *argv[])
{
	if(argc<9)
	{
		cout<<"Bad Input!"<<endl;
		return;
	}
	string ifname(argv[2]);
	string ofname(argv[3]);
	double sigma;
	sscanf(argv[4],"%lf",&sigma);
	double thred;
	sscanf(argv[5],"%lf",&thred);
	TensorVoting tv;
	string vectortype(argv[6]);
	if(vectortype.compare("NORMAL")==0)
		tv.readFile(ifname);
	else if(vectortype.compare("TANGENT")==0)
		tv.readFile(ifname,false);
	double constant,nsample;
	sscanf(argv[7],"%lf",&constant);
	sscanf(argv[8],"%lf",&nsample);
	tv.VotingWithField(sigma,constant,nsample);
	tv.OutPut(ofname,thred);
}

void votingWithFieldFile(int argc, char *argv[])
{
	if(argc<7)
	{
		cout<<"Bad Input!"<<endl;
		return;
	}
	string ifname(argv[2]);
	string ofname(argv[3]);
	string fieldname(argv[4]);
	double thred;
	sscanf(argv[5],"%lf",&thred);
	TensorVoting tv;
	string vectortype(argv[6]);
	if(vectortype.compare("NORMAL")==0)
		tv.readFile(ifname);
	else if(vectortype.compare("TANGENT")==0)
		tv.readFile(ifname,false);
	tv.VotingWithField(fieldname);
	tv.OutPut(ofname,thred);
}

void generateFieldFile(int argc,char *argv[])
{
	if(argc<7)
	{
		cout<<"Bad Input!"<<endl;
		return;
	}
	string ofname(argv[2]);
	double sigma;
	sscanf(argv[3],"%lf",&sigma);
	double constant,nsample;
	sscanf(argv[4],"%lf",&constant);
	sscanf(argv[5],"%lf",&nsample);
	int K;
	sscanf(argv[6],"%d",&K);
	TensorVoting tv;
	tv.generateFieldFile(ofname,K,sigma,constant,nsample);
}

int main(int argc, char *argv[]) 
{
	if(argc<2)
	{
		cout<<"Bad Input!"<<endl;
		return 0;
	}
	string methodtype(argv[1]);

	if(methodtype.compare("CLOSE")==0)
		closeFormVoting(argc,argv);
	else if(methodtype.compare("FIELD")==0)
		votingWithField(argc,argv);
	else if(methodtype.compare("GENFIELD")==0)
		generateFieldFile(argc,argv);
	else if(methodtype.compare("FIELDFILE")==0)
		votingWithFieldFile(argc,argv);
	else
		cout<<"Bad Input!"<<endl;
	return 0;
}