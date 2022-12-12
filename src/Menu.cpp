#include "Menu.h"

Menu::Menu() // on met toutes les textures à NULL.
{
}

Menu::~Menu()
{
}

void Menu::initMenu() // on initialise la SDL.
{

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Initialisation de l'écriture
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Park_Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Initialisation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "erreur lors de la création du rendu " << endl;
        SDL_Quit();
        exit(1);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);

    initTexture();
    initFont();
}

void Menu::initFont() // initialisation de la police.
{
    font_default = TTF_OpenFont("font/arial.ttf", 15);
}

void Menu::initTexture() // initialisation des textures.
{
    background.loadFromFile("img/background.png", renderer);
    startButton.loadFromFile("img/start.png", renderer);
    quitButton.loadFromFile("img/exit.png", renderer);
    settings.loadFromFile("img/settings.png",renderer);
}

void Menu::afficherMenu() // affichage du menu.
{
    background.draw(renderer, 0, 0, DimWindowX, DimWindowY, 0);
    startButton.draw(renderer, 350, 200, 300, 200, 0);
    quitButton.draw(renderer, 350, 500, 300, 200, 0);
    settings.draw(renderer,850,650,100,100,0);
    SDL_RenderPresent(renderer);
}

void Menu::destructMenu() // destruction de toute les instances SDL (sans SDL_Quit).
{
    TTF_CloseFont(font_default);
    TTF_Quit();
    background.~Image();
    startButton.~Image();
    quitButton.~Image();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Menu::launchSim()
{
    Affichage sim;
    sim.AffichageSimulation();
}

void Menu::menuLoop()
{
    initMenu();        // on initialise la SDL.
    bool quit = false; // condition du while.
    int x, y;          // position de la souris.
    x = 0;
    y = 0;
    afficherMenu(); // on affiche le Menu.
    while (!quit)
    {
        while (SDL_PollEvent(&events)) // boucle d'évènements SDL.
        {
            switch (events.type)
            {
            case SDL_QUIT:   // si on ferme la fenêtre..
                quit = true; // .. on ferme la fenêtre.
                break;
            case SDL_MOUSEBUTTONDOWN:                        // si on appuie sur un bouton de la souris..
                if (events.button.button == SDL_BUTTON_LEFT) // .. et que c'est le clique gauche..
                {
                    x = events.motion.x; // .. on récupère la position de la souris.
                    y = events.motion.y;
                }
                break;
            default:
                break;
            }
        }
        // Ici on tests si le clique de la souris était dans un bouton ou non.
        if ((x > 350) && (x < 350 + 300) && (y > 300) && (y < 300 + 200))
        {
            destructMenu(); // on efface le menu.
            launchSim();    // on lance la simulation.
            x = 0;          // on reset la position de la souris.
            y = 0;
            initMenu(); // on réinitialise le menu.
            initFont();
            initTexture();
        }

        else if ((x > 350) && (x < 350 + 300) && (y > 500) && (y < 500 + 200))
        { // on quitte le menu.
            quit = true;
        }
        afficherMenu(); // si aucune des conditions n'est remplies, on continue d'afficher le menu.
    }
    destructMenu(); // si on sort de la boucle, on détruit le menu.
    SDL_Quit();     // on quitte la SDL.
}