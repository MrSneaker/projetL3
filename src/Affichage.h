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

class Affichage{

    private:
        Environnement environnement;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        
        //------------------------------- IMAGE -----------------------------------
      
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

        unsigned int  PauseX = 50;
        unsigned int  PauseY = 826;
        unsigned int  PauseW = 43;
        unsigned int  PauseH = 55;
        Image Pause;
        Image Play;

        unsigned int  SpeedUpX = 150;
        unsigned int  SpeedUpY = 826;
        unsigned int  SpeedUpW = 43;
        unsigned int  SpeedUpH = 55;
        Image SpeedUp;

        unsigned int  ExitX = 853;
        unsigned int  ExitY = 826;
        unsigned int  ExitW = 132;
        unsigned int  ExitH = 55;
        Image Exit;

        unsigned int MenuArrowX = 470;
        unsigned int MenuArrowY = 20;
        unsigned int MenuArrowW = 60;
        unsigned int MenuArrowH = 20;
        unsigned int MenuArrowAngle = 0;
        Image MenuArrow;



        SDL_Rect Place;


        bool quit;

        //------------------------------- TEXT -----------------------------------
        TTF_Font *font_default;
        TTF_Font *font_UserCard;
        TTF_Font *font_Time;
        TTF_Font *font_Calendar;

        int X = 0;
        int Y = 0;
        int Xm, Ym;
        int XC, YC;

        
        //Utile pour le temps et les frames

        int totalFrames = 0;

        int frames = 0;

        float frametime=0;

        int prevtime = 0;

        int currenttime = 0;

        float deltatime = 0.f;

        bool DisplayUnrolledMenu = false; // si le menu est déroulé




    public:
    
        vector<SDL_Rect> VoituresRect; // Tableau des rectangles des voitures (Pour plus tard)
        Affichage();
        ~Affichage();

        void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b, int a);

        void InitAffichage();

        void AffichagePlateau();

        void AffichageMenu();

        int AffichageUserCard(unsigned int Vind);

        int AffichageParkingCard(unsigned int Parkind);

        int AffichageGraphMenu();

        void AffichageSimulation();

};



#endif