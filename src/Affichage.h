#ifndef _Affichage_H_
#define _Affichage_H_

#include "Environnement.h"
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
        SDL_Surface *surface;
        SDL_Surface *UpRoad;
        SDL_Surface *DownRoad; 
        SDL_Texture *texture;
        SDL_Texture *textureUpRoad;
        SDL_Texture *textureDownRoad;
        bool quit;

        TTF_Font *font_default;



    public:
        Affichage();
        ~Affichage();
        void InitAffichage();
        void AffichagePlateau();

        void AffichageSimulation();

};



#endif