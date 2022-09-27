#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "vec2.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>

using namespace std;

class Environnement {
    private:
        vector<Voiture> voitures;
        vector<Parking> parkings;
        vector<Utilisateur> utilisateur;
        Vec2 position;
        float speed;
        float batterie;
        
        //! \brief Fonction revoyant un nombre en deux valeurs
        //! \param min valeur minimale
        //! \param max valeur maximale
        int random(int min, int max); 
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
        
        //! \brief Initialisation d'un utilisateur, puis ajout dans le tableau de conducteurs.
        void initUser();

        // Initialisation des voitures dans l'environnement en fonction du temps 
        void initVoitureInEnvironnement();








        void test_regresion();
};


#endif