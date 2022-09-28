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
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        bool quit;
    public:
        Affichage();
        ~Affichage();
        void Affichage_play(Environnement &env);
};



#endif