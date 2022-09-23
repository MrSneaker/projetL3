#ifndef _PARKING_H
#define _PARKING_H

#include "Place.h"
#include "vec2.h"
#include <vector>

using namespace std;

class Parking {

    private :

        Place* placesTab;

        int nbPlaces;

        int nbAvailablePlaces;

        float minPrice;

        float maxPrice;

        bool isFull;

        vector<int>* conversationsTab;
        // Pas encore sûrs qu'on va l'utiliser

        vector<int>* usersTab;
        // Pas encore sûrs qu'on "stocke" les utilisateurs de cette manière

        int nbVisits;
        // Le parking va, toutes les 2h dans la simulation (par ex), calculer son nombre de
        // réussites par rapport à son nombre de négociations. Si les négociations
        // ont souvent abouti à un refus de l'utilisateur de se garer dans le parking en question,
        // (i.e. si le rapport nb de réussites/nb de négociations est au-dessous d'un certain seuil
        // qu'on aura fixé [voir plus tard si on fait plus dynamique qu'un simple seuil fixé]),
        // cela veut dire que les prix du parking sont trop hauts, et ce dernier va donc baisser
        // ses tarifs en moyenne pour obtenir globalement plus de voitures.

        vector<int>* nbVisitsTab;
        // Pas encore sûrs qu'on "stocke" ces données sur les venues des utilisateurs de cette manière

        Vec2 pos;


    public:

        // CONSTRUCTEUR et DESTRUCTEUR

        Parking (Vec2 position, int numberOfPlaces, float minimumPrice, float maximumPrice);
        ~Parking ();



        // ACCESSEURS

        Place* getPlacesTab () const;
        // Utile ?

        int getNbPlaces () const;

        int getNbAvailablePlaces () const;

        int getMinPrice () const;

        int getMaxPrice () const;

        bool isFull () const;

        vector<int>* getConversationsTab () const;

        vector<int>* getUsersTab () const;

        int getNbVisits () const;

        vector<int>* getNbVisitesTab () const;

        Vec2 getPos () const;



        // MUTATEURS

        void setPlacesTab (); // !!!!

        void setNbAvailablePlaces (int numberOfAvailablePlaces);

        void setMinPrice (float minimumPrice);

        void setMaxPrice (float maximumPrice);

        void setIsFull (bool filledToCapacity);

        void setConversationsTab (); // !!!!

        void setUsersTab (); // !!!!

        void incrementNbVisits ();

        void incrementNbVisitsTab (); // !!!!

};

#endif
