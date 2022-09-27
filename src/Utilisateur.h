#ifndef __UTILISATEUR_H__
#define __UTILISATEUR_H__

#include <string>
#include <assert.h>
#include <iostream>

using namespace std;

class Utilisateur
{
private:
    double maxPrice;
    unsigned int id;
    string name;

public:
    //! \brief constructeur
    Utilisateur();
    //! \brief constructeur avec parametre
    Utilisateur(double maxPrice, unsigned int id, string name);
    //! \brief destructeur.
    ~Utilisateur();
    //! \brief renvoie un float contenant le prix maximum que l'utilisateur pourrait payer.
    double getMaxPrice() const;
    //! \brief renvoie l'id de l'utilisateur, qui sera unique.
    unsigned int getId() const;
    //! \brief renvoie le nom de l'utilisateur sous forme de string.
    string getName() const;
    //! \brief test de régression de la classe utilisateur.
    void testRegression();
};

#endif