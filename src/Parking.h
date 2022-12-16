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
    // [cf commentaire de la donnée membre successPercentageLastConv pour plus d'explications]

    float startingPrice; // Prix proposé par le parking au début de la négociation

    // - C'est un prix toujours supérieur à minPrice

    // - Valeur variable, que le parking peut diminuer ou augmenter
    // au cours de sa vie, en fonction de si ce prix de départ
    // a tendance à être trop haut (pour les utilisateurs)
    // ou trop bas (ie le parking ne gagne pas assez d'argent)
    // [cf commentaire de la donnée membre successPercentageLastConv pour plus d'explications]

    int idP; // Numéro du parking : 0, 1 ou 2 dans l'implémentation, mais 1, 2 ou 3 sur l'affichage au sol

    bool isFull; // Vrai si le parking est plein, faux sinon

    Vec2 pos; // Position du coin supérieur gauche du parking

    double successPercentage; // Pourcentage de réussite des négociations du Parking


    double successPercentageLastConv; // Pourcentage de réussite des 10 dernières négociations du Parking

    // - Ratio, en pourcentage, de lastNbAgreements sur lastNbFinishedConv.

    // - A intervalles réguliers, le parking considère cette donnée membre
    // pour éventuellement modifier son minPrice et son startingPrice
    // (cf fonction membre reconsiderPrices).

    /* - En détails : le parking calcule régulièrement son nombre de
       réussites récentes par rapport à son nombre de négociations récentes. Si les négociations
       ont souvent abouti à un refus de l'utilisateur de se garer dans le parking,
       (i.e. si successPercentageLastConv est au-dessous
       d'un certain seuil fixe [TO DO : voir plus tard si on fait plus dynamique qu'un simple seuil fixe]),
       cela veut dire que les prix du parking sont trop hauts, et ce dernier va donc diminuer
       les bornes de son intervalle de prix pour faire venir globalement plus de voitures.
       A l'inverse, si le rapport est au-dessus d'un certain seuil fixe (pas le même seuil),
       le parking va augmenter ses prix pour tenter de gagner plus d'argent.
    */


    double profit; // Quantité totale d'argent reçue par le Parking

    unsigned int nbFinishedConv; // Nombre de négociations effectuées par le parking
    // Cette donnée rentre dans le calcul de successPercentage.

    unsigned int lastNbFinishedConv; // nbFinishedConv % 10
    // Cette donnée rentre dans le calcul de successPercentageLastConv.

    unsigned int lastNbAgreements; // Nombre total de visites du parking à l'issue de ses 10 dernières conversations
    // Cette donnée rentre dans le calcul de successPercentageLastConv.

    unsigned int nbAgreement; // Nombre total d'accords trouvés par le Parking, donc nombre total de visites du Parking

    // - Une visite correspond à une fois où un utilisateur s'est garé dans le parking.

    // - Cette donnée rentre dans le calcul de successPercentage.



