#ifndef _PARKING_H
#define _PARKING_H

#include "Place.h"
#include "vec2.h"
#include <vector>

using namespace std;

class Parking {

    private :

        Place placesTab [];

        int nbPlaces;

        int nbAvailablePlaces;

        float MinPrice;

        float MaxPrice;

        bool isFull;

        vector<int> ConversationsTab;
        // Pas encore sûrs qu'on va l'utiliser

        vector<int> usersTab;
        // Pas encore sûrs qu'on "stocke" les utilisateurs de cette manière

        int nbVisits;
        // Le parking va, toutes les 2h dans la simulation (par ex), calculer son nombre de
        // réussites par rapport à son nombre de négociations. Si les négociations
        // ont souvent abouti à un refus de l'utilisateur de se garer dans le parking en question,
        // (i.e. si le rapport nb de réussites/nb de négociations est au-dessous d'un certain seuil
        // qu'on aura fixé [voir plus tard si on fait plus dynamique qu'un simple seuil fixé]),
        // cela veut dire que les prix du parking sont trop hauts, et ce dernier va donc baisser
        // ses tarifs en moyenne pour obtenir globalement plus de voitures.

        vector<int> nbVisitesTab;
        // Pas encore sûrs qu'on "stocke" ces données sur les venues des utilisateurs de cette manière

        vec2 pos;

};

#endif
