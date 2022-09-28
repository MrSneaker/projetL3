#include "vec2.h"
#include "Environnement.h"

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
    Utilisateur u;
    //u.testRegression(); 
    
    bool AfficheTime = false;
    if(AfficheTime){
        while(1){
            time_t now = time(NULL); // temps actuel
            tm *ltm = localtime(&now); // temps local
            int heure = ltm->tm_hour;
            int minute = ltm->tm_min;
            int seconde = ltm->tm_sec;
            cout<<"--------------------------------------"<<endl;
            cout<<"Heure : "<<heure<<":"<<minute<<":"<<seconde<<endl;
            cout<<"--------------------------------------"<<endl;

            if(seconde%10 == 0)
            {
                cout<<"Faire une action"<<endl;
            }

        sleep(1);
        }
    }

    Environnement Simulation;

    Simulation.Environnement_play();
    //Simulation.test_regresion();


    return 0;
}