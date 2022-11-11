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

        int PauseX = 50;
        int PauseY = 830;
        int PauseW = 43;
        int PauseH = 55;
        Image Pause;
        Image Play;

        int SpeedUpX = 150;
        int SpeedUpY = 830;
        int SpeedUpW = 43;
        int SpeedUpH = 55;
        Image SpeedUp;


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

        void AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b);

        void InitAffichage();

        void AffichagePlateau();

        void AffichageMenu();

        void AffichageSimulation();

};



#endif