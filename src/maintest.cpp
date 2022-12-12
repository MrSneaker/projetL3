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
    // V1.test_regresion();

    // test de regression de la classe Utilisateur
    // Utilisateur u;
    // u.testRegression();
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

    //Affichage aff;

    //aff.AffichageSimulation();

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

    Menu m;
    m.menuLoop();
    return 0;
}