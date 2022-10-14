#ifndef _VOITURE_H
#define _VOITURE_H 

#include "vec2.h"
#include "Utilisateur.h"
#include <assert.h>
#include <vector>
#include <mutex>
#include "Message.h"

class Voiture 
{

    private:

        Vec2 position; // Position (x,y) de la voiture
        Vec2 TargetPosition; // Position (x,y) de la cible (parking / place / sortie)
        float speed; // speed de la voiture
        int angle; // angle de la voiture
        bool Is_in; // true si la voiture entre dans le parking
        bool Is_parked; // true si la voiture est garée dans le parking
        int parking; // numéro du parking dans lequel la voiture est garée
        int place; // numéro de la place dans lequel la voiture est garée
        float width; // largeur de la voiture 
        float height; // hauteur de la voiture
        //float batterie; // batterie de la voiture
        //Couleur couleur; // Couleur de la voiture

    
    public:
        Utilisateur User; // Utilisateur de la voiture



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





    //! \brief La voiture lit le message reçu (donné en paramètre) s'il y en a un
    //! \brief (s'il n'y en a pas, le pointeur est nul),
    //! \brief et en crée un nouveau (s'il s'agit d'une réponse, les données du nouveau
    //! \brief message sont initialisées en fonction des données contenues dans le message reçu).
    Message managingConversation (Message * aMessage) const;




    //! \brief Modifie la position de la cible (parking / place / sortie)
    void setTargetPosition(Vec2 new_pos);

    //! \brief Modifie l'angle de la voiture
    //! \param new_angle : nouvel angle de la voiture
    void setAngle(int new_angle);

    //! \brief Renvoie la position de la cible (parking / place / sortie)
    Vec2 getTargetPosition();

    //! \brief Renvoie la position de la voiture
    Vec2 get_position();

    //! \brief Renvoie l'angle de la voiture
    int getAngle();

    //! \brief Modifie la position de la voiture
    //! \param new_pos nouvelle position de la voiture
    void set_position(Vec2 new_pos);

    //! \brief vérifie qu'un prix donné est acceptable ou non, selon un intervalle arbitraire. Renvoie un booléen.
    //! \param price prix à vérifier
    bool isPriceOk(double price, Utilisateur User) const;

    //! \brief Affiche les Infos du conducteur
    void UserGetInfos();

    //! \brief renvoie la vitesse de la voiture
    float getSpeed();

    //! \brief Modifie la vitesse de la voiture
    void setSpeed(float new_speed);

    
    bool getIs_in();

    void setIs_in(bool new_Is_in);

    void setIs_parked(bool new_Is_parked);

    bool getIs_parked();

    void setParking(int new_parking);

    int getParking();

    void setPlace(int new_place);

    int getPlace();

    void setwidth(int new_width);

    int getwidth();

    void setheight(int new_height);

    int getheight();

    //! \brief Test de regression la classe Voiture
    void test_regresion();

};


#endif  