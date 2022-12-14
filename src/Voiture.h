#ifndef _VOITURE_H
#define _VOITURE_H

#include "vec2.h"
#include "Utilisateur.h"
#include "Node.h"
#include <assert.h>
#include <vector>
#include <mutex>
#include "Message.h"

class Voiture
{

private:
    Vec2 position;       // Position (x,y) de la voiture
    Vec2 TargetPosition; // Position (x,y) de la cible (parking / place / sortie)

    bool Is_in;       // true si la voiture entre dans le parking
    bool Is_parked;   // true si la voiture est garée dans le parking
    bool Is_pathfind; // true si la voiture a trouvé un chemin

    int speed;          // speed de la voiture
    int angle;          // angle de la voiture
    int parking;        // numéro du parking dans lequel la voiture est garée
    int place;          // numéro de la place dans lequel la voiture est garée
    int nbFinishedConv; // nombre de conversations finies par voiture.
    int width;          // largeur de la voiture
    int height;         // hauteur de la voiture
    int CarColor;       // couleur de la voiture

    vector<Node *> pathTab; // tableau des noeuds du chemin

public:
    Utilisateur User;        // Utilisateur de la voiture
    vector<Node *> nodes;    // tableau des noeuds
    vector<Node *> openList; // tableau des noeuds ouverts
    bool decrement;          // booléen pour décrémenter le nombre de places libres 1 seule fois par voiture
    bool reachGoal;          // true si la voiture a atteint sa cible
    bool isMoving;
    bool ChangeTrajToExit;   // booléen pour changer la trajectoire de la voiture vers la sortie
    int indice;              // indice de la voiture dans le tableau de voiture
    int Exit;                // indice de la sortie
    float startTimer;        // temps t ou la voiture et apparu dans la simulation

    //! \brief Constructeur de la classe Voiture
    Voiture();

    //! \brief Constructeur de Voiture avec un Utilisateur
    //! \param User : Utilisateur de la voiture
    Voiture(Utilisateur User);

    //! \brief Destructor de la classe Voiture
    ~Voiture();

    //---------------------------- Getter + Setter ---------------------------------

    //! \brief Setter de la couleur de la voiture
    //! \param new_CarColor : couleur de la voiture
    void setCarColor(int new_CarColor);

    //! \brief Getter de la couleur de la voiture
    //! \return int : couleur de la voiture
    const int &getCarColor() const;

    //! \brief Modifie la position de la cible (parking / place / sortie)
    //! \param new_pos : nouvelle position de la cible (parking / place / sortie)
    void setTargetPosition(Vec2 new_pos);

    //! \brief Getter de la position de la cible (parking / place / sortie)
    //! \return Vec2 : position de la cible (parking / place / sortie)
    const Vec2 &getTargetPosition() const;

    //! \brief Modifie l'angle de la voiture
    //! \param new_angle : nouvel angle de la voiture
    void setAngle(int new_angle);

    //! \brief Getter de l'angle de la voiture
    //! \return int : angle de la voiture
    const int &getAngle() const;

    //! \brief Modifie la position de la voiture
    //! \param new_pos nouvelle position de la voiture
    void set_position(Vec2 new_pos);

    //! \brief Getter de la position de la voiture
    //! \return Vec2 : position de la voiture
    const Vec2 &get_position() const;

    //! \brief Modifie la vitesse de la voiture
    //! \param new_speed nouvelle vitesse de la voiture
    void setSpeed(int new_speed);

    //! \brief Getter de la vitesse de la voiture
    //! \return int : vitesse de la voiture
    const int &getSpeed() const;

    //! \brief Getter du nombre de conversations finies
    //! \return int : nombre de conversations finies
    const int &getNbFinishedConv() const;

    //! \brief Mofifie le booléen qui indique si la voiture est dans une place
    //! \param new_Is_in : nouvelle valeur du booléen
    void setIs_in(bool new_Is_in);

    //! \brief Getter du booléen qui indique si la voiture est dans une place
    //! \return bool : valeur du booléen
    const bool &getIs_in() const;

