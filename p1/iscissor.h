#ifndef ISCISSOR_H
#define ISCISSOR_H
#include<QImage>
#include"fibheap.h"

using namespace std;


class PixelNode:public FibHeapNode
{
public:
    enum State{INITIAL, ACTIVE, EXPANDED};
private:
    double linkCost[8];
    int column, row;
public:
    PixelNode(int c,int r);
    void setLinkCost(int link,double value);
    double LinkCost(int link);//return linkcost with linkID
    double LinkCost(PixelNode *pn);//return linkcost between this and pn, return -1 if they are not neighbor;this is not used now
    State state;
    double totalCost;
    PixelNode *prevNode;
    double Column();
    double Row();
    virtual void operator =(PixelNode& RHS);
    virtual int  operator ==(PixelNode& RHS);
    virtual int  operator <(PixelNode& RHS);
    virtual void Print();
    void Neighbor(int link,int &c,int &r);//return column and row of neighbor in link direction
};

class Iscissor
{
public:
    enum CostFunction{MODIFIED, ORIGIN};//cost function,modified is the basic requriement in this project,origin is the paper's
private:
    QImage * img;
    QImage mask;
    vector<vector<PixelNode*> > pixelnodes;
    PixelNode *seed;
    CostFunction costfunction;
    void costFun();
    void costFunModify();
    void costFunOrigin();
    double getD(int i,int j,int link, const QImage &tmpimg);
    void updatePathTree();
    void initializePixelNodes();
public:
    Iscissor(QImage *image,CostFunction cf=MODIFIED);//image is the original image
    void setCostFunction(CostFunction cf);
    void setSeed(int column,int row);
    QPoint snapSeed(int column,int row);
    //find one edge point closed to the input as a seed, return the new seed meanwhile update path tree
    void setMask(const QImage &m);//set the region that path mask stay
    QImage drawPixelNode();
    QImage drawCostGraph();
    QImage drawPathTree();
    void getPath(int column, int row, vector<QPoint> &path);
    //return path from seed to (column,row), pair.first is column, pair.second is row
};

#endif // ISCISSOR_H
