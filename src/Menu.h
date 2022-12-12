#ifndef __MENU_H_
#define __MENU_H_

#include "Image.h"
#include "Affichage.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

#define DimWindowX 1000
#define DimWindowY 800

class Menu
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event events;

    Image startButton;
    Image quitButton;
    Image background;
    Image settings;

    TTF_Font *font_default;

public:
    Menu();
    ~Menu();

    void initMenu();
    void initFont();
    void initTexture();
    void destructMenu();
    void afficherMenu();
    void launchSim();
    void menuLoop();
};

#endif