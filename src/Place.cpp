#include "Place.h"
#include <iostream>

Place::Place()
{
}

Place::Place(Vec2 p_pos, int p_indP)
{
    pos = p_pos;
    indP = p_indP;
    isTaken = false;
}

Place::~Place()
{
}

const Vec2& Place::getPos() const
{
    return pos;
}

const int& Place::getIndP() const
{
    return indP;
}

void Place::setIsTaken(bool new_isTaken)
{
    isTaken = new_isTaken;
}

const bool& Place::getIsTaken() const
{
    return isTaken;
}

void Place::test_regresion()
{
    std::cout << "test regression" << std::endl;

    Place p2(Vec2(1, 2), 3);

    std::cout << "p2.getPos().x = " << p2.getPos().x << std::endl;
    std::cout << "p2.getPos().y = " << p2.getPos().y << std::endl;
    std::cout << "p2.getIndP() = " << p2.getIndP() << std::endl;
    std::cout << "p2.getIsTaken() = " << p2.getIsTaken() << std::endl;

    p2.setIsTaken(true);

    std::cout << "p2.getIsTaken() = " << p2.getIsTaken() << std::endl;

}

