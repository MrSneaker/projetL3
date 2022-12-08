#ifndef _GRAPH_H__
#define _GRAPH_H__

#include <string>
#include <iostream>
#include <vector>
#include <gnuplot-iostream.h>
#include <time.h>
#include <random>

using namespace std;

class Graph
{
    private:
    vector<pair<double,double>> data1;
    vector<pair<double,double>> data2;
    vector<pair<double,double>> data3;
    string graphName;
    int xMin;
    int yMin;
    int xMax;
    int yMax;
    Gnuplot gp;

    public:
    //! \brief constructeur par défaut, utiliser uniquement dans le test régression.
    Graph();
    //! \brief destructeur de graph.
    ~Graph();
    //! \brief constructeur de graphiques prenant trois source de données différentes, pour comparer les courbes de 3 parkings par exemples.
    Graph(vector<pair<double,double>> data1_, vector<pair<double,double>> data2_, vector<pair<double,double>> data3_, string graphName_, int xMin_, int yMin_, int xMax_, int yMax_);
    //! \brief constructeur de grahique avec courbe unique.
    Graph(vector<pair<double,double>> data1_, string graphName_, int xMin_, int yMin_, int xMax_, int yMax_);
    //! \brief fonction de création de graphique.
    //! \return retourne 0 si pas d'erreur, -1 sinon. 
    int createGraph();
    void test_regression();
};

#endif