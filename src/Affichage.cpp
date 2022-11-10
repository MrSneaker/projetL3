#include "Affichage.h"

#include <iostream>

using namespace std;

Affichage::Affichage()
{
}

Affichage::~Affichage()
{

    TTF_CloseFont(font_default);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    P1.~Image();
    P2.~Image();
    P3.~Image();
    UpRoad.~Image();
    DownRoad.~Image();
    Voiture.~Image();

    TTF_Quit();

    SDL_Quit();
}

void Affichage::InitAffichage()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Park Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY + 50, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() < 0)
    {
        cout << "Erreur lors de l'initialisation de TTF" << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // FONTS
    font_default = TTF_OpenFont("font/arial.ttf", 24);

    if (font_default == nullptr)
    {
        cout << "Failed to load img/Arial.ttf in 24 SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Fonction qui permet de load des images
    IMG_Init(IMG_INIT_PNG);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);

    // Donne au parkings une image
    P1.loadFromFile("img/P2.png", renderer);
    P2.loadFromFile("img/P1.png", renderer);
    P3.loadFromFile("img/P3.png", renderer);
    // Donne aux routes une image
    UpRoad.loadFromFile("img/UpRoad.png", renderer);
    DownRoad.loadFromFile("img/DownRoad.png", renderer);
    Voiture.loadFromFile("img/Voiture1.png", renderer);
}

void Affichage::AffichagePlateau()
{
    // Test Affichage

    // ------------------ Affiche l'image des parkings ------------------

    P1.draw(renderer, environnement.parkings[0].getPos().x * 10 - 10, environnement.parkings[0].getPos().y * 10 - 10, 440, 390, 0);
    P2.draw(renderer, environnement.parkings[1].getPos().x * 10 - 10, environnement.parkings[1].getPos().y * 10 - 10, 440, 390, 0);

    P3.draw(renderer, environnement.parkings[2].getPos().x * 10 - 10, environnement.parkings[2].getPos().y * 10 - 10, 1000, 290, 0);
    //------------------ Affiche les routes ------------------

    UpRoad.draw(renderer, 440, 0, 120, 400, 0);
    DownRoad.draw(renderer, 0, 390, 1000, 120, 0);

    //------------------ Affiche les voitures ------------------
    // Avec l'anlge
    for (int i = 0; i < environnement.voitures.size(); i++)
    {

        unsigned int w = environnement.voitures[i].getwidth();
        unsigned int h = environnement.voitures[i].getheight();
        unsigned int x = environnement.voitures[i].get_position().x - w / 2;
        unsigned int y = environnement.voitures[i].get_position().y - h / 2;
        int angle = environnement.voitures[i].getAngle();

        Voiture.draw(renderer, x, y, w, h, angle);
    }

    //------------------ Affiche les places de chaques parkings ------------------
    for (int j = 0; j < environnement.parkings.size(); j++)
    {

        for (int i = 0; i < environnement.parkings[j].getPlacesTab().size(); i++)
        {
            // cout<<"size parking j : "<<j<<" : "<<environnement.parkings[j].getPlacesTab().size()<<endl;

            Place.x = environnement.parkings[j].getPlacesTab()[i].getPos().x * 10;
            Place.y = environnement.parkings[j].getPlacesTab()[i].getPos().y * 10;
            Place.w = 10;
            Place.h = 20;

            if (environnement.parkings[j].getPlacesTab()[i].getIsTaken() == true)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &Place);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &Place);
            }
        }
    }

    // for (int i = 0; i < environnement.voitures.size(); i++)
    // {
    //     for (int j = 0; j < environnement.voitures[i].getpathTab().size(); j++)
    //     {
    //         SDL_Rect rect;
    //         rect.x = environnement.voitures[i].getpathTab()[j]->getNodepos().x * 10;
    //         rect.y = environnement.voitures[i].getpathTab()[j]->getNodepos().y * 10;
    //         rect.w = 10;
    //         rect.h = 10;
    //         SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //         SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    //         SDL_RenderFillRect(renderer, &rect);
    //     }
    // }

    //------------------ Affiche menu ------------------
    SDL_Rect Menu;
    Menu.x = 0;
    Menu.y = 800;
    Menu.w = 1000;
    Menu.h = 50;
    SDL_SetRenderDrawColor(renderer, 193, 163, 163, 255);
    SDL_RenderFillRect(renderer, &Menu);
}

void Affichage::AffichageSimulation()
{
    bool display = true;
    int lanceSim = false;
    bool ispress = false;
    int x = 0;
    int y = 0;
    bool isapress = false;

    float beginTick = SDL_GetTicks();

    InitAffichage();

    while (display)
    {
         // Affiche les fps dans la console
        
        
        //===============Afficher le temps===================================================

        environnement.temps = ((SDL_GetTicks() - beginTick)); // récup le temps toute les secondes

       


        AffichagePlateau();
        environnement.Environnement_play();

        int Xm, Ym;
        int XC, YC;

        // Gestion des evenements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // detecte la mouvement de la souris
            case SDL_MOUSEMOTION:
                Xm = event.motion.x;
                Ym = event.motion.y;

                break;
            case SDL_MOUSEBUTTONDOWN:
                ispress = true;
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    XC = event.button.x;
                    YC = event.button.y;
                    isapress = true;
                }
                break;
            case SDL_QUIT:
                display = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    display = false;
                    break;
                case SDLK_SPACE:
                    lanceSim = true;
                    break;
                }
                break;
            }
        }
        if (ispress == true)
        {
                    if (isapress == true)
                    {
                        cout<<"X : "<<XC<<" Y : "<<YC<<endl;
                        environnement.AddVoiture();
                    }

            isapress = false;
            ispress = false;
        }

        // Si la valeur Is_in de la voiture est true on modifie la taille de la voiture
        // TODO : Faire en sorte que chaques voitures changent de taille independament
        for (int i = 0; i < environnement.voitures.size(); i++)
        {
            if (environnement.voitures[i].getIs_in())
            {
                environnement.voitures[i].setwidth(10);
                environnement.voitures[i].setheight(20);
            }
            else
            {
                environnement.voitures[i].setwidth(20);
                environnement.voitures[i].setheight(30);
            }
        }

        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}