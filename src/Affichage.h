#ifndef _Affichage_H_
#define _Affichage_H_

#include "Environnement.h"
#include "Image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define DimWindowX 1000
#define DimWindowY 800

class Affichage{

    private:
        Environnement environnement;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        
        //------------------------------- IMAGE -----------------------------------
      
        Image Voiture;
        Image P1;
        Image P2;
        Image P3;
        Image UpRoad;
        Image DownRoad;


        SDL_Rect Place;


        bool quit;

        //------------------------------- TEXT -----------------------------------
        TTF_Font *font_default;

        int X = 0;
        int Y = 0;

        
        //Utile pour le temps et les frames

        int totalFrames = 0;

        int frames = 0;

        float frametime=0;

        int prevtime = 0;

        int currenttime = 0;

        float deltatime = 0.f;





    public:
    
        vector<SDL_Rect> VoituresRect; // Tableau des rectangles des voitures (Pour plus tard)
        Affichage();
        ~Affichage();
        void InitAffichage();
        void AffichagePlateau();

        void AffichageSimulation();

};



#endif