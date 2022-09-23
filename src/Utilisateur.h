#ifndef __UTILISATEUR_H__
#define __UTILISATEUR_H__

#include <string>
using namespace std;

class Utilisateur
{
private:
    float minPrice,maxPrice;
    unsigned int id;
    string name;
    
public:
    //! \brief constructeur
    Utilisateur();
    //! \brief constructeur avec parametre
    Utilisateur(float minPrice,float maxPrice,unsigned int id);
    //! \brief destructeur
    ~Utilisateur();
    //! \brief 
    float getMinPrice();
    float getMaxPrice();
    float getAvgPrice();
    unsigned int getId();
    string getName();
};


#endif