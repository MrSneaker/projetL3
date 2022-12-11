#ifndef _PARKING_H
#define _PARKING_H

#include "Place.h"
#include "vec2.h"
#include "Voiture.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

class Parking
{

private:
    vector<Place> placesTab; // Tableau dynamique de Places

    int nbPlaces; // Nombre total de places (disponibles + occupées) dans le parking
    // Valeur fixe du début à la fin de la vie du parking

    int nbAvailablePlaces; // Nombre de places disponibles dans le parking

    int DIMX, DIMY; // Dimensions horizontale et verticale

    float minPrice; // Prix minimum accepté par le parking

    // - C'est le prix au-dessous duquel le parking refusera d'aller au cours d'une négocation

    // - Valeur variable, que le parking peut diminuer ou augmenter
    // au cours de sa vie, en fonction de si ce prix minimum
    // a tendance à être trop haut (pour les utilisateurs)
    // ou trop bas (ie le parking ne gagne pas assez d'argent)
    // [cf commentaire de la donnée membre "nbTotalVisits" pour plus d'explications]

    float startingPrice; // Prix proposé par le parking au début de la négociation

    // - C'est un prix toujours supérieur à minPrice

    // - Valeur variable, que le parking peut diminuer ou augmenter
    // au cours de sa vie, en fonction de si ce prix de départ
    // a tendance à être trop haut (pour les utilisateurs)
    // ou trop bas (ie le parking ne gagne pas assez d'argent)
    // [cf commentaire de la donnée membre "nbTotalVisits" pour plus d'explications]

    int idP; // Numéro du parking : 0, 1 ou 2 dans l'implémentation, mais 1, 2 ou 3 sur l'affichage au sol

    bool isFull; // Vrai si le parking est plein, faux sinon

    int nbTotalVisits; // Nombre total de visites du Parking

    // - Une visite correspond à une fois où un utilisateur s'est garé dans le parking.

    /* - Le parking calcule régulièrement son nombre de
       réussites récentes par rapport à son nombre de négociations récentes. Si les négociations
       ont souvent abouti à un refus de l'utilisateur de se garer dans le parking en question,
       (i.e. si successPercentageLastConv est au-dessous
       d'un certain seuil fixe [TO DO : voir plus tard si on fait plus dynamique qu'un simple seuil fixe]),
       cela veut dire que les prix du parking sont trop hauts, et ce dernier va donc diminuer
       les bornes de son intervalle de prix pour faire venir globalement plus de voitures.
       A l'inverse, si le rapport est au-dessus d'un certain seuil fixe (pas le même seuil),
       le parking va augmenter ses prix pour tenter de gagner plus d'argent.
       */

    Vec2 pos; // Position du coin supérieur gauche du parking

    double successPercentage; // Pourcentage de réussite des négociations du Parking

    double successPercentageLastConv; // Pourcentage de réussite des 10 dernières négociations du Parking

    // - Ratio, en pourcentage, de lastNbAgreements sur lastNbFinishedConv.

    // - A intervalles réguliers, le parking considère cette donnée membre
    // pour éventuellement modifier son minPrice et son startingPrice
    // (cf fonction membre reconsiderPrices).

    double profit; // Quantité totale d'argent reçue par le Parking

    unsigned int nbFinishedConv; // Nombre de négociations effectuées par le parking
    // Cette donnée rentre dans le calcul de successPercentage.

    unsigned int lastNbFinishedConv; // nbFinishedConv % 10
    // Cette donnée rentre dans le calcul de successPercentageLastConv.

    unsigned int lastNbAgreements; // Nombre total de visites du parking à l'issue de ses 10 dernières conversations
    // Cette donnée rentre dans le calcul de successPercentageLastConv.

    unsigned int nbAgreement;
    // - Nombre total d'accord trouvé par le parking.

public:
    // CONSTRUCTEURS et DESTRUCTEUR

    //! \brief Constructeur parametre de la class parking
    //! \param position position du parking (position du rectangle en haut a gauche)
    //! \param minimumPrice Prix minimum d'acceptance par minutes que le  parking peut accepté -> A REVOIR
    //! \param startPrice Prix max que le parking propose -> A REVOIR
    Parking(Vec2 position, float minimumPrice, float startPrice, int DimX, int DimY, int id);

    Parking();

