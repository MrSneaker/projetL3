#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "vec2.h"
#include "Node.h"
#include "Conversation.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

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
    Node *startNode;
    Node *endNode;
    Node *currentNode;
    bool endNodeReached = false;
    int step = 0;

    // on veut gérer les convs dynamiquement
    vector<Conversation *> conv;

public:
    string map[DimWindowX / tailleCase * DimWindowY / tailleCase];
    vector<Node *> nodes;
    vector<Voiture> voitures;
    vector<Parking> parkings;
    vector<Utilisateur> conducteurs;

    void initNodes();
    void resetNodes(Voiture &v);
    void setNodes(unsigned int startInd, unsigned int endInd);
    void Astar(Voiture &v, unsigned int StartInd, unsigned int EndInd);
    void trackPath();
    vector<Node *> pathTab;  // tableau des noeuds du chemin
    vector<Node *> openList; // liste des noeuds à visiter

    //! \brief Fonction revoyant un nombre aléatoire en deux valeurs
    //! \param min valeur minimale
    //! \param max valeur maximale
    int random(int min, int max);

    Environnement();
    ~Environnement();

    //! \brief Fonction permettant de retourner la position d'une case a partir de son indice
    Vec2 GetPosbyNodeInd(int indiceCase);

    //! \brief Fonction permettant de retourner l'indice d'une case a partir de sa position
    int GetNodeIndbyPos(Vec2 pos);

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

    // on créé une conv quand on veut communiquer.
    int createConv();

    // pour suppr une conv après utilisation
    void deleteConv(int ind);

    // pour réaliser la conversation.
    void conversation(Voiture v, Parking p);

    //! \brief Test de regression de la classe Environnement
    void test_regresion();
};

#endif