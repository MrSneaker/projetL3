#include "Parking.h"

// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float startPrice) :
    pos(position), nbPlaces(numberOfPlaces), minPrice(minimumPrice),
    startingPrice(startPrice), nbAvailablePlaces (numberOfPlaces),
    isFull (false), nbTotalVisits (0) {

        //initPlace();

    }

Parking::Parking()
{

}

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


vector<int> Parking::getConversationsTab () const {
    return conversationsTab;
}

vector<Utilisateur*> Parking::getUsersTab() const
{
    return usersTab;
}

int Parking::getNbTotalVisits() const
{
    return nbTotalVisits;
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

void Parking::setUsersTab(Utilisateur* unUtilisateur)
{
}

void Parking::incrementNbTotalVisits()
{

    nbTotalVisits++;
}



void Parking::incrementNbVisitsTab(Utilisateur* unUtilisateur)
{

    // Ajouter bout de code pour incrémenter le nombre de visites de l'utilisateur

    incrementNbTotalVisits();
}




void Parking::initPlace(int nbPlLigne, int nbPlCol, int PcornerX, int PcornerY)
{
    int indPl = 1;
    for (int i = 0; i < nbPlCol; i++)
    {
        // on  veut dix places par ligne et fuck ben.
        for (int j = 0; j < nbPlLigne; j++)
        {
            Place p = Place(Vec2(PcornerX+j,PcornerY+i),indPl,false);
            placesTab.push_back(p);
            indPl++;
        }
    }
}






void Parking::testRegression()
{
    Parking p1(Vec2(1, 1), 200, 0.5, 1.5);
    p1.initPlace(10,20,10,10);
    assert(p1.placesTab.size()==200);
    for(int i = 0;i<p1.nbPlaces;i++)
    {
        cout<<p1.placesTab.at(i).getPos().x<<endl;
        cout<<p1.placesTab.at(i).getPos().y<<endl;
        cout<<p1.placesTab.at(i).getIndP()<<endl;
        cout<<endl;
    }

}