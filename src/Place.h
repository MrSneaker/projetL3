#ifndef __PLACE_H__
#define __PLACE_H__

#include "vec2.h"

class Place
{
private:
    Vec2 pos;
    int indP;
    bool isTaken;
public:
    //! \brief constructeur de la place.
    Place();
    //! \brief constructeur à paramètre de Place.
    Place(Vec2 pos, int indP, bool isTaken);
    //! \brief destructeur de la place.
    ~Place();
    //! \brief position de la place.
    const Vec2& getPos() const;
    //! \brief procédure de récupération de l'indice de la position de la place.
    const int& getIndP() const;

    void setIsTaken(bool new_isTaken);

    const bool& getIsTaken() const;

    void test_regresion();
    
};


#endif