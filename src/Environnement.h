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

#define DimWindowX 1000
#define DimWindowY 800
#define tailleCase 10

using namespace std;

class Environnement
{
private:

    // Pour le temps
    float frames;
    float frameParkTime;
    float prevtime;
    float currentTime;
    float realTime;
    float deltaTime;
    float frametime;

    // on veut gérer les convs dynamiquement
    vector<Conversation *> conv;
    unsigned int nbConv; 

    vector<Utilisateur> SimuConducteurs; // liste des conducteurs qui sont utilisés dans la simulation
    vector<Utilisateur> tmpsavedConducteurs; // liste des nouveaux conducteurs qui sont ajoutés dans la simulation et qui seront ajouté au fichier User.txt
    vector<Utilisateur> savedConducteurs; // liste des conducteurs enregistrés dans le fichier
    unsigned int nbUserCreated;
    unsigned int nbUserSaved;

    vector<string> m_NameList; // liste des prenoms des conducteurs
    vector<string> f_NameList; // liste des prenoms des conductrices
    vector<string> SurnameList; // liste des noms des conducteurs

public:

    string map[DimWindowX / tailleCase * DimWindowY / tailleCase]; // tableau pour stocker 

    vector<Voiture> voitures; // liste des voitures
    vector<Parking> parkings; // liste des parkings
    vector<Utilisateur> conducteurs; // liste des conducteurs
    vector<int> doubleUser; // liste des conducteurs qui ont été enregistrés deux fois
    unsigned int temps;
    float TempsEcoule;
    bool Pause = false;
    bool SpeedUp = false;
    int Secondes ;
    int Minutes;
    int Heures;
    int Jours;
    int Mois;

    void Astar(Voiture &v, unsigned int StartInd, unsigned int EndInd, vector<Node *> &nodes);

    //! \brief Fonction revoyant un nombre aléatoire en deux valeurs
    //! \param min valeur minimale
    //! \param max valeur maximale
    int random(int min, int max);

    Environnement();
    ~Environnement();

    //! \brief Fonction permettant de retourner la position d'une case a partir de son indice
    //! \param indice indice de la case
    //! \return la position de la case
    Vec2 GetPosbyNodeInd(int indiceCase) const;

    //! \brief Fonction permettant de retourner l'indice d'une case a partir de sa position
    //! \param pos position de la case
    //! \return Entier correspondant a l'indice de la case
    const int GetNodeIndbyPos(Vec2 pos) const;

    //! \brief Fonction permettant de retourner l'indice du noeud d'une des 3 entrées
    //! \return Un entier correspondant à l'indice du noeud
    const int GetEntry();

    //! \brief Fonction permettant de retourner l'indice du noeud d'une des 3 sorties
    //! \return Un entier correspondant à l'indice du noeud
    const int GetExit();

    //! \brief Récupère les données pour les graphiques dans un fichier
    //! \param fileName vecteur de pair de double contenant les données x et y du graphique
    //! \return vecteur de pair de double contenant les données x et y du graphique
    const vector<pair<double,double>> getDataFromFile(string fileName) const;

    //! \brief Fonction qui permet d'actualisé l'horloge pour l'affichage (seconde, minute, heure, jour, mois)
    void ClockTime();

    //! \brief Fonction permettant de retourner un temps de stationnement aléatoire
    float randomParkTime();

    //! \brief Initialisation d'un utilisateur, puis ajout dans le tableau de conducteurs.
    //! \param quitif booleéan qui permet de faire réapparaitre un conducteur si il est déjà apparrut dans la simu
    void initUser(bool quitif);

    //! \brief Fonction permettant de créer un id aléatoire pour un utilisateur sans qu'il y ait de doublons
    //! \return Un entier correspondant à l'id de l'utilisateur
    int CreateRandomId();

    //! \brief Initialisation des parkings
    void initParkings();

    //! \brief Ajout d'une voiture avec un conducteur dans le tableau de voitures.
    void AddVoiture();

    //! \brief Enleve une voiture du tableau de voitures et le conducteur de la voiture du tableau de conducteurs.
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

    //! \brief Choisit le meilleur parking pour une voiture
    //! \param conv Vecteur de conversation qui contient toutes les conversations
    //! \param v Voiture qui a communiqué
    //! \return entier correspondant à l'id du parking choisit (si -1 alors pas de parking)
    int chosenPark(vector<Conversation *> conv, Voiture v);

    //! \brief pour suppr une conv après utilisation
    //! \param ind indice de la conv à supprimer
    void deleteConv(int ind);

    //! \brief pour réaliser la conversation.
    //! \param v Voiture qui a communiqué
    void conversation(Voiture &v);

    //! \brief supprime le dossier de logs avant nouvelle itération.
    void removeLogs();

    //! \brief Trouve le maximum d'un vecteur de pair de double
    //! \param tab vecteur de pair de double
    //! \return double correspondant au maximum du vecteur
    double searchMaxInPair(vector<pair<double,double>> tab);

    //! \brief Trouve le maximum d'un vecteur de double
    //! \param tab vecteur de double
    //! \return double correspondant au maximum du vecteur
    double searchMax(vector<double> tab);

    //! \brief Fonction qui permet de revoyer l'indice d'une place d'un des 3 parkings sauf si celui-ci est plein et que la place est prise
    //! \param parking parking dans lequel on cherche une place
    //! \return entier correspondant à l'indice de la place
    const int getPlaceInd(int parkingInd);

    //! \brief Permet a une voiture de changer de trajectoire a tout moment
    //! \param v Voiture qui change de trajectoire
    //! \param indPr Indice du parkings
    void changeTarget(Voiture &v, int indPr);

    //! \brief Fonction qui fait un graphique 
    //! \param choice choix du graphique (0 : profit, 1 : evolution du starting price, 2 : nombre de place occupé, 3 : Succès moyen des parkings)
    void makeGraph(int choice);

    //! \brief Fonction qui permet d'enregistrer les utilisateurs dans un fichier
    void saveUser();

    //! \brief Fonction qui permet de charger les utilisateurs dans le vecteur savedconducteurs 
    void getUser();

    //! \brief Fonction qui verifie qu'il ny'a pas de doublons d'id dans le fichier user.txt
    //! \param id id a verifier
    //! \param filename nom du fichier
    //! \return booléen qui permet de savoir si il y a des doublons ou non
    bool checkId(int id, string filename);

    //! \brief Fonction qui récupère les noms et prénoms dans les fichiers txt
    void getNames_SurnamesFromFile();

    //! \brief Fonction qui retourne un nom aléatoire
    //! \param gender "m" = male | "f" = female | [vide] = aleatoire
    //! \return string correspondant au nom
    string getName(string gender = "any");

    //! \brief Fonction qui retourne un prénom aléatoire
    //! \return string correspondant au prénom
    string getSurname();

    //! \brief Test de regression de la classe Environnement
    void test_regresion();
};

#endif
