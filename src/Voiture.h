#ifndef _VOITURE_H
#define _VOITURE_H 

#include "vec2.h"
#include "Utilisateur.h"
#include <assert.h>

class Voiture 
{

    private:

        Vec2 position; // Position (x,y) de la voiture
        Vec2 TargetPosition; // Position (x,y) de la cible (parking / place / sortie)
        float speed; // speed de la voiture
        //float batterie; // batterie de la voiture
        //Couleur couleur; // Couleur de la voiture

    
    public:
        Utilisateur User; // Utilisateur de la voiture
        bool Is_in = false; // true si la voiture entre dans le parking
        bool Is_parked = false; // true si la voiture est garée dans le parking



    Voiture();

    //constructeur de voiture avec un utilisateur
    Voiture(Utilisateur User);

    ~Voiture();

    //! \brief Déplace la voiture vers la droite
    void MoveRight();

    //! \brief Déplace la voiture vers la gauche
    void MoveLeft();

    //! \brief Déplace la voiture vers le haut
    void MoveUp();

    //! \brief Déplace la voiture vers le bas
    void MoveDown();

    //! \brief Déplace la voiture vers la position de la cible (parking / place / sortie)
    //! \return true si la voiture est arrivée à la position de la cible (parking / place / sortie)
    bool MoveToTargetPosition();

    //! \brief Modifie la position de la cible (parking / place / sortie)
    void setTargetPosition(Vec2 new_pos);

    //! \brief Renvoie la position de la cible (parking / place / sortie)
    Vec2 getTargetPosition();

    //! \brief Renvoie la position de la voiture
    Vec2 get_position();

    //! \brief Modifie la position de la voiture
    //! \param new_pos nouvelle position de la voiture
    void set_position(Vec2 new_pos);

    //! \brief vérifie qu'un prix donné est acceptable ou non, selon un intervalle arbitraire. Renvoie un booléen.
    //! \param price prix à vérifier
    bool isPriceOk(double price, Utilisateur User);

    //! \brief Affiche les Infos du conducteur
    void UserGetInfos();

    //! \brief Test de regression la classe Voiture
    void test_regresion();

};


#endif  