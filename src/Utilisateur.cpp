#include "Utilisateur.h"

Utilisateur::Utilisateur()
{
    id = 0;
    name = "default";
    maxPrice = 0;
    ParkTime = 0;
    
}

Utilisateur::~Utilisateur()
{
}

Utilisateur::Utilisateur(double u_maxPrice, unsigned int u_id, string u_name)
{
    maxPrice = u_maxPrice;
    id = u_id;
    name = u_name;
    ParkTime = randomParkTime();
}

double Utilisateur::getMaxPrice() const
{
    return maxPrice;
}

unsigned int Utilisateur::getId() const
{
    return id;
}

float Utilisateur::getParkTime() const
{
    return ParkTime;
}

string Utilisateur::getName() const
{
    return name;
}

void Utilisateur::setParkTime(float u_ParkTime)
{
    ParkTime = u_ParkTime;
}

float Utilisateur::randomParkTime()
{
    float new_Parktime = 0;
    // On simule un pourcentage qui définie le temps de stationnement de l'utilisateur.
    float res = rand() % 100;
    
    // Si le pourcentage est inferieur à 10, on met le temps de stationnement entre 15 minutes et 1 heure
    if (res < 10)
    {
        new_Parktime = (rand() % 45 + 15);
        new_Parktime = new_Parktime / 60;
    }
    // Si le pourcentage est inferieur à 50 et supperieur a 10, on met le temps de stationnement entre 1 et 5 heures
    else if (res < 50)
    {
        new_Parktime = (rand() % 240 + 60)/60;
    }
    // Si le pourcentage est supperieur a 50, on met le temps de stationnement entre 5 et 12 heures
    else
    {
        new_Parktime = (rand() % 420 + 300)/60;
    }

    return new_Parktime;
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
    float parktime = randomParkTime();
    Utilisateur u2(2.54,34,"Zidane");
    u2.setParkTime(parktime);
    assert(u2.id == 34);
    assert(u2.maxPrice == 2.54);
    assert(u2.name == "Zidane");
    assert(u2.ParkTime == parktime);
    cout << "Test constructeur avec parametre OK" << endl;

    Utilisateur u3(2,37,"Michel");
    cout<<u3.getParkTime()<<endl;
    
}