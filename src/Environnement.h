#ifndef _Environnement_H_
#define _Environnement_H_

#include "Voiture.h"
#include "Parking.h"
#include "Utilisateur.h"
#include "Place.h"
#include "vec2.h"
#include "Node.h"
#include "Conversation.h"
#include "Graph.h"
#include <filesystem>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <thread>
#include <filesystem>

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
    unsigned int currentTime = 0;
    float realTime = 0.f;
    float deltaTime = 0.f;
    float frametime = 0.f;

    // on veut gérer les convs dynamiquement
    vector<Conversation *> conv;
    vector<Utilisateur> SimuConducteurs; // liste des conducteurs qui sont utilisés dans la simulation
    vector<Utilisateur> tmpsavedConducteurs; // liste des conducteurs qui seront enregistrés à la fin de la simulation
    vector<Utilisateur> savedConducteurs; // liste des conducteurs enregistrés dans le fichier
    int nbUserCreated = 0;
    int nbUserSaved = 0;

    vector<string> m_NameList;
    vector<string> f_NameList;
    vector<string> SurnameList;

    vector<pair<double,double>> dataAvgSuccessPourcent;

public:
    string map[DimWindowX / tailleCase * DimWindowY / tailleCase];

    vector<Voiture> voitures; // liste des voitures
    vector<Parking> parkings; // liste des parkings
    vector<Utilisateur> conducteurs; // liste des conducteurs
    vector<int> doubleUser; // liste des conducteurs qui ont été enregistrés deux fois
    unsigned int temps;
    float TempsEcoule = 0.f;
    bool Pause = false;
    bool SpeedUp = false;
    int Secondes = 0;
    int Minutes = 0;
    int Heures = 0;
    int Jours = 0;
    int Mois = 0;

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

    const int GetExit();

    //! \brief Fonction horloge
    void ClockTime();

    //! \brief Fonction permettant de retourner un temps de stationnement aléatoire
    float randomParkTime();
    //! \brief Initialisation d'un utilisateur, puis ajout dans le tableau de conducteurs.
    void initUser(bool quitif);

    //! \brief Fonction permettant de créer un id aléatoire pour un utilisateur sans qu'il y ait de doublons
    int CreateRandomId();

    //! \brief Initialisation des parkings
    void initParkings();

    //! \brief Ajout d'une voiture avec un conducteur dans le tableau de voitures.
    void AddVoiture();

    //! \brief Enleve une voiture du tableau de voitures.
    //! \param numVoiture numéro de la voiture à enlever.
    void RemoveVoiture(int numVoiture);

    //! \brief Update le status de chaque voiture.
    void updateStateVoiture();

    //! \brief Update les caractéristiques de chaque parking (dont ses prix).
    void updateStateCarParks();

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
    void conversation(Voiture &v);

    //! \brief supprime le dossier de logs avant nouvelle itération.
    void removeLogs();

    double searchMaxInPair(vector<pair<double,double>> tab);

    double searchMax(vector<double> tab);

    //Fonction qui permet de revoyer l'indice d'une place d'un des 3 parkings sauf si celui-ci est plein et que la place est prise
    int getPlaceInd(int parkingInd);

    int getParkingInd();

    void changeTarget(Voiture &v, int indPr);

    void makeGraph(int choice);

    void saveUser();

    void getUser();

    //Fonction qui verifie qu'il ny'a pas de doublons d'id dans le fichier user.txt
    bool checkId(int id, string filename);

    //! \brief Fonction qui récupère les noms et prénoms dans les fichiers txt
    void getNames_SurnamesFromFile();

    //! \brief Fonction qui retourne un nom aléatoire
    //! \param gender "m" = male | "f" = female | [vide] = aleatoire
    string getName(string gender = "any");

    //! \brief Fonction qui retourne un prénom aléatoire
    string getSurname();

    //! \brief Test de regression de la classe Environnement
    void test_regresion();
};

#endif