    ~Parking();

    // ACCESSEURS

    vector<Place> &getPlacesTab();

    //! \brief Retourne le nombre de places du parking
    int getNbPlaces() const;

    int getNbAvailablePlaces() const;

    int getMinPrice() const;

    int getStartingPrice() const;

    const double &getProfit() const;

    const int &getId() const;

    const vector<pair<double, double>> &getDataProfit() const;

    const vector<pair<double, double>> &getDataStartingPrice() const;

    const vector<pair<double, double>> &getDataNbPlaceTaken() const;

    const int &getNbTotalVisits() const;

    //! \brief Donne la position (x,y) du parking - coin en haut a gauche
    const Vec2 &getPos() const;

    //! \brief Donne la largeur du parking
    const int &getDIMX() const;

    //! \brief Donne la hauteur du parking
    const int &getDIMY() const;

    //! \brief fonction qui renvoie le pourcentage de succes.
    const double &getSuccessPourcentage() const;

    //! \brief Fonction qui renvoie un entier, permet de savoir si le parking est plein ou non
    bool IsFull();

    // MUTATEURS

    void setMinPrice(float minimumPrice);

    void setStartingPrice(float startPrice);

    void setNbAvailablePlaces(int nbAvailablePlaces);

    //! \brief ajoute un utilisateur au tableau usersTab en vérifiant que celui-ci n'existe pas déjà dans le tableau.
    //! \param unUtilisateur un utilisateur.
    void addUsersData(Utilisateur unUtilisateur);

    void addToData(double currentTime);

    void incrementNbTotalVisits();

    //! \brief incrémente le nombre de visites de l'utilisateur en paramètre de 1 à chaque appel.
    //! \param unUtilisateur pointeur sur un utilisateur.
    void incrementNbVisitsUser(unsigned int id);

    //! \brief enleve une place au nombre de places dispo
    void decrementNbAvailablePlaces();

    //! \brief ajoute une place au nombre de places dispo
    void incrementNbAvailablePlaces();

    //! \brief Incrémente le nombre total de visites du parking
    //! \brief à l'issue des 10 dernières conversations.
    void incrementNbAgreements();

    //! \brief Incrémente de 1 le nombre de négociations effectuées par le parking.
    void incrementNbFinishedConv();

    //! \brief Ajoute au profit (du parking) la valeur
    //! \brief (prix de la place louée à une voiture) passée en paramètre.
    void updateProfit(double aPrice, float parkTime);

    //! \brief Met à jour le pourcentage de réussite des négociations du Parking.
    void updateSuccessPercentage();

    // AUTRES FONCTIONS

    //! \brief initialisation de toutes les places de parkings (positions, etc..).
    void initPlace(int PcornerX, int PcornerY);

    //! \brief vérifie qu'un prix donné est acceptable ou non, avec une marge arbitraire. Renvoie un booléen.
    //! \param price prix à vérifier
    bool isPriceOk(double price) const;

    //! \brief Le parking lit le message reçu (donné en paramètre)
    //! \brief et en crée un nouveau (comme il s'agit forcément d'une réponse, les données du nouveau
    //! \brief message sont initialisées en fonction des données contenues dans le message reçu).
    //! \brief Types de message générable :
    //! \brief  - OFFER
    //! \brief  - COUNTER_OFFER
    //! \brief  - LAST_OFFER
    //! \brief  - ACCEPT
    //! \brief  - REJECT
    //! \brief Types de message reçu pris en compte :
    //! \brief  - CALL
    //! \brief  - COUNTER_OFFER
    //! \brief  - LAST_OFFER
    //! \brief  - ACCEPT
    //! \brief  - REJECT
    Message managingConversation(Message *aMessage) const;

    //! \brief - Confirme la transaction ou non en fonction de la réponse de la voiture, fait les opérations en conséquence.
    //! \brief - Cette fonction est appelée pour toute négociation, on y incrémente donc notamment le nombre de négociations
    //! \brief effectuées par le parking.
    Message confirmConversation(Message *aMessage);

    //! \brief Consideration de la donnée membre successPercentage
    //! \brief puis modification éventuelle de minPrice et startingPrice en conséquence.
    void reconsiderPrices();

    int extractIntFromString(string aString) const;

    // TEST DE REGRESSION

    void testRegression();
};

#endif
