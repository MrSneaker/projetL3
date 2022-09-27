#include "Utilisateur.h"

Utilisateur::Utilisateur()
{
    id = 0;
    name = "default";
    maxPrice = 0;
}

Utilisateur::~Utilisateur()
{
}

Utilisateur::Utilisateur(double u_maxPrice, unsigned int u_id, string u_name)
{
    maxPrice = u_maxPrice;
    id = u_id;
    name = u_name;
}

double Utilisateur::getMaxPrice() const
{
    return maxPrice;
}

unsigned int Utilisateur::getId() const
{
    return id;
}

string Utilisateur::getName() const
{
    return name;
}

void Utilisateur::testRegression()
{
    Utilisateur u1;
    assert(u1.id == 0);
    assert(u1.maxPrice == 0);
    assert(u1.name == "default");
    cout<<"test constructeur OK"<<endl;

    Utilisateur u2(2.54,34,"Zidane");
    assert(u2.id == 34);
    assert(u2.maxPrice == 2.54);
    assert(u2.name == "Zidane");
    cout<<"test constructeur à param OK"<<endl;
}