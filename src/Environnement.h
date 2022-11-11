#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "vec2.h"
#include "Node.h"
#include "Conversation.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <thread>

#define DimWindowX 1000
#define DimWindowY 800
#define tailleCase 10

using namespace std;

class Environnement
{
private:
    Vec2 position;
    float speed;

    // Noeud de départ et d'arrivée

    bool endNodeReached = false;
    unsigned int frames = 0;
    float frameParkTime = 0.f;
    unsigned int prevtime = 0;
    unsigned int currenttime = 0;
    float deltaTime = 0.f;
    float frametime = 0.f;





    // on veut gérer les convs dynamiquement
    vector<Conversation *> conv;

public:
    string map[DimWindowX / tailleCase * DimWindowY / tailleCase];
    
    vector<Voiture> voitures;
    vector<Parking> parkings;
    vector<Utilisateur> conducteurs;
    unsigned int temps;
    float TempsEcoule = 0.f;
    bool Pause = false;
    bool SpeedUp = false;

    void Astar(Voiture &v, unsigned int StartInd, unsigned int EndInd);

    //! \brief Fonction revoyant un nombre aléatoire en deux valeurs
    //! \param min valeur minimale
    //! \param max valeur maximale
    int random(int min, int max);

    Environnement();
    ~Environnement();

    //! \brief Fonction permettant de retourner la position d'une case a partir de son indice
    Vec2 GetPosbyNodeInd(int indiceCase) const; 

    //! \brief Fonction permettant de retourner l'indice d'une case a partir de sa position
    int GetNodeIndbyPos(Vec2 pos) const;

    const int GetEntry();

    //! \brief Initialisation d'un utilisateur, puis ajout dans le tableau de conducteurs.
    void initUser();

    //! \brief Initialisation des parkings
    void initParkings();

    //! \brief Ajout d'une voiture avec un conducteur dans le tableau de voitures.
    void AddVoiture();

    //! \brief Enleve une voiture du tableau de voitures.
    //! \param numVoiture numéro de la voiture à enlever.
    void RemoveVoiture(int numVoiture);

    //! \brief Update le status de chaque voiture.
    void updateStateVoiture();

    //! \brief Boucle de jeu
    void Environnement_play();

    //! \brief récupère les valeurs contenue dans le fichier map.txt qui contient un plateau de 0 et de 1
    //! \brief 0 = case libre, 1 = case obstacle
    void getMap();

    //! \brief on créé une conv quand on veut communiquer.
    int createConv();

    int chosenPark(vector<Conversation *> conv, Voiture v);

    //! \brief pour suppr une conv après utilisation
    void deleteConv(int ind);

    //! \brief pour réaliser la conversation.
    void conversation(Voiture v);

    //! \brief supprime le dossier de logs avant nouvelle itération.
    void removeLogs();

    //Fonction qui permet de revoyer l'indice d'une place d'un des 3 parkings sauf si celui-ci est plein et que la place est prise
    int getPlaceInd(int parkingInd);

    int getParkingInd();

    void changeTarget(Voiture v, int indPr);

    //! \brief Test de regression de la classe Environnement
    void test_regresion();
};

#endif