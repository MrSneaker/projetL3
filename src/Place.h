#ifndef __PLACE_H__
#define __PLACE_H__

#include "vec2.h"

class Place
{
private:
    Vec2 pos;
    int indP;
    bool isTaken;
    bool isReserved;
public:
    //! \brief constructeur de la place.
    Place();
    //! \brief constructeur à paramètre de Place.
    Place(Vec2 pos, int indP);
    //! \brief destructeur de la place.
    ~Place();
    //! \brief position de la place.
    const Vec2& getPos() const;
    //! \brief procédure de récupération de l'indice de la position de la place.
    const int& getIndP() const;

    //! \brief met à jour la valeur de isTaken avec la valeur de \param new_isTaken, un booléen.
    void setIsTaken(bool new_isTaken);

    //! \brief retourne le booléen isTaken. Vrai = place prise, faux sinon.
    const bool& getIsTaken() const;

    //! \brief  met à jour la valeur de isReserved avec la valeur de \param new_isReserved, un booléen.
    void setIsReserved(bool new_isReserved);

    //! \brief retourne le booléen isReserved. Vrai = place réservée, faux sinon. 
    const bool& getIsReserved() const;

    //! \brief test de régression de la classe Place.
    void test_regresion();
    
};


#endif