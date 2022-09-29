#include "Parking.h"

// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float startPrice) : pos(position), nbPlaces(numberOfPlaces), minPrice(minimumPrice), startingPrice(startPrice) {}

Parking::~Parking()
{
    nbPlaces = -1;
    minPrice = -2;
    startingPrice = -3;
}

// ACCESSEURS

vector<Place> Parking::getPlacesTab() const
{
     return placesTab;
}

int Parking::getNbPlaces() const
{
    return nbPlaces;
}

// int Parking::getNbAvailablePlaces () const {
//     return nbAvailablePlaces;
// }

int Parking::getMinPrice() const
{
    return minPrice;
}

int Parking::getStartingPrice() const
{
    return startingPrice;
}

bool Parking::IsFull()
{
    if (nbAvailablePlaces == 0)
    {
        isFull = true;
    }
    else
    {
        isFull = false;
    }
    return isFull;
}

/*
vector<int>* Parking::getConversationsTab () const {
    return conversationsTab;
}*/

vector<Utilisateur> *Parking::getUsersTab() const
{
    return usersTab;
}

int Parking::getNbVisits() const
{
    return nbVisits;
}

vector<int> Parking::getNbVisitesTab() const
{
    return nbVisitsTab;
}

Vec2 Parking::getPos() const
{
    return pos;
}

// MUTATEURS
void Parking::decrementNbAvailablePlaces()
{
    nbAvailablePlaces--;
    IsFull();
}

void Parking::incrementNbAvailablePlaces()
{
    nbAvailablePlaces++;
    IsFull();
}

void Parking::setMinPrice(float minimumPrice)
{
    minPrice = minimumPrice;
}

void Parking::setStartingPrice(float startPrice)
{

    startingPrice = startPrice;
}

void Parking::setConversationsTab()
{
}

void Parking::setUsersTab()
{
}

void Parking::incrementNbVisits()
{

    nbVisits++;
}

void Parking::incrementNbVisitsTab()
{
}

void Parking::initPlace()
{
    for(int i = 0; i<nbPlaces;i++)
    {
        //on  veut dix places par ligne et fuck ben.
        //for(int j = 0; j<10; j++)
        //Vec2 tmp;
        //tmp.x = pos.x 
        //Place(Vec2(pos.x,pos.y))
    }
}