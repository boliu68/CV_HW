#include <iostream>
#include "mvm.h"

using namespace std;

int main(int argc, char *argv[])
{
    //cout << "Hello World!" << endl;
	if(argc<5)
	{
		cout<<"Bad Input!"<<endl;
		return 0;
	}
	string methodtype(argv[1]);
	string input(argv[2]);
	string output(argv[3]);
	int nsample;
	sscanf(argv[4],"%d",&nsample);

	MVM mm;
	if(methodtype.compare("initial")==0)
		mm.initialNormal(nsample,input,output);
	else if(methodtype.compare("refine")==0)
	{
		if(argc<9)
		{
			cout<<"Bad Input!"<<endl;
			return 0;
		}
		double lamda,sigma,thred;
		int itermax;
		sscanf(argv[5],"%lf",&lamda);
		sscanf(argv[6],"%lf",&sigma);
		sscanf(argv[7],"%d",&itermax);
		sscanf(argv[8],"%lf",&thred);
		if(!mm.readInitialNormal(input))
		{
			cout<<"Bad Input!"<<endl;
			return 0;
		}
		mm.Refinement(nsample,sigma,lamda,itermax,thred);
		mm.outPutNormal(output);
		mm.outPutSlantTilt(output);
	}
	else
	{
		cout<<"Bad Input!"<<endl;
		return 0;
	}

	return 0;
}

