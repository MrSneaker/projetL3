#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "Utilisateur.h"
#include "vec2.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Environnement {
    private:
        vector<Voiture> voitures;
        vector<Parking> parkings;
        vector<Utilisateur> utilisateur;
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

        //! \brief Ajoute une voiture dans l'environnement
        //! \param v voiture à ajouter
        void addVoiture(Voiture v);
        
        void initUser();
        // Initialisation des voitures dans l'environnement en fonction du temps 
        void initVoitureInEnvironnement();








        void test_regresion();
};


#endif