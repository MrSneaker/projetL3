#include "vec2.h"
#include "Environnement.h"
#include "Affichage.h"
#include "Parking.h"
#include "Conversation.h"

#include <time.h>
#include <iostream>
#include <unistd.h>
#include <limits>

using namespace std;

int main()
{
    srand(time(NULL)); // initialisation de rand

    // test de regression de la classe Voiture
    Voiture V1;
    // V1.test_regresion();

    // test de regression de la classe Utilisateur
    // Utilisateur u;
    // u.testRegression();

    time_t begin = time(NULL);
    Environnement Simulation;
    int a = 0;
    /*while (a!=-1)
    {
        Simulation.Environnement_play();
        //cout<<"temps : "<<Simulation.temps<<endl;
        if(Simulation.temps%30 == 0)
        {
            cout<<"continue? :";
            cin>>a;
            cout<<endl;
        }
    }*/
    // Simulation.test_regresion();

    Affichage aff;

    aff.AffichageSimulation();

    // time_t end = time(NULL)

    // Parking p1;
    // p1.testRegression();

    // Place P1;
    // P1.test_regresion();

    // Conversation c;
    // c.testRegression();
    // cout<<"Temps de calcul = "<<end-begin<<" secondes"<<endl;

    // Graph g;
    // g.test_regression();
    return 0;
}