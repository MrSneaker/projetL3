#include "vec2.h"
#include "Environnement.h"
#include "Affichage.h"
#include "Parking.h"
#include "Conversation.h"
#include "Menu.h"

#include <time.h>
#include <iostream>
#include <unistd.h>
#include <limits>

using namespace std;

int main()
{
    srand(time(NULL)); // initialisation de rand

    // test de regression de la classe Voiture
    Voiture v1;
    v1.test_regresion();

    // test de regression de la classe Utilisateur
    Utilisateur u;
    u.testRegression();

    Parking p1;
    p1.testRegression();

    Place P1;
    P1.test_regresion();

    Conversation c;
    c.testRegression();

    Graph g;
    g.test_regression();

    Environnement sim;
    sim.test_regresion();

    return 0;
}