    //! \brief Modifier le booléen qui indique si la voiture est garée
    //! \param new_Is_parked : nouvelle valeur du booléen
    void setIs_parked(bool new_Is_parked);

    //! \brief Getter du booléen qui indique si la voiture est garée
    //! \return bool : valeur du booléen
    const bool &getIs_parked() const;

    //! \brief Modifier le booléen qui indique si la voiture à generer son chemin
    //! \param new_Is_pathfind : nouvelle valeur du booléen
    void setIs_pathfind(bool new_Is_pathfind);

    //! \brief Getter du booléen qui indique si la voiture à generer son chemin
    //! \return bool : valeur du booléen
    const bool &getIs_pathfind() const;

    //! \brief Modifier l'indice du parkings ou la voiture va / est
    //! \param new_parking : nouvelle valeur de l'indice du parking
    void setParking(int new_parking);

    //! \brief Getter de l'indice du parking ou la voiture va / est
    //! \return int : valeur de l'indice du parking
    const int &getParking() const;

    //! \brief Modifier l'indice de la place ou la voiture va / est
    //! \param new_place : nouvelle valeur de l'indice de la place
    void setPlace(int new_place);

    //! \brief Getter de l'indice de la place ou la voiture va / est
    //! \return int : valeur de l'indice de la place
    const int &getPlace() const;

    //! \brief Modifier la valeurs de la largeur de la voiture
    //! Sert a ce que quand la voiture rentre dans l'enceinte du parking, elle rattrécie sa largeur
    //! \param new_width : nouvelle valeur de la largeur de la voiture
    void setwidth(int new_width);

    //! \brief Getter de la largeur de la voiture
    //! \return int : valeur de la largeur de la voiture
    const int &getwidth() const;

    //! \brief Modifier la valeurs de la hauteur de la voiture
    //! Sert a ce que quand la voiture rentre dans l'enceinte du parking, elle rattrécie sa hauteur
    //! \param new_height : nouvelle valeur de la hauteur de la voiture
    void setheight(int new_height);

    //! \brief Getter de la hauteur de la voiture
    //! \return int : valeur de la hauteur de la voiture
    const int &getheight() const;

    //! \brief Getter du chemin que la voiture va parcourir
    //! \return vector : chemin de la voiture
    vector<Node *> &getpathTab();

    //------------------------------------------------------------------------------

    //! \brief vérifie qu'un prix donné est acceptable ou non, avec une marge arbitraire. Renvoie un booléen.
    //! \param price prix à vérifier
    //! \param User utilisateur de la voiture
    //! \return bool : true si le prix est acceptable, false sinon
    bool isPriceOk(double price, Utilisateur User) const;

    //! \brief Extrait un ou plusieurs entier d'un String
    //! \param aString : String à extraire
    //! \return int : entier extrait
    int extractIntFromString(string aString) const;

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

    void deleteNode();

    //! \brief La voiture lit le message reçu (donné en paramètre) s'il y en a un
    //! (s'il n'y en a pas, le pointeur est nul),
    //! \param message : message reçu
    //! \return message généré
    Message managingConversation(Message *aMessage) const;

    //! \brief La voiture lit le message reçu (donné en paramètre)
    //! renvoie un message de type ACCEPT ou REJECT avec le nouveau prix si reject
    //! \param message : message reçu
    //! \param indPrOK : indice du parkings que la voiture a choisi
    //! \return message généré
    Message confirmConversation(Message *aMessage, int indPrOK) const;

    //! \brief Trouve le meilleur (minimum) prix dans un tableau de prix
    //! \param tabPrice vector de float : prix
    //! \return float : meilleur prix
    float bestPrice(vector<float> tabPrice);

    //! \brief incrémente le nombre de conversations finies de 1.
    void incrementNbFinishedConv();

    //! \brief Affiche les Infos du conducteur
    void UserGetInfos();

    //! \brief Test de regression la classe Voiture
    void test_regresion();
};

#endif