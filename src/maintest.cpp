#include "vec2.h"
#include "Voiture.h"

#include <iostream>

using namespace std;

int main(){
    srand(time(NULL));
    //test de regression de la classe Voiture
    Voiture V1;
    V1.test_regresion();

    //test de regression de la classe Utilisateur 
    Utilisateur u;
    u.testRegression();

    return 0;
}