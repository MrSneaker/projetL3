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

    Image plus;
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

    unsigned int clearButtonX;
    unsigned int clearButtonY;
    unsigned int clearButtonW;
    unsigned int clearButtonH;
    Image clearButton;

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

    double userPriceInf;
    double defUserPriceInf;

    double tpsAppVoiture;
    double defTpsApp;

public:
    //! \brief Constructeur du Menu.
    Menu();
    //! \brief Destructeur du Menu.
    ~Menu();

    //! \brief initialise le menu (initialisation de la SDL, des textures, des fonts).
    void initMenu();
    //! \brief initialise les fonts.
    void initFont();
    //! \brief initialise les textures.
    void initTexture();
    //! \brief Détruit le menu et libère l'espace alloué aux textures et fonts.
    void destructMenu();
    //! \brief Affichage du menu.
    void showMenu();
    //! \brief Lancement de la simulation.
    void launchSim();
    //! \brief Boucle d'affichage et de gestion des évènements.
    void menuLoop();
    //! \brief Affichage des paramètres.
    void showSettings();
    //! \brief Réinitialise les valeurs de simulation choisies aux valeurs par défaut.
    void setToDef();
    //! \brief Sauvegarde les valeurs de simulation choisies.
    void saveValue();
    //! \brief Affiche du texte selon les différents paramètre
    //! \brief 2 choix possible : 1 - Afficher une simple ligne de texte ou 2 - Afficher du texte + une valeur statique ou dynamique (qui change au fil du temps)
    //! \brief Pour passer de du choix 1 a 2 il suffit de mettre juste un String vide ( "" ) sur le parametre Msg
    //! ex : AfficherTexte(---, "Son texte", --- , ---, etc. ) -> Affiche une simple ligne de texte.
    //! ex : AfficherTexte(---, "", "Texte", valeur, ---, etc.) -> Affiche Texte + valeur
    //! \param font Police du texte
    //! \param Msg 1 - Texte simple
    //! \param MsgWithValeur 2 - Texte qui accompagne la valeur
    //! \param valeur Valeur que l'on veut afficher
    //! \param x Position en x du texte
    //! \param y Position en y du texte
    //! \param r Parametre R du RGBA -> color rouge
    //! \param g Parametre G du RGBA -> color vert
    //! \param b Parametre B du RGBA -> color bleu
    //! \param a Parametre A du RGBA -> transparance
    void afficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);
};

#endif