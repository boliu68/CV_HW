#ifndef MVM_H
#define MVM_H
#include"define.h"
#include"pixel.h"
#include"graph.h"
typedef Graph<double,double,double> GRAPH;
class MVM
{
private:
    vector<vector<Pixel> > pixels;
    void Refinement(int NSAMPLE, double sigma, double lamda);
    void initialNormal(int NSAMPLE);
    double alphaExpansion(int label, GRAPH &graph, double sigma, double lamda);
    void constructGraph(int label, GRAPH &graph, double sigma, double lamda);
    int width, height;
    double dataEnergy(int r,int c);//r:row, c:column
    double dataEnergy(int r, int c, int label);
    double smoothEnergy(int r1,int c1,int r2,int c2,double lamda,double sigma);
    double smoothEnergy(int r,int c,int label,double lamda,double sigma);
    vector<Vec3d> samples;
    void assignTmpLabel(GRAPH &graph, int label);
    void assignLabel();
public:
    MVM();
    void outPutNormal(const string &prefix);
};

#endif // MVM_H
