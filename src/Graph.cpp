#include "Graph.h"

Graph::Graph(vector<pair<double, double>> data_, string graphName_, int xMin_, int yMin_, int xMax_, int yMax_)
{
    data = data_;
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
        gp << "plot" << gp.file1d(data) << "with lines title '"+graphName+"'" << std::endl;
        ret = 0;
    }
    else
        ret = -1;

    return ret;
}

void Graph::test_regression()
{
    double y=0;
    vector<pair<double, double>> d;
    for(double i = 0;i<500;i+=5)
    {
        y += (double)((rand()%1000)/100);
        cout<<"val y : "<<y<<endl;
        d.push_back(make_pair(i,y));
    }
    Graph(d,"test",0,0,500,500);
}