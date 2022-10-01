#include "Parking.h"

// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float startPrice, int DIMX, int DIMY) :
    pos(position), nbPlaces(numberOfPlaces), minPrice(minimumPrice),
    startingPrice(startPrice), nbAvailablePlaces (numberOfPlaces),
    isFull (false), nbTotalVisits (0), DIMX (DIMX), DIMY(DIMY) {
    
        initPlace(1, 1, position.x+1, position.y+1);

    }

Parking::Parking()
{
}

Parking::~Parking()
{
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

 int Parking::getNbAvailablePlaces () const 
 {
    return nbAvailablePlaces;
 }

int Parking::getMinPrice() const
{
    return minPrice;
}

int Parking::getStartingPrice() const
{
    return startingPrice;
}

int Parking::getDIMX() const
{
    return DIMX;
}

int Parking::getDIMY() const
{
    return DIMY;
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

    nbPlCol = DIMX/2;//(DIMX-2)*(DIMY-2) / nbPlaces;
    nbPlLigne = DIMY/4; //On divise par 4 car les places font 2 de hauteur et qu'il y'en a 1 toutes les 2 lignes 
    //On en repalera dans la semaine Mateo mais dcp la les places sont constuite en fonction de la taille du parking pour le remplir en entier 
    //Et non pas du nombre de place
 

    for (int i = 0; i < nbPlLigne; i++)
    {
        for (int j = 0; j < nbPlCol; j++)
        {
            Place p = Place(Vec2(PcornerX + j*2, PcornerY + i*3+i), indPl, false);
            placesTab.push_back(p);
            indPl++;
        }
    }
    
}

void Parking::testRegression()
{
    Parking p1(Vec2(1, 1), 100, 0.5, 1.5,43,38);
    p1.initPlace(14, 7, 2, 2);
    cout<<p1.placesTab.size()<<endl;
    assert(p1.placesTab.size() == 98);
    for (int i = 0; i < p1.placesTab.size(); i++)
    {
        cout << p1.placesTab.at(i).getPos().x << endl;
        cout << p1.placesTab.at(i).getPos().y << endl;
        cout << p1.placesTab.at(i).getIndP() << endl;
        cout << endl;
    }
}