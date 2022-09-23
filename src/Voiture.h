#ifndef _VOITURE_H
#define _VOITURE_H 

#include "vec2.h"

class Voiture 
{

    private:

        Vec2 position; // Position (x,y) de la voiture
        Vec2 TargetPosition; // Position (x,y) de la cible (parking / place / sortie)
        float vitesse; // vitesse de la voiture
        //float batterie; // batterie de la voiture
        //Couleur couleur; // Couleur de la voiture
        //Utilisateur conducteur; // Personna qui est dans la voiture

    
    public:

        bool Is_in; // true si la voiture entre dans le parking
        bool Is_garee; // true si la voiture est garée dans le parking



    Voiture();
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

    //! \brief Modifie la position de la cible (parking / place / sortie)
    void setTargetPosition(Vec2 new_pos);

    //! \brief Renvoie la position de la voiture
    Vec2 get_position();

    //! \brief Modifie la position de la voiture
    //! \param new_pos nouvelle position de la voiture
    void set_position(Vec2 new_pos);


};


#endif  