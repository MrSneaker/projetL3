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
    Pause.~Image();
    Play.~Image();
    SpeedUp.~Image();

    TTF_Quit();

    SDL_Quit();
}

// Affiche du texte selon l'entrée
void Affichage::AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b)
{

    // return;
    SDL_Color color = {r, g, b};
    const char *text = Msg.c_str();

    if (Msg == "")
    {
        ostringstream Val;
        Val << Valeur;
        string val = MsgWithValeur + Val.str();
        text = val.c_str();
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w, h = 24;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dstrect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Affichage::InitAffichage()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Park Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY + 100, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    SDL_RenderClear(renderer);

    // Donne au parkings une image
    P1.loadFromFile("img/P2.png", renderer);
    P2.loadFromFile("img/P1.png", renderer);
    P3.loadFromFile("img/P3.png", renderer);
    // Donne aux routes une image
    UpRoad.loadFromFile("img/UpRoad.png", renderer);
    DownRoad.loadFromFile("img/DownRoad.png", renderer);
    // Donne à voiture une image
    Voiture.loadFromFile("img/Voiture1.png", renderer);
    // Donne à pause une image
    Pause.loadFromFile("img/Pause.png", renderer);
    // Donne à play une image
    Play.loadFromFile("img/Play.png", renderer);
    // Donne à speedup une image
    SpeedUp.loadFromFile("img/SpeedUp.png", renderer);
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
    Menu.h = 100;
    SDL_SetRenderDrawColor(renderer, 255, 234, 177, 255);
    SDL_RenderFillRect(renderer, &Menu);
    SDL_Rect Banner;
    Banner.x = 0;
    Banner.y = 800;
    Banner.w = 1000;
    Banner.h = 10;
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &Banner);
    SDL_Rect Banner2;
    Banner2.x = 0;
    Banner2.y = 810;
    Banner2.w = 1000;
    Banner2.h = 5;
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &Banner2);

    // Affichage du bouton pause
    if (environnement.Pause == false)
    {
        Pause.draw(renderer, PauseX, PauseY, PauseW, PauseH, 0);
    }
    else
    {
        Play.draw(renderer, PauseX, PauseY, PauseW, PauseH, 0);
    }

    // Affichage du bouton speed
    SpeedUp.draw(renderer, SpeedUpX, SpeedUpY, SpeedUpW, SpeedUpH, 0);
    //--------------------------------------------------

    AfficherTexte(font_default, "", "", int(environnement.TempsEcoule), 900, 838, 0, 0, 0);
}

void Affichage::AffichageSimulation()
{
    bool display = true;
    int lanceSim = false;
    bool ispress = false;
    int x = 0;
    int y = 0;
    bool isapress = false;
    bool speedUp = false;

    float beginTick = SDL_GetTicks();

    InitAffichage();

    while (display)
    {

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
                // si la souris est sur le bouton pause / play
                if (Xm > 50 && Xm < 115 && Ym > 815 && Ym < 885)
                {
                    PauseX = 50 - 5 / 2;  // on decale le bouton de la moitier la largueur ajouté -> plus propre
                    PauseY = 830 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
                    PauseW = 43 + 5;      // on ajoute 5 de chaque coté
                    PauseH = 55 + 5;      // on ajoute 5 de chaque coté
                }
                else if (Xm > 150 && Xm < 215 && Ym > 815 && Ym < 885)
                {
                    SpeedUpX = 150 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
                    SpeedUpY = 830 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
                    SpeedUpW = 43 + 5;      // on ajoute 5 de chaque coté
                    SpeedUpH = 55 + 5;      // on ajoute 5 de chaque coté
                }
                else
                {
                    // on revient au valeur de base, sinon le bouton reste grandi
                    PauseX = 50;
                    PauseY = 830;
                    PauseW = 43;
                    PauseH = 55;
                    SpeedUpX = 150;
                    SpeedUpY = 830;
                    SpeedUpW = 43;
                    SpeedUpH = 55;
                }

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
                    environnement.SpeedUp = !environnement.SpeedUp;
                    break;
                }
                break;
            }
        }
        if (ispress == true)
        {
            //------------------ Bouton pause ------------------
            if (XC > 50 && XC < 115 && YC > 815 && YC < 885)
            {
                environnement.Pause = !environnement.Pause;
            }
            //--------------------------------------------------

            //------------------Info Utilisateur------------------
            if (environnement.Pause == true)
            {
                for (int i = 0; i < environnement.voitures.size(); i++)
                {
                    if (XC > environnement.voitures[i].get_position().x - 5 && XC < environnement.voitures[i].get_position().x + 5 && YC > environnement.voitures[i].get_position().y - 5 && YC < environnement.voitures[i].get_position().y + 5)
                    {
                        cout << "voiture : " << i << " touchée" << endl;
                        // TODO : Afficher les infos de l'utilisateur qui est dans la voiture
                    }
                }
            }
            //----------------------------------------------------

            //------------------ Bouton speed ------------------
            if (XC > 150 && XC < 215 && YC > 815 && YC < 885)
            {
                environnement.SpeedUp = !environnement.SpeedUp;
            }
            //--------------------------------------------------

            ispress = false;
        }

        // Si la valeur Is_in de la voiture est true on modifie la taille de la voiture
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

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}