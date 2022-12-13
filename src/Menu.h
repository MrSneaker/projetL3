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

    unsigned int startButtonX;
    unsigned int startButtonY;
    unsigned int startButtonW;
    unsigned int startButtonH;
    Image startButton;

    unsigned int quitButtonX;
    unsigned int quitButtonY;
    unsigned int quitButtonW;
    unsigned int quitButtonH;
    Image quitButton;

    Image background;

    unsigned int settingsX;
    unsigned int settingsY;
    unsigned int settingsW;
    unsigned int settingsH;
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