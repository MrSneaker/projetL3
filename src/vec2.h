#ifndef __VEC2_H__
#define __VEC2_H__

class Vec2
{
public:
    float x;
    float y;
    Vec2();

    //! \brief Constructeur de la classe Vec2
    Vec2(float x, float y);

    //! \brief Destructeur de la classe Vec2
    ~Vec2();

    //! \brief Surcharge de l'opérateur +
    //! \param New_vec : vecteur à ajouter
    Vec2 operator+(Vec2 New_vec);

    //! \brief Surcharge de l'opérateur *
    //! \param New_vec : vecteur à multiplier
    Vec2 operator*(Vec2 New_vec);
};

#endif