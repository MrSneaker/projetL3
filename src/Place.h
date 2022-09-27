#ifndef __PLACE_H__
#define __PLACE_H__

#include "vec2.h"

class Place
{
private:
    Vec2 pos;
public:
    //! \brief constructeur de la place.
    Place();
    //! \brief destructeur de la place.
    ~Place();
    //! \brief position de la place.
    Vec2 getPos() const;
    //! \brief procédure de modification de la position de la place.
    void setPos(Vec2 pos);
    //! \brief booléen servant à savoir si la place est occupée ou non.
    bool isTaken = false;
};


#endif