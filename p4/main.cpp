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
	return 0;
}

