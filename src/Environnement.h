#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "vec2.h"
#include <vector>
#include <iostream>

using namespace std;

class Environnement {
    private:
        Vec2 position;
        float speed;
        float batterie;
    public:
        vector<Voiture> voitures;
        vector<Parking> parkings;
        vector<Utilisateur> Conducteur;
        unsigned int Time;
        Environnement();
        ~Environnement();

        // Initialisation des voitures dans l'environnement en fonction du temps 
        void initVoitureInEnvironnement();








        void test_regresion();
};


#endif