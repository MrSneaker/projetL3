#include "Place.h"
#include <iostream>

Place::Place()
{
}

Place::Place(Vec2 p_pos, int p_indP, bool p_isTaken)
{
    pos = p_pos;
    indP = p_indP;
    isTaken = p_isTaken;
}

Place::~Place()
{
}

Vec2 Place::getPos() const
{
    return pos;
}

int Place::getIndP() const
{
    return indP;
}