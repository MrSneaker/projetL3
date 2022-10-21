#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::setisVisited(bool visited)
{
    isVisited = visited;
}

bool Node::getisVisited()
{
    return isVisited;
}

void Node::setisObstacle(bool obstacle)
{
    isObstacle = obstacle;
}

bool Node::getisObstacle()
{
    return isObstacle;
}

void Node::setlocalGoal(float newlocalGoal)
{
    localGoal = newlocalGoal;
}

float Node::getlocalGoal()
{
    return localGoal;
}

void Node::setGlobalGoal(float newglobalGoal)
{
    GlobalGoal = newglobalGoal;
}

float Node::getGlobalGoal()
{
    return GlobalGoal;
}
void Node::setParent(Node *parent)
{
    this->parent = parent;
}

Node *Node::getParent()
{
    return parent;
}

void Node::setVecNeighbours(vector<Node *> VecNeighbours)
{
    this->VecNeighbours = VecNeighbours;
}

vector<Node *> Node::getVecNeighbours()
{
    return VecNeighbours;
}

void Node::setNodepos(Vec2 pos)
{
    Nodepos = pos;
}

Vec2 Node::getNodepos()
{
    return Nodepos;
}