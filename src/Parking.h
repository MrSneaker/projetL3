#ifndef _PARKING_H
#define _PARKING_H

#include "Place.h"
#include "vec2.h"
#include "Voiture.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Parking
{

private:


    vector<Place> placesTab;
    // Tableau dynamique de Places

    int nbPlaces;
    // - Nombre total de places (disponibles + occupées) dans le parking
    // - Valeur fixe du début à la fin de la vie du parking

    int nbAvailablePlaces;
    // Nombre de places disponibles dans le parking

    int DIMX,DIMY;

    float minPrice;
    // - Prix minimum accepté par le parking

    // - C'est le prix au-dessous duquel le parking refusera d'aller au cours d'une négocation

    // - Valeur variable, que le parking peut diminuer ou augmenter
    // au cours de sa vie, en fonction de si ce prix minimum
    // a tendance à être trop haut (pour les utilisateurs)
    // ou trop bas (ie le parking ne gagne pas assez d'argent)
    // [cf commentaire de la donnée membre "nbVisits" pour plus d'explications]







    float startingPrice;
    // - Prix proposé par le parking au début de la négociation

    // - C'est un prix toujours supérieur à minPrice

    // - Valeur variable, que le parking peut diminuer ou augmenter
    // au cours de sa vie, en fonction de si ce prix de départ
    // a tendance à être trop haut (pour les utilisateurs)
    // ou trop bas (ie le parking ne gagne pas assez d'argent)
    // [cf commentaire de la donnée membre "nbVisits" pour plus d'explications]





    bool isFull;
    // Vrai si le parking est plein, faux sinon




    vector<int> conversationsTab;
    // - Pas encore sûrs qu'on va l'utiliser,
    // et pas encore sûrs du type que l'on va stocker dans ce vector
    // (car on va peut-être stocker les conversations dans des fichiers TXT,
    // et/ou ne pas garder en mémoire les conversations une fois que ces dernières ont eu lieu)




    vector<Voiture*> voitures;
    // !!! [Pas sûr] Pointeur sur un tableau dynamique des Voitures "contenues"

    vector<Utilisateur*> usersTab;
    // Pas encore sûrs qu'on "stocke" les utilisateurs de cette manière

    int nbVisits;
    // Stocke le nombre de visites du parking.

    // Le parking va, toutes les 2h dans la simulation (par ex), calculer son nombre de
    // réussites par rapport à son nombre de négociations. Si les négociations
    // ont souvent abouti à un refus de l'utilisateur de se garer dans le parking en question,
    // (i.e. si le rapport nb de réussites/nb de négociations est au-dessous d'un certain seuil
    // qu'on aura fixé [voir plus tard si on fait plus dynamique qu'un simple seuil fixé]),
    // cela veut dire que les prix du parking sont trop hauts, et ce dernier va donc baisser
    // ses tarifs en moyenne pour obtenir globalement plus de voitures.

    vector<int> nbVisitsTab;
    // Pas encore sûrs qu'on "stocke" ces données sur les venues des utilisateurs de cette manière

    Vec2 pos;
    // Position du coin supérieur gauche du parking






public:


    // CONSTRUCTEUR et DESTRUCTEUR

    //! \brief Constructeur parametre de la class parking
    //! \param position position du parking (position du rectangle en haut a gauche)
    //! \param numberOfPlaces Nombre de palces disponible dans le parking
    //! \param minimumPrice Prix minimum d'acceptance par minutes que le  parking peut accepté -> A REVOIR
    //! \param startPrice Prix max que le parking propose -> A REVOIR
    Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float startPrice );
    
    Parking();

    ~Parking();


    
    

    // ACCESSEURS

    vector<Place> getPlacesTab() const;
    // Utile ?

    //! \brief Retourne le nombre de places du parking
    int getNbPlaces() const;

    int getNbAvailablePlaces() const;

    int getMinPrice() const;

    int getMaxPrice() const;

    vector<int> getConversationsTab() const;

    vector<Utilisateur*> getUsersTab() const;

    int getNbVisits() const;

    int getStartingPrice () const;
    
    vector<int> getNbVisitesTab() const;

    //! \brief Donne la position (x,y) du parking - coin en haut a gauche
    Vec2 getPos() const;

    //! \brief Fonction qui renvoie un entier, permet de savoir si le parking est plein ou non
    bool IsFull();

    // MUTATEURS

    // void setPlacesTab ();
    // TO DO : Je dois la finir et voir quel(s) paramètre(s) lui mettre

    void decrementNbAvailablePlaces();

    void incrementNbAvailablePlaces();

    void setMinPrice(float minimumPrice);

    void setMaxPrice(float maximumPrice);

    void setIsFull(bool filledToCapacity);

    void setConversationsTab();
    // TO DO : Je dois la finir et voir quel(s) paramètre(s) lui mettre

    void setUsersTab();
    // TO DO : Je dois la finir et voir quel(s) paramètre(s) lui mettre
    // dans l'idee on stock les iD.

    void incrementNbVisits();

    void incrementNbVisitsTab();
    // TO DO : Je dois la finir et voir quel(s) paramètre(s) lui mettre

        
    void setStartingPrice (float startPrice);
    

    //! \brief enleve une place au nombre de places dispo
    void decrementNbPlaces();

    //! \brief ajoute une place au nombre de places dispo
    void incrementNbPlaces();

    //! \brief initialisation de toutes les places de parkings (positions, etc..).
    void initPlace(int nbPlaceLi, int nbPlaceCol, int PcornerX, int PcornerY);

    void testRegression();
};

#endif
