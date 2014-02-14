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
private:
    QImage * img;
    vector<vector<PixelNode*> > pixelnodes;
    PixelNode *seed;
    virtual void costFun();
    virtual double getD(int i,int j,int link, const QImage &tmpimg);
    void transColorFormat(QRgb qrgb,int color[3]);
    void updatePathTree();
    void initializePixelNodes();
public:
    Iscissor(QImage *image);//image is the original image
    void setSeed(int column,int row);
    QImage drawPixelNode();
    QImage drawCostGraph();
    QImage drawPathTree();
    void getPath(int column, int row, vector<QPoint> &path);
    //return path from seed to (column,row), pair.first is column, pair.second is row
};

#endif // ISCISSOR_H