public:
    // CONSTRUCTEURS et DESTRUCTEUR

    //! \brief Constructeur à paramètres
    //! \param position position du parking (position du coin en haut à gauche)
    //! \param minimumPrice prix minimum que le parking peut accepter
    //! \param startPrice prix maximum que le parking propose
    //! \param DimX dimension horizontale du parking
    //! \param DimY dimension verticale du parking
    //! \param id ID du parking
    Parking(Vec2 position, float minimumPrice, float startPrice, int DimX, int DimY, int id);

    Parking();

    ~Parking();

    // ACCESSEURS

    vector<Place> &getPlacesTab();

    //! \brief Donne le nombre de places du parking
    int getNbPlaces() const;

    int getNbAvailablePlaces() const;

    int getMinPrice() const;

    int getStartingPrice() const;

    const double &getProfit() const;

    const int &getId() const;

    const vector<pair<double, double>> &getDataProfit() const;

    const vector<pair<double, double>> &getDataStartingPrice() const;

    const vector<pair<double, double>> &getDataNbPlaceTaken() const;

    //! \brief Donne la position (x,y) du parking – coin en haut à gauche
    const Vec2 &getPos() const;

    //! \brief Donne la largeur du parking
    const int &getDIMX() const;

    //! \brief Donne la hauteur du parking
    const int &getDIMY() const;

    //! \brief Donne le pourcentage de succès du parking
    const double &getSuccessPourcentage() const;

    //! \brief Met à jour la donnée membre isFull, puis retourne sa valeur
    bool IsFull();

    // MUTATEURS

    void setMinPrice(float minimumPrice);

    void setStartingPrice(float startPrice);

    void setNbAvailablePlaces(int nbAvailablePlaces);

    //! \brief Incrémente de 1 le nombre de visites de l'utilisateur passé en paramètre.
    //! \param id ID d'un utilisateur.
    void incrementNbVisitsUser(unsigned int id);

    //! \brief Enlève une place au nombre de places disponibles.
    void decrementNbAvailablePlaces();

    //! \brief Ajoute une place au nombre de places disponibles.
    void incrementNbAvailablePlaces();

    //! \brief Incrémente le nombre de visites du parking.
    void incrementNbAgreements();

    //! \brief Incrémente de 1 le nombre de négociations effectuées par le parking.
    void incrementNbFinishedConv();

    // AUTRES FONCTIONS

    //! \brief Initialise toutes les places du parking (positions, etc.).
    //! \param PcornerX position horizontale
    //! \param PcornerY position verticale
    void initPlace(int PcornerX, int PcornerY);

    //! \brief Vérifie qu'un prix donné est acceptable ou non, avec une marge arbitraire de tolérance.
    //! \param price prix à vérifier
    //! \return vrai si le prix est acceptable, faux sinon
    bool isPriceOk(double price) const;

    //! \brief 1e phase de la négociation côté parking.
    //! \brief Durant cette phase, le parking et la voiture
    //! \brief négocient pour tenter de se mettre d'accord sur un prix.
    //! \brief Le parking lit le message reçu (passé en paramètre)
    //! \brief et en crée un nouveau (comme il s'agit forcément d'une réponse, les données du nouveau
    //! \brief message sont initialisées en fonction des données contenues dans le message reçu).
    //! \brief Types de messages générables :
    //! \brief  - OFFER
    //! \brief  - COUNTER_OFFER
    //! \brief  - NO_MORE_SPOTS
    //! \brief  - LAST_OFFER
    //! \brief  - ACCEPT
    //! \brief  - REJECT
    //! \brief Types de messages reçus pris en compte :
    //! \brief  - CALL
    //! \brief  - COUNTER_OFFER
    //! \brief  - LAST_OFFER
    //! \brief  - ACCEPT
    //! \brief  - REJECT
    //! \param aMessage message reçu
    //! \return un message
    Message managingConversation(Message* aMessage) const;

    //! \brief 2e phase de la négociation côté parking.
    //! \brief Durant cette phase, la voiture informe le parking
    //! \brief de sa venue ou de sa non-venue, selon si le parking
    //! \brief en question est celui qu'elle a choisi ou non,
    //! \brief après avoir comparé les prix.
    //! \brief Types de messages générables :
    //! \brief  - OK_TO_PARK
    //! \brief  - ABORT
    //! \brief Types de messages reçus pris en compte :
    //! \brief  - CONFIRM_ACCEPT
    //! \brief  - RENOUNCE
    //! \param aMessage message reçu
    //! \return un message
    Message confirmConversation(Message* aMessage);

    //! \brief Ajoute au profit du parking la valeur
    //! \brief (prix de la place louée à une voiture) passée en paramètre multipliée
    //! \brief par la durée de stationnement (convertie en heures simulation) passée en paramètre.
    //! \param aPrice un prix
    //! \param parkTime une durée de stationnement
    void updateProfit(double aPrice, float parkTime);

    //! \brief Met à jour le pourcentage de réussite des négociations du parking.
    void updateSuccessPercentage();

    //! \brief Considère la donnée membre successPercentageLastConv
    //! \brief et modifie éventuellement minPrice et startingPrice en conséquence.
    void reconsiderPrices();

    int extractIntFromString(string aString) const;

    void addUsersData(Utilisateur unUtilisateur);

    void addToData(double currentTime);

    // TEST DE REGRESSION

    void testRegression();
};

#endif

