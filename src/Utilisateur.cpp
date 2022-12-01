#include "Utilisateur.h"
#include <stdlib.h>
#include <time.h>

Utilisateur::Utilisateur()
{
    id = 0;
    name = "default";
    surname = "default";
    maxPrice = 0;
    ParkTime = 0;
    Age = 0;
    AlreadySpawned = false;
}

Utilisateur::~Utilisateur()
{
}



Utilisateur::Utilisateur(double u_maxPrice, unsigned int u_id, string u_name, string u_surname, unsigned int u_Age, float u_parkTime)
{
    maxPrice = u_maxPrice;
    id = u_id;
    name = u_name;
    surname = u_surname;
    Age = u_Age;
    ParkTime = u_parkTime;
    AlreadySpawned = false;
}

double Utilisateur::getMaxPrice() const
{
    return maxPrice;
}

const unsigned int& Utilisateur::getId() const
{
    return id;
}

string Utilisateur::getName() const
{
    return name;
}

string Utilisateur::getSurname() const
{
    return surname;
}

unsigned int Utilisateur::getAge() const
{
    return Age;
}


void Utilisateur::setAge(unsigned int u_Age)
{
    Age = u_Age;
}


float Utilisateur::getParkTime() const
{
    return ParkTime;
}


void Utilisateur::setParkTime(float u_ParkTime)
{
    ParkTime = u_ParkTime;
}

void Utilisateur::testRegression()
{
    // Test de régression de la classe Utilisateur
    cout << "Test de régression de la classe Utilisateur" << endl;
    cout << "-----------------------------------------" << endl;

    // Test du constructeur par défaut
    cout << "Test du constructeur par défaut" << endl;
    Utilisateur u1;
    assert(u1.id == 0);
    assert(u1.maxPrice == 0);
    assert(u1.name == "default");
    assert(u1.ParkTime == 0);
    cout << "Test du constructeur par défaut OK" << endl;

    //test constructeur avec parametre
    cout << "Test constructeur avec parametre + setParkTime()" << endl;
    float parktime = 1.5;
    Utilisateur u2(2.54,34,"Zidane", "Zinedine", 45, 2);
    u2.setParkTime(parktime);
    assert(u2.id == 34);
    assert(u2.maxPrice == 2.54);
    assert(u2.name == "Zidane");
    assert(u2.ParkTime == parktime);
    cout << "Test constructeur avec parametre OK" << endl;

    Utilisateur u3(2,37,"Michel", "Dupont", 25, 2);
    cout<<u3.getParkTime()<<endl;
    
}