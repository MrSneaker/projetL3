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

Vec2 Voiture::getTargetPosition()
{
    return TargetPosition;
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
    else if (position.x == TargetPosition.x && position.y == TargetPosition.y)
    {

        return true;
    }
    return false;
}

// Test de regression la classe Voiture
void Voiture::test_regresion(){

    std::cout << "Test de regression de la classe Voiture" << std::endl;

    // Test de la fonction MoveRight()
    std::cout << "Test de la fonction MoveRight()" << std::endl;
    position.x = 0;
    position.y = 0;
    vitesse = 1;
    MoveRight();
    if (position.x == 1 && position.y == 0)
    {
        std::cout << "Test de la fonction MoveRight() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction MoveRight() : NOT OK" << std::endl;
    }

    // Test de la fonction MoveLeft()
    std::cout << "Test de la fonction MoveLeft()" << std::endl;
    position.x = 0;
    position.y = 0;
    vitesse = 1;
    MoveLeft();
    if (position.x == -1 && position.y == 0)
    {
        std::cout << "Test de la fonction MoveLeft() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction MoveLeft() : NOT OK" << std::endl;
    }

    // Test de la fonction MoveUp()
    std::cout << "Test de la fonction MoveUp()" << std::endl;
    position.x = 0;
    position.y = 0;
    vitesse = 1;
    MoveUp();
    if (position.x == 0 && position.y == 1)
    {
        std::cout << "Test de la fonction MoveUp() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction MoveUp() : NOT OK" << std::endl;
    }

    // Test de la fonction MoveDown()
    std::cout << "Test de la fonction MoveDown()" << std::endl;
    position.x = 0;
    position.y = 0;
    vitesse = 1;
    MoveDown();
    if (position.x == 0 && position.y == -1)
    {
        std::cout << "Test de la fonction MoveDown() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction MoveDown() : NOT OK" << std::endl;
    }

    //test de la fonction set_position()
    std::cout << "Test de la fonction set_position()" << std::endl;
    position.x = 0;
    position.y = 0;
    Vec2 new_pos;
    new_pos.x = 3;
    new_pos.y = 5;
    set_position(new_pos);
    if (position.x == 3 && position.y == 5)
    {
        std::cout << "Test de la fonction set_position() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction set_position() : NOT OK" << std::endl;
    }

    // Test de la fonction get_position()
    std::cout << "Test de la fonction get_position()" << std::endl;
    Vec2 new_pos2 = {2,5};
    set_position(new_pos2);
    Vec2 pos = get_position();
    if (pos.x == 2 && pos.y == 5)
    {
        std::cout << "Test de la fonction get_position() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction get_position() : NOT OK" << std::endl;
    }

    // Test de la fonction setTargetPosition()
    std::cout << "Test de la fonction setTargetPosition()" << std::endl;
    TargetPosition.x = 0;
    TargetPosition.y = 0;
    Vec2 new_pos3;
    new_pos3.x = 3;
    new_pos3.y = 5;
    setTargetPosition(new_pos3);
    if (TargetPosition.x == 3 && TargetPosition.y == 5)
    {
        std::cout << "Test de la fonction setTargetPosition() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction setTargetPosition() : NOT OK" << std::endl;
    }

    // Test de la fonction getTargetPosition()
    std::cout << "Test de la fonction getTargetPosition()" << std::endl;
    Vec2 new_pos4 = {2,5};
    setTargetPosition(new_pos4);
    Vec2 pos2 = getTargetPosition();
    if (pos2.x == 2 && pos2.y == 5)
    {
        std::cout << "Test de la fonction getTargetPosition() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction getTargetPosition() : NOT OK" << std::endl;
    }

    // test de la fonction MoveToTargetPosition()
    std::cout << "Test de la fonction MoveToTargetPosition" << std::endl;
    position.x = 0;
    position.y = 0;
    TargetPosition.x = 3;
    TargetPosition.y = 5;
    vitesse = 1;
    std::cout<<TargetPosition.x<<std::endl;
    std::cout<<TargetPosition.y<<std::endl;
    while(MoveToTargetPosition() == false){

        std::cout<<"position.x = "<<position.x<<std::endl;
        std::cout<<"position.y = "<<position.y<<std::endl;
    }

    std::cout<<"fin - position.x = "<<position.x<<std::endl;
    std::cout<<"fin - position.y = "<<position.y<<std::endl;

    if (position.x == TargetPosition.x && position.y == TargetPosition.y)
    {
        std::cout << "Test de la fonction MoveToTargetPosition() : OK" << std::endl;
    }
    else
    {
        std::cout << "Test de la fonction MoveToTargetPosition() : NOT OK" << std::endl;
    }


    

}
