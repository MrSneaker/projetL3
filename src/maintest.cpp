#include "vec2.h"
#include "Voiture.h"
#include <time.h>

#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    srand(time(NULL));
    //test de regression de la classe Voiture
    Voiture V1;
    //V1.test_regresion();

    //test de regression de la classe Utilisateur 
    Utilisateur u;
    //u.testRegression();


    while(1){
        time_t now = time(NULL); // temps actuel
        tm *ltm = localtime(&now); // temps local
        int heure = ltm->tm_hour; 
        int minute = ltm->tm_min;
        int seconde = ltm->tm_sec;
        cout<<"Heure : "<<heure<<":"<<minute<<":"<<seconde<<endl;

        //Affiche hello toute les 30 secondes 
        if(seconde%30 == 0){
            cout<<"Hello"<<endl;
        }

        sleep(1);


    }



    return 0;
}