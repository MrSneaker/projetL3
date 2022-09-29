#include "Affichage.h"

#include <iostream>

using namespace std;

Affichage::Affichage(){
    Environnement Env;
    Env.initParkings();
    environnement = Env;
}

Affichage::~Affichage(){

    TTF_CloseFont(font_default);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void Affichage::InitAffichage()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Park Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() < 0) {
        cout << "Erreur lors de l'initialisation de TTF" << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // FONTS
    font_default = TTF_OpenFont("font/arial.ttf", 24);

    if (font_default == nullptr) {
        cout << "Failed to load img/Arial.ttf in 24 SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);

    environnement.AddVoiture();
    environnement.voitures[0].set_position(Vec2(0,0));
    environnement.voitures[0].setTargetPosition(environnement.parkings[0].getPos());
    

}

void Affichage::AffichagePlateau()
{
    SDL_Rect Voiture1;
    Voiture1.x = environnement.voitures[0].get_position().x;
    Voiture1.y = environnement.voitures[0].get_position().y;
    Voiture1.w = 20;
    Voiture1.h = 20;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &Voiture1);

    SDL_Rect P1;
    P1.x = environnement.parkings[0].getPos().x;
    P1.y = environnement.parkings[0].getPos().y;
    P1.w = 100;
    P1.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &P1);

    SDL_Rect UpRoad;
    UpRoad.x = 450;
    UpRoad.y = 0;
    UpRoad.w = 100;
    UpRoad.h = 400;

    SDL_Rect DownRoad;
    DownRoad.x = 0;
    DownRoad.y = 400;
    DownRoad.w = 1000;
    DownRoad.h = 100;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &UpRoad);
    SDL_RenderFillRect(renderer, &DownRoad);

    for(int i =0; i <DimWindowX; i+=30)
    {
            SDL_Rect Place;
            Place.x = i;
            Place.y = 0;
            Place.w = 10;
            Place.h = 20;
        //Draw les place tout les 20px sauf en x entre 450 et 550
        if(i < 450 || i > 550)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &Place);
        }

    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i =0; i<DimWindowX; i+=10){
        SDL_RenderDrawLine(renderer, i, 0, i, DimWindowY);
    }
    for(int i =0; i<DimWindowY; i+=10){
        SDL_RenderDrawLine(renderer, 0, i, DimWindowX, i);
    }
    

}


void Affichage::AffichageSimulation()
{
    bool display = true;
    bool doit= true;
 
    InitAffichage();
    while (display)
    {
        this_thread::sleep_for(chrono::milliseconds(10));
       
        AffichagePlateau();

        //environnement.voitures[0].MoveToTargetPosition();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    display = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            display = false;
                            break;

                        case SDLK_SPACE:
                        if(!environnement.voitures[0].MoveToTargetPosition()){
                            
                        }
                            break;
                    }
                    break;
            }
        }


        
        /*
        if(environnement.voitures[0].MoveToTargetPosition() == false)
        {
            
        }
        else 
        {
            environnement.voitures[0].setTargetPosition(Vec2(680, 580));
        }*/
        

        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

    }
}