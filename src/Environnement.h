#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Place.h"
#include "vec2.h"
#include <vector>
#include <iostream>

using namespace std;

class Environnement {
    private:
        vector<Voiture> voitures;
        vector<Parking> parkings;
        vector<Utilisateur> Conducteur;
        Vec2 position;
        float speed;
        float batterie;
        unsigned int time;
    public:
        Environnement();
        ~Environnement();

        //! \brief Ajoute une voiture dans l'environnement
        //! \param v voiture à ajouter
        void addVoiture(Voiture v);








        void test_regresion();
};


#endif