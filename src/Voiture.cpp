#include "Voiture.h"

#include <iostream>

// Constructeur de la classe Voiture
Voiture::Voiture()
{
}

// Destructeur de la classe Voiture
Voiture::~Voiture()
{
}

// Déplace la voiture vers la droite
void Voiture::MoveRight()
{
    position.x += vitesse;
}

// Déplace la voiture vers la gauche
void Voiture::MoveLeft()
{
    position.x -= vitesse;
}

// Déplace la voiture vers le haut
void Voiture::MoveUp()
{
    position.y += vitesse;
}

// Déplace la voiture vers le bas
void Voiture::MoveDown()
{
    position.y -= vitesse;
}

// Renvoie la position (x;y) de la voiture
Vec2 Voiture::get_position()
{
    return position;
}

// Modifie la position (x;y) de la voiture
void Voiture::set_position(Vec2 new_pos)
{
    position = new_pos;
}

// Modifie la position de la cible (parking / place / sortie)
void Voiture::setTargetPosition(Vec2 new_pos)
{
    TargetPosition = new_pos;
}

// Déplace la voiture vers la position de la cible (parking / place / sortie)
// On changer la position de la cible quand la voiture entre dans le parking
// Nouvelle position cible = position place de parking etc.
bool Voiture::MoveToTargetPosition()
{

    // Si la voiture est au dessus de la cible
    if (position.y > TargetPosition.y)
    {

        MoveDown();
        if (position.y < TargetPosition.y)
        {

            position.y = TargetPosition.y;
        }
    }
    // Si la voiture est au dessous de la cible
    else if (position.y < TargetPosition.y)
    {

        MoveUp();
        if (position.y > TargetPosition.y)
        {

            position.y = TargetPosition.y;
        }
    }
    // Si la voiture est à gauche de la cible
    if (position.x < TargetPosition.x)
    {

        MoveRight();
        if (position.x > TargetPosition.x)
        {

            position.x = TargetPosition.x;
        }
    }
    // Si la voiture est à droite de la cible
    else if (position.x > TargetPosition.x)
    {

        MoveLeft();
        if (position.x < TargetPosition.x)
        {

            position.x = TargetPosition.x;
        }
    }
    // Si la voiture est à la position cible
    if (position.x == TargetPosition.x && position.y == TargetPosition.y)
    {

        return true;
    }
    return false;
}
