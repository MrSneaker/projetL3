#ifndef __UTILISATEUR_H__
#define __UTILISATEUR_H__

#include <string>
using namespace std;

class Utilisateur
{
private:
    float maxPrice;
    unsigned int id;
    string name;

public:
    //! \brief constructeur
    Utilisateur();
    //! \brief constructeur avec parametre
    Utilisateur(float maxPrice, unsigned int id, string name);
    //! \brief destructeur.
    ~Utilisateur();
    //! \brief renvoie un float contenant le prix maximum que l'utilisateur pourrait payer.
    float getMaxPrice() const;
    //! \brief renvoie l'id de l'utilisateur, qui sera unique.
    unsigned int getId();
    //! \brief renvoie le nom de l'utilisateur sous forme de string.
    string getName();
};

#endif