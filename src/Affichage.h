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
        SDL_Surface *P1;
        SDL_Texture *P1Texture;
        SDL_Surface *P2;
        SDL_Texture *P2Texture;
        SDL_Surface *P3;
        SDL_Texture *P3Texture;


        SDL_Surface *UpRoad;
        SDL_Texture *textureUpRoad;

        SDL_Surface *DownRoad; 
        SDL_Texture *textureDownRoad;

        Image Voiture;

        SDL_Rect Place;


        bool quit;

        //------------------------------- TEXT -----------------------------------
        TTF_Font *font_default;




    public:
    
        vector<SDL_Rect> VoituresRect; // Tableau des rectangles des voitures (Pour plus tard)
        Affichage();
        ~Affichage();
        void InitAffichage();
        void AffichagePlateau();

        void AffichageSimulation();

};



#endif