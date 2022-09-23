#include "Utilisateur.h"

Utilisateur::Utilisateur()
{
    id = 0;
    name = "default";
    maxPrice = 0;
}

Utilisateur::Utilisateur(float u_maxPrice, unsigned int u_id, string u_name)
{
    maxPrice = u_maxPrice;
    id = u_id;
    name = u_name;
}

float Utilisateur::getMaxPrice() const
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
