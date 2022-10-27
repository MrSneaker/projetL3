#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include "vec2.h"

using namespace std;

class Node
{
private:
    Vec2 Nodepos;
    bool isVisited = false;
    bool isObstacle = false;

    Node *parent;
    vector<Node *> VecNeighbours;

public:
    vector<Node *> nodes;
    bool open = false;
    float localGoal;
    float GlobalGoal;
    int indice;
    //! \brief Constructeur
    Node();
    //! \brief Destructeur
    ~Node();
    //! \brief Fonction permettant de modifier la valeur de isVisited
    //! \param visited valeur booléenne
    void setisVisited(bool visited);
    //! \brief Fonction permettant de récupérer la valeur de isVisited
    //! \return isVisited
    bool getisVisited();
    //! \brief Fonction permettant de modifier la valeur de isObstacle
    //! \param obstacle valeur booléenne
    void setisObstacle(bool obstacle);
    //! \brief Fonction permettant de récupérer la valeur de isObstacle
    //! \return isObstacle
    bool getisObstacle();
    //! \brief Fonction permettant de modifier la valeur de parent
    //! \param parent pointeur sur un noeud
    void setParent(Node *parent);
    //! \brief Fonction permettant de récupérer la valeur de parent
    //! \return parent
    Node *getParent();
    //! \brief Fonction permettant de modifier la valeur de VecNeighbours
    //! \param VecNeighbours vecteur de pointeurs sur des nodes
    void setVecNeighbours(vector<Node *> VecNeighbours);
    //! \brief Fonction permettant de récupérer la valeur de VecNeighbours
    //! \return VecNeighbours
    vector<Node *> &getVecNeighbours();
    //! \brief Fonction permettant de modifier la valeur de Nodepos
    //! \param pos vecteur 2D
    void setNodepos(Vec2 pos);
    //! \brief Fonction permettant de récupérer la valeur de Nodepos
    //! \return Nodepos
    Vec2 getNodepos();
};

#endif