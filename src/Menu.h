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
    Image settingsBack;

    unsigned int settingsX;
    unsigned int settingsY;
    unsigned int settingsW;
    unsigned int settingsH;
    Image settings;

    unsigned int plusX;
    unsigned int plusY;
    unsigned int plusW;
    unsigned int plusH;
    Image plus;

    unsigned int minusX;
    unsigned int minusY;
    unsigned int minusW;
    unsigned int minusH;
    Image minus;

    unsigned int okButtonX;
    unsigned int okButtonY;
    unsigned int okButtonW;
    unsigned int okButtonH;
    Image okButton;

    unsigned int cancelButtonX;
    unsigned int cancelButtonY;
    unsigned int cancelButtonW;
    unsigned int cancelButtonH;
    Image cancelButton;

    TTF_Font *font_default;
    TTF_Font *font_param;

    double price1;
    double defPrice1;

    double price2;
    double defPrice2;

    double price3;
    double defPrice3;

    double userPrice;
    double defUserPrice;

    double tpsAppVoiture;
    double defTpsApp;

public:
    Menu();
    ~Menu();

    void initMenu();
    void initFont();
    void initTexture();
    void destructMenu();
    void showMenu();
    void launchSim();
    void menuLoop();
    void showSettings();
    void afficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);
};

#endif