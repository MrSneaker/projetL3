#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
    for(int i=0;i<VecNeighbours.size();i++)
        VecNeighbours[i] = nullptr;
    parent = nullptr;
}

void Node::setisVisited(bool visited)
{
    isVisited = visited;
}

const bool& Node::getisVisited() const
{
    return isVisited;
}

void Node::setisObstacle(bool obstacle)
{
    isObstacle = obstacle;
}

const bool& Node::getisObstacle() const
{
    return isObstacle;
}

void Node::setParent(Node *parent)
{
    this->parent = parent;
}

Node *Node::getParent() const
{
    return parent;
}

void Node::setVecNeighbours(vector<Node *> VecNeighbours)
{
    this->VecNeighbours = VecNeighbours;
}

vector<Node *> &Node::getVecNeighbours()
{
    return VecNeighbours;
}

void Node::setNodepos(Vec2 pos)
{
    Nodepos = pos;
}

const Vec2& Node::getNodepos() const
{
    return Nodepos;
}