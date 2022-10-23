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
    P1 = IMG_Load("img/P1.png");
    P1Texture = SDL_CreateTextureFromSurface(renderer, P1);
    SDL_FreeSurface(P1); // on libère la surface
    P2 = IMG_Load("img/P2.png");
    P2Texture = SDL_CreateTextureFromSurface(renderer, P2);
    SDL_FreeSurface(P2); // On libère la surface car on a créé la texture à partir de celle-ci (on a donc plus besoin de la surface)
    P3 = IMG_Load("img/P3.png");
    P3Texture = SDL_CreateTextureFromSurface(renderer, P3);
    SDL_FreeSurface(P3); // On libère la surface pour éviter les fuites de mémoire

    // Donne aux routes une image
    UpRoad = IMG_Load("img/UpRoad.png"); // Route verticale
    textureUpRoad = SDL_CreateTextureFromSurface(renderer, UpRoad);
    SDL_FreeSurface(UpRoad);
    DownRoad = IMG_Load("img/DownRoad.png"); // Route horizontale
    textureDownRoad = SDL_CreateTextureFromSurface(renderer, DownRoad);
    SDL_FreeSurface(DownRoad);

    Voiture.loadFromFile("img/Voiture1.png", renderer);

    environnement.parkings[0].getPlacesTab()[21].setIsTaken(true);
}

