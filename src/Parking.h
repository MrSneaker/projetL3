#ifndef _PARKING_H
#define _PARKING_H

#include "Place.h"
#include "vec2.h"
#include "Voiture.h"
#include <vector>

using namespace std;

class Parking
{

private:
    vector<Place> placesTab;
    // tableau 1D de Places

    int nbPlaces;

    int nbAvailablePlaces;

    float minPrice;

    float maxPrice;

    bool isFull;

    vector<int> *conversationsTab;
    // Pas encore sûrs qu'on va l'utiliser

    vector<Voiture> *voitures;

    vector<Utilisateur> *usersTab;
    // Pas encore sûrs qu'on "stocke" les utilisateurs de cette manière

    int nbVisits;
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

public:
    // CONSTRUCTEUR et DESTRUCTEUR

    //! \brief Constructeur parametre de la class parking
    //! \param position position du parking (position du rectangle en haut a gauche)
    //! \param numberOfPlaces Nombre de palces disponible dans le parking
    //! \param minimumPrice Prix minimum d'acceptance par minutes que le  parking peut accepté -> A REVOIR
    //! \param maximumPrice Prix max que le parking propose -> A REVOIR
    Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float maximumPrice);

    ~Parking();

    // ACCESSEURS

    vector<Place> getPlacesTab() const;
    // Utile ?

    //! \brief Retourne le nombre de places du parking
    int getNbPlaces() const;

    int getNbAvailablePlaces() const;

    int getMinPrice() const;

    int getMaxPrice() const;

    vector<int> *getConversationsTab() const;

    vector<Utilisateur> *getUsersTab() const;

    int getNbVisits() const;

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

    //! \brief enleve une place au nombre de places dispo
    void decrementNbPlaces();

    //! \brief ajoute une place au nombre de places dispo
    void incrementNbPlaces();

    //! \brief initialisation de toutes les places de parkings (positions, etc..).
    void initPlace();
};

#endif
