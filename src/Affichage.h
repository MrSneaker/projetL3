#ifndef _Affichage_H_
#define _Affichage_H_

#include "Environnement.h"
#include "Image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#define DimWindowX 1000
#define DimWindowY 800

class Affichage
{

private:
    Environnement environnement;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

//------------------------------- IMAGE ----------------------------------------

    Image Voiture;
    Image Voiture2;
    Image Voiture3;
    Image P1;
    Image P2;
    Image P3;
    Image UpRoad;
    Image DownRoad;
    Image UserCard;
    Image ParkSheet;
    Image Clock;
    Image Calendar;

    unsigned int PauseX = 50;
    unsigned int PauseY = 826;
    unsigned int PauseW = 43;
    unsigned int PauseH = 55;
    Image Pause;
    Image Play;

    unsigned int SpeedUpX = 150;
    unsigned int SpeedUpY = 826;
    unsigned int SpeedUpW = 43;
    unsigned int SpeedUpH = 55;
    Image SpeedUp;

    unsigned int ExitX = 853;
    unsigned int ExitY = 826;
    unsigned int ExitW = 132;
    unsigned int ExitH = 55;
    Image Exit;

    unsigned int MenuArrowX = 470;
    unsigned int MenuArrowY = 20;
    unsigned int MenuArrowW = 60;
    unsigned int MenuArrowH = 20;
    unsigned int MenuArrowAngle = 0;
    Image MenuArrow;

    SDL_Rect Place;

    bool quit;

//----------------------------------- TEXTE ------------------------------------

    TTF_Font *font_default;
    TTF_Font *font_UserCard;
    TTF_Font *font_UserCardBold;
    TTF_Font *font_Time;
    TTF_Font *font_Calendar;

//------------------------------------------------------------------------------

    int Xm, Ym; // Position X Y de la souris lorsqu'elle bouge 
    int XC, YC; // Position X Y de la souris lorsqu'ont clique

    bool DisplayUnrolledMenu = false; // si le menu est déroulé

public:

    //! \brief Constructeur de la classe Affichage
    Affichage();

    //! \brief Destructor de la classe Affichage
    ~Affichage();

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
    void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a);

    //! \brief Initialise tout les composants graphique SDL (Window, Font, Image, renderer)
    void InitAffichage();

    //! \brief Affiche les composants graphique de la simulation
    void AffichagePlateau();

    //! \brief Affiche les composants graphique du menu en bas
    void AffichageMenu();

    //! \brief Affiche le permis de l'utilisateur de la voiture (Nom, Prenom, Age, ParkTime, ID)
    //! \param Vind Indice de la voiture sur lequel on a cliqué
    //! \return int : Sert a savoir si on affiche ou non les infos
    int AffichageUserCard(unsigned int Vind);

    //! \brief Affiche les informations du parkings (Indice du parking, Prix de départ, Prix moyen, nombre de places dispo)
    //! \return int : Sert a savoir si on affiche ou non les infos 
    int AffichageParkingCard(unsigned int Parkind);

    //! \brief Affiche le menu pour choisir les différent graphique a afficher
    int AffichageGraphMenu();

    //! \brief boucle principal d'affichage de la simulation
    void AffichageSimulation();
};

#endif