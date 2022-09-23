#include "Parking.h"


// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking (Vec2 position, int numberOfPlaces, float minimumPrice, float maximumPrice) :
pos (position), nbPlaces (numberOfPlaces), minPrice (minimumPrice), maxPrice (maximumPrice) {}

Parking::~Parking () {
    nbPlaces = -1;
    minPrice = -2;
    maxPrice = -3;
}



// ACCESSEURS


Place* Parking::getPlacesTab () const {
    return placesTab;
}

int Parking::getNbPlaces () const {
    return nbPlaces;
}

int Parking::getNbAvailablePlaces () const {
    return nbAvailablePlaces;
}

int Parking::getMinPrice () const {
    return minPrice;
}

int Parking::getMaxPrice () const {
    return maxPrice;
}

bool Parking::isFull () const {
    return isFull;
}

vector<int>* Parking::getConversationsTab () const {
    return conversationsTab;
}

vector<int>* Parking::getUsersTab () const {
    return usersTab;
}

int Parking::getNbVisits () const {
    return nbVisits;
}

vector<int>* Parking::getNbVisitesTab () const {
    return nbVisitsTab;
}

Vec2 Parking::getPos () const {
    return pos;
}





// MUTATEURS



void Parking::setPlacesTab () {


}


void Parking::decrementNbAvailablePlaces () {

    nbAvailablePlaces--;
    if (nbAvailablePlaces == 0) {
        setIsFull (false);
    }

}


void Parking::incrementNbAvailablePlaces () {

    nbAvailablePlaces++;
    if (nbAvailablePlaces == 1) {
        setIsFull (true);
    }

}


void Parking::setMinPrice (float minimumPrice) {

    minPrice = minimumPrice;

}


void Parking::setMaxPrice (float maximumPrice) {

    maxPrice = maximumPrice;

}


void Parking::setIsFull (bool filledToCapacity) {

    isFull = filledToCapacity;

}


void Parking::setConversationsTab () {

}


void Parking::setUsersTab () {

}


void Parking::incrementNbVisits () {

    nbVisits++;


}

void Parking::incrementNbVisitsTab () {

    

}