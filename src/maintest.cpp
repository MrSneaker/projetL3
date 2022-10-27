#include "vec2.h"
#include "Environnement.h"
#include "Affichage.h"
#include "Parking.h"
#include "Conversation.h"

#include <time.h> 
#include <iostream> 
#include <unistd.h> 

using namespace std;

int main(){
    srand(time(NULL)); // initialisation de rand

    //test de regression de la classe Voiture
    Voiture V1;
    //V1.test_regresion();

    //test de regression de la classe Utilisateur 
    //Utilisateur u;
    //u.testRegression(); 
    
    time_t begin = time(NULL);
    Environnement Simulation;

    //Simulation.Environnement_play();
    //Simulation.test_regresion();

    Affichage Graph;

    Graph.AffichageSimulation();

    time_t end = time(NULL);


    //Parking p1;
    //p1.testRegression();

    //Place P1;
    //P1.test_regresion();

    //Conversation c;
    //c.testRegression();
    //cout<<"Temps de calcul = "<<end-begin<<" secondes"<<endl;
    return 0;
}