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
    float ParkTime;
    unsigned int id;
    string name;

public:
    //! \brief constructeur
    Utilisateur();
    //! \brief constructeur avec parametre
    //! \param u_maxPrice prix maximum que l'utilisateur est prêt à payer
    //! \param u_id identifiant de l'utilisateur
    //! \param u_name nom de l'utilisateur
    //! \param u_Parktime temps de stationnement de l'utilisateur
    Utilisateur(double maxPrice, unsigned int id, string name);
    //! \brief destructeur.
    ~Utilisateur();
    //! \brief renvoie un float contenant le prix maximum que l'utilisateur pourrait payer.
    double getMaxPrice() const;
    //! \brief renvoie l'id de l'utilisateur, qui sera unique.
    unsigned int getId() const;
    //! \brief renvoie le temps de stationnement de l'utilisateur.
    float getParkTime() const;
    //! \brief Modifie le temps de stationnement de l'utilisateur.
    //! \param u_ParkTime temps de stationnement de l'utilisateur.
    void setParkTime(float u_ParkTime);
    //! \brief renvoie le nom de l'utilisateur sous forme de string.
    string getName() const;
    //! \brief test de régression de la classe utilisateur.
    void testRegression();
    //! \brief Renvoie un temps de stationnement aléatoire en fonction de pourcentage de temps de stationnement.
    float randomParkTime();
};

#endif