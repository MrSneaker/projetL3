#include "Graph.h"

Graph::Graph(vector<pair<double,double>> data1_, vector<pair<double,double>> data2_, vector<pair<double,double>> data3_, string graphName_, int xMin_, int yMin_, int xMax_, int yMax_)
{
    data1 = data1_;
    data2 = data2_;
    data3 = data3_;
    graphName = graphName_;
    xMin = xMin_;
    xMax = xMax_;
    yMin = yMin_;
    yMax = yMax_;
    int r = createGraph();
    if(r == -1)
        cerr<<"error in an attempt of creating an instance of Graph.";
}

Graph::Graph()
{

}

int Graph::createGraph()
{
    int ret;
    if (gp.good())
    {
        gp << "set xrange [" + to_string(xMin) + ":" + to_string(xMax) + "]\nset yrange [" + to_string(yMin) + ":" + to_string(yMax) + "]\n";
        gp << "plot" << gp.file1d(data1) << "with lines title '"+graphName+"0"+"'," << gp.file1d(data2)<< "with lines title '"+graphName+"1"+"',"
           << gp.file1d(data3) << "with lines title '"+graphName+"3"+"'," <<
        std::endl;
        ret = 0;
    }
    else
        ret = -1;

    return ret;
}

void Graph::test_regression()
{
    srand(time(NULL));
    double y1=0;
    double y2=0;
    double y3=0;
    vector<pair<double, double>> d1;
    vector<pair<double, double>> d2;
    vector<pair<double, double>> d3;
    for(double i = 0;i<500;i+=5)
    {
        y1 += (double)((rand()%1000)/100);
        y2 += (double)((rand()%1000)/100);
        y3 += (double)((rand()%1000)/100);
        d1.push_back(make_pair(i,y1));
        d2.push_back(make_pair(i,y2));
        d3.push_back(make_pair(i,y3));
    }
    Graph(d1,d2,d3,"test",0,0,500,500);
}