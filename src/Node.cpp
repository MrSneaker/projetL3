#include "Node.h"

Node::Node() {
}

Node::~Node() {
}

void Node::setisVisited(bool visited) {
    isVisited = visited;
}

bool Node::getisVisited() {
    return isVisited;
}

void Node::setisObstacle(bool obstacle) {
    isObstacle = obstacle;
}

bool Node::getisObstacle() {
    return isObstacle;
}

void Node::setFcost(float fcost) {
    this->fcost = fcost;
}

float Node::getFcost() {
    return fcost;
}

void Node::setGcost(float gcost) {
    this->gcost = gcost;
}

float Node::getGcost() {
    return gcost;
}

void Node::setHcost(float hcost) {
    this->hcost = hcost;
}

float Node::getHcost() {
    return hcost;
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

Node* Node::getParent() {
    return parent;
}

void Node::setVecNeighbours(vector<Node*> VecNeighbours) {
    this->VecNeighbours = VecNeighbours;
}

vector<Node*> Node::getVecNeighbours() {
    return VecNeighbours;
}

void Node::setNodepos(Vec2 pos) {
    Nodepos = pos;
}

Vec2 Node::getNodepos() {
    return Nodepos;
}