void Affichage::AffichagePlateau()
{
    // Test Affichage

    // ------------------ Affiche l'image des parkings ------------------

    SDL_Rect P1;
    P1.x = environnement.parkings[1].getPos().x * 10 - 10;
    P1.y = environnement.parkings[1].getPos().y * 10 - 10;
    P1.w = 440;
    P1.h = 390;
    SDL_RenderCopy(renderer, P1Texture, NULL, &P1);

    SDL_Rect P2;
    P2.x = environnement.parkings[0].getPos().x * 10 - 10;
    P2.y = environnement.parkings[0].getPos().y * 10 - 10;
    P2.w = 440;
    P2.h = 390;
    SDL_RenderCopy(renderer, P2Texture, NULL, &P2);

    SDL_Rect P3;
    P3.x = environnement.parkings[2].getPos().x * 10 - 10;
    P3.y = environnement.parkings[2].getPos().y * 10 - 10;
    P3.w = 1000;
    P3.h = 290;
    SDL_RenderCopy(renderer, P3Texture, NULL, &P3);

    //------------------ Affiche les routes ------------------
    SDL_Rect UpRoad;
    UpRoad.x = 440;
    UpRoad.y = 0;
    UpRoad.w = 120;
    UpRoad.h = 400;
    SDL_RenderCopy(renderer, textureUpRoad, NULL, &UpRoad);

    SDL_Rect DownRoad;
    DownRoad.x = 0;
    DownRoad.y = 390;
    DownRoad.w = 1000;
    DownRoad.h = 120;
    SDL_RenderCopy(renderer, textureDownRoad, NULL, &DownRoad);

    //------------------ Affiche les voitures ------------------
    for (int i = 0; i < environnement.voitures.size(); i++)
    {
        unsigned int w = environnement.voitures[i].getwidth();
        unsigned int h = environnement.voitures[i].getheight();
        unsigned int x = environnement.voitures[i].get_position().x - w / 2;
        unsigned int y = environnement.voitures[i].get_position().y - h / 2;

        Voiture.draw(renderer, x, y, w, h);
    }

    //------------------ Affiche les places de chaques parkings ------------------
    for (int j = 0; j < environnement.parkings.size(); j++)
    {

        for (int i = 0; i < environnement.parkings[j].getNbPlaces(); i++)
        {

            Place.x = environnement.parkings[j].getPlacesTab()[i].getPos().x * 10;
            Place.y = environnement.parkings[j].getPlacesTab()[i].getPos().y * 10;
            Place.w = 10;
            Place.h = 20;

            // Si la place est prise, on affiche une place rouge
            if (environnement.parkings[j].getPlacesTab()[i].getIsTaken())
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
        // Affiche la taille de detection des parkings
        SDL_Rect Park;
        Park.x = environnement.parkings[j].getPos().x * 10;
        Park.y = environnement.parkings[j].getPos().y * 10;
        Park.w = environnement.parkings[j].getDIMX() * 10;
        Park.h = environnement.parkings[j].getDIMY() * 10;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &Park);
    }

    // Affiche si la case est un obstacle ou non
    /*
    for(int x = 0; x < DimWindowX/tailleCase; x++)
    {
        for(int y = 0; y < DimWindowY/tailleCase; y++)
        {
            if(x+y*DimWindowX/tailleCase == 47 || x+y*DimWindowX/tailleCase == 4299 || x+y*DimWindowX/tailleCase == 1951 )
            {
                SDL_Rect Obstacle;
                Obstacle.x = x*tailleCase;
                Obstacle.y = y*tailleCase;
                Obstacle.w = tailleCase;
                Obstacle.h = tailleCase;
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &Obstacle);
            }
            else if(environnement.nodes[x+DimWindowX/tailleCase*y]->getisObstacle() == true)
            {
                SDL_Rect rect;
                rect.x = environnement.nodes[x+DimWindowX/tailleCase*y]->getNodepos().x*10;
                rect.y = environnement.nodes[x+DimWindowX/tailleCase*y]->getNodepos().y*10;
                rect.w = 10;
                rect.h = 10;
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else
            {
                SDL_Rect rect;
                rect.x = environnement.nodes[x+DimWindowX/tailleCase*y]->getNodepos().x*10;
                rect.y = environnement.nodes[x+DimWindowX/tailleCase*y]->getNodepos().y*10;
                rect.w = 10;
                rect.h = 10;
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                SDL_RenderDrawRect(renderer, &rect);
            }

        }
    }*/

    for (int i = 0; i < environnement.voitures.size(); i++)
    {
        for (int j = 0; j < environnement.voitures[i].getpathTab().size(); j++)
        {
            SDL_Rect rect;
            rect.x = environnement.voitures[i].getpathTab()[j]->getNodepos().x * 10;
            rect.y = environnement.voitures[i].getpathTab()[j]->getNodepos().y * 10;
            rect.w = 10;
            rect.h = 10;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

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
    bool doit = true;
    int lanceSim = false;
    bool ispress = false;
    bool ispressR = false;
    bool ispressL = false;
    int x = 0;
    int y = 0;
    bool isapress = false;

    InitAffichage();

    while (display)
    {
        this_thread::sleep_for(chrono::milliseconds(10));

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
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    XC = event.button.x;
                    YC = event.button.y;
                    ispressR = true;
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
                    environnement.AddVoiture();
                    lanceSim = true;
                    // Juste pour tester et pour fun xD
                    // int indice = environnement.random(0, 3);
                    // environnement.voitures[environnement.voitures.size() - 1].setTargetPosition(environnement.parkings[indice].getPlacesTab()[environnement.random(0, environnement.parkings[indice].getPlacesTab().size())].getPos()*Vec2(10, 10));
                    break;
                }
                break;
            }
        }
        if (ispress == true)
        {
            for (int i = 0; i < environnement.nodes.size(); i++)
            {
                if (XC >= environnement.nodes[i]->getNodepos().x * 10 && XC <= environnement.nodes[i]->getNodepos().x * 10 + 10 && YC >= environnement.nodes[i]->getNodepos().y * 10 && YC <= environnement.nodes[i]->getNodepos().y * 10 + 10)
                {

                    cout << "indice du noeud : " << i << endl;
                    if (ispressL == true)
                    {
                        X = i;
                    }
                    else if (ispressR == true)
                    {
                        Y = i;
                    }

                    else if (isapress == true)
                    {

                        environnement.nodes[i]->setisObstacle(true);
                        if (environnement.nodes[i]->getisObstacle() == true)
                        {
                            cout << "noeud : " << i << " est bien un obstacle" << endl;
                        }
                    }

                    // change sur le fichier map.txt
                }
            }

            ispressL = false;
            ispressR = false;
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
        if (lanceSim == true)
        {
            for(int i = 0; i < environnement.voitures.size(); i++)
            {
                environnement.Astar(environnement.voitures[i], 47, environnement.GetNodeIndbyPos(environnement.voitures[i].getTargetPosition()));
                
                lanceSim = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}