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
#include <thread>
#include <time.h>

using namespace std;

class Environnement {
    private:
        Vec2 position;
        float speed;
        
        //! \brief Fonction revoyant un nombre en deux valeurs
        //! \param min valeur minimale
        //! \param max valeur maximale
        int random(int min, int max); 
    public:
        vector<Voiture> voitures;
        vector<Parking> parkings;
        vector<Utilisateur> conducteurs;
        unsigned int Time;
        bool display;


        Environnement();
        ~Environnement();
        
        //! \brief Initialisation d'un utilisateur, puis ajout dans le tableau de conducteurs.
        void initUser();

        //! \brief Ajout d'une voiture avec un conducteur dans le tableau de voitures.
        void AddVoiture();

        //! \brief Boucle de jeu
        void Environnement_play();

        //! \brief Test de regression de la classe Environnement
        void test_regresion();
};


#endif