#include "sampling.h"

void subdivideTriangle(const vector<Vec3d> &tri,int level,vector<Vec3d> &sphereSamples)
{
    queue<vector<Vec3d> > vertexs;
    //the queue to store subdivided triangles
    queue<bool> check;
    //whether the triangle corresponding in vertexs is in the middle of its father
    vertexs.push(tri);
    check.push(true);
    int count=pow(4,double(level));//number of samples
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

void generateSphereSamples(int NSAMPLE,vector<Vec3d> &sphereSamples)
{
    double t=(1.0+sqrt(double(5)))/2.0;
    double a=sqrt(t)/pow(5.0,0.25);
    double b=1.0/(sqrt(t)*pow(5.0,0.25));
    double vertexs[12][3]={{-a,0,b},{0,b,-a},{0,b,a},{a,0,-b},
    {-b,-a,0},{-b,a,0},{0,-b,a},{b,a,0},
    {0,-b,-a},{a,0,b},{b,-a,0},{-a,0,-b}};//vertexs coordinate
    int faces[20][3]={{9,2,6},{1,5,11},{11,1,8},{0,11,4},{3,7,1},
    {3,1,8},{9,3,7},{0,2,6},{4,6,10},{1,7,5},
    {7,2,5},{8,10,3},{4,11,8},{9,2,7},{10,6,9},
    {0,11,5},{0,2,5},{8,10,4},{3,9,10},{6,4,0}};//faces with vertexs index
    double nsamplepertri=NSAMPLE/20.0;//number of samples in per triangle
    int level=ceil(log(nsamplepertri)/log(4.0));//levels of sampling in per triangle
    for(int i=0;i<20;i++)
    {
        vector<Vec3d> tri;
        tri.resize(3);
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                tri[j][k]=vertexs[faces[i][j]][k];
        subdivideTriangle(tri,level,sphereSamples);
    }
    //cout<<"Have Generated Sphere Samples!"<<endl;
    /*ofstream ofile("sphereSample.vw");
    for(int i=0;i<sphereSamples.size();i++)
    {
        for(int j=0;j<3;j++)
            ofile<<sphereSamples[i][j]<<" ";
        ofile<<2<<endl;
    }
    ofile.close();*/
}