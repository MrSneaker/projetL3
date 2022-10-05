#include "Voiture.h"

#include <iostream>

// Constructeur de la classe Voiture
Voiture::Voiture()
{
}

Voiture::Voiture(Utilisateur U)
{
    User = U;
    speed = 2;
    Is_in = false;
    Is_parked = false;
    parking = 0;
    place = 0;
    width = 1;
    height = 2;
    position = Vec2(0, 0);
}

// Destructeur de la classe Voiture
Voiture::~Voiture()
{
}

// Déplace la voiture vers la droite
void Voiture::MoveRight()
{
    position.x += speed;
    setAngle(270);
}

// Déplace la voiture vers la gauche
void Voiture::MoveLeft()
{
    position.x -= speed;
    setAngle(90);
}

// Déplace la voiture vers le haut
void Voiture::MoveUp()
{
    position.y += speed;
    setAngle(0);
}

// Déplace la voiture vers le bas
void Voiture::MoveDown()
{
    position.y -= speed;
    setAngle(180);
}

void Voiture::setAngle(int new_angle)
{
    angle = new_angle;
}

int Voiture::getAngle()
{
    return angle;
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

// // Déplace la voiture vers la position de la cible (parking / place / sortie)
// // On changer la position de la cible quand la voiture entre dans le parking
// // Nouvelle position cible = position place de parking etc.
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

bool Voiture::isPriceOk(double price, Utilisateur User)
{
    double u_price = User.getMaxPrice();
    bool ok = (price == u_price) || (price <= u_price + 0.5) || (price >= u_price - 0.5);
    if (ok)
        return true;
    else
        return false;
}

void Voiture::UserGetInfos()
{
    // Donne les infos du conducteur
    std::cout << "Nom : " << User.getName() << std::endl;
    std::cout << "ID : " << User.getId() << std::endl;
    std::cout << "Temps de stationnement : " << User.getParkTime() << std::endl;
    std::cout << "Prix max : " << User.getMaxPrice() << std::endl;
}

float Voiture::getSpeed()
{
    return speed;
}

void Voiture::setSpeed(float new_speed)
{
    speed = new_speed;
}

void Voiture::setIs_in(bool new_is_in)
{
    Is_in = new_is_in;
}

bool Voiture::getIs_in()
{
    return Is_in;
}

void Voiture::setIs_parked(bool new_is_parked)
{
    Is_parked = new_is_parked;
}

bool Voiture::getIs_parked()
{
    return Is_parked;
}

void Voiture::setParking(int new_parking)
{
    parking = new_parking;
}

int Voiture::getParking()
{
    return parking;
}

// set place
void Voiture::setPlace(int new_place)
{
    place = new_place;
}

// get place
int Voiture::getPlace()
{
    return place;
}

// set Width
void Voiture::setwidth(int new_width)
{
    width = new_width;
}

// get Width
int Voiture::getwidth()
{
    return width;
}

// set Height
void Voiture::setheight(int new_height)
{
    height = new_height;
}

// get Height
int Voiture::getheight()
{
    return height;
}

// -----------------------------------------------------------------------------------------------
// Test de regression la classe Voiture
void Voiture::test_regresion()
{

    std::cout << "Test de regression de la classe Voiture" << std::endl;

    // test constructeur avec parametre
    std::cout << "Test constructeur avec parametre" << std::endl;
    Utilisateur u1(2.54, 34, "Zidane");
    Voiture v1(u1);
    v1.User.setParkTime(2);
    assert(v1.User.getId() == 34);
    assert(v1.User.getMaxPrice() == 2.54);
    assert(v1.User.getName() == "Zidane");
    assert(v1.User.getParkTime() == 2);
    std::cout << "Test constructeur avec parametre OK" << std::endl;

    // Test de la fonction MoveRight()
    std::cout << "Test de la fonction MoveRight()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveRight();
    assert(position.x == 1 && position.y == 0);
    std::cout << "Test de la fonction MoveRight() OK" << std::endl;

    // Test de la fonction MoveLeft()
    std::cout << "Test de la fonction MoveLeft()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveLeft();
    assert(position.x == -1 && position.y == 0);
    std::cout << "Test de la fonction MoveLeft() OK" << std::endl;

    // Test de la fonction MoveUp()
    std::cout << "Test de la fonction MoveUp()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveUp();
    assert(position.x == 0 && position.y == 1);
    std::cout << "Test de la fonction MoveUp() OK" << std::endl;

    // Test de la fonction MoveDown()
    std::cout << "Test de la fonction MoveDown()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveDown();
    assert(position.x == 0 && position.y == -1);
    std::cout << "Test de la fonction MoveDown() OK" << std::endl;

    // test de la fonction set_position()
    std::cout << "Test de la fonction set_position()" << std::endl;
    position.x = 0;
    position.y = 0;
    Vec2 new_pos;
    new_pos.x = 3;
    new_pos.y = 5;
    set_position(new_pos);
    assert(position.x == 3 && position.y == 5);
    std::cout << "Test de la fonction set_position() OK" << std::endl;

    // Test de la fonction get_position()
    std::cout << "Test de la fonction get_position()" << std::endl;
    Vec2 new_pos2 = {2, 5};
    set_position(new_pos2);
    Vec2 pos = get_position();
    assert(pos.x == 2 && pos.y == 5);
    std::cout << "Test de la fonction get_position() OK" << std::endl;

    // Test de la fonction setTargetPosition()
    std::cout << "Test de la fonction setTargetPosition()" << std::endl;
    TargetPosition.x = 0;
    TargetPosition.y = 0;
    Vec2 new_pos3;
    new_pos3.x = 3;
    new_pos3.y = 5;
    setTargetPosition(new_pos3);
    assert(TargetPosition.x == 3 && TargetPosition.y == 5);
    std::cout << "Test de la fonction setTargetPosition() OK" << std::endl;

    // Test de la fonction getTargetPosition()
    std::cout << "Test de la fonction getTargetPosition()" << std::endl;
    Vec2 new_pos4 = {2, 5};
    setTargetPosition(new_pos4);
    Vec2 pos2 = getTargetPosition();
    assert(pos2.x == 2 && pos2.y == 5);
    std::cout << "Test de la fonction getTargetPosition() OK" << std::endl;

    // test de la fonction MoveToTargetPosition()
    std::cout << "Test de la fonction MoveToTargetPosition" << std::endl;
    position.x = 0;
    position.y = 0;
    TargetPosition.x = 3;
    TargetPosition.y = 5;
    speed = 1;
    while (MoveToTargetPosition() == false)
    {
        continue;
    }
    assert(position.x == 3 && position.y == 5);
    std::cout << "Test de la fonction MoveToTargetPosition() OK" << std::endl;

    // Test de la fonction isPriceOk()
    std::cout << "Test de la fonction isPriceOk()" << std::endl;
    Utilisateur u(2.54, 0, "lol");
    Voiture v2(u);
    bool test = isPriceOk(3, User);
    assert(test == true);
    std::cout << "Test de la fonction isPriceOk() OK" << std::endl;

    // test de la fonction setIs_in()
    std::cout << "Test de la fonction setIs_in()" << std::endl;
    setIs_in(true);
    assert(getIs_in() == true);
    std::cout << "Test de la fonction setIs_in() OK" << std::endl;

    // test de la fonction getIs_in()
    std::cout << "Test de la fonction getIs_in()" << std::endl;
    setIs_in(false);
    assert(getIs_in() == false);
    std::cout << "Test de la fonction getIs_in() OK" << std::endl;
}
