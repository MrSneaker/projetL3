#include "Menu.h"

Menu::Menu() // on met toutes les textures à NULL.
{
}

Menu::~Menu()
{
}

void Menu::initMenu() // on initialise la SDL.
{
    startButtonX = 350;
    startButtonY = 200;
    startButtonW = 300;
    startButtonH = 200;

    quitButtonX = 350;
    quitButtonY = 500;
    quitButtonW = 300;
    quitButtonH = 200;

    settingsX = 850;
    settingsY = 650;
    settingsW = 100;
    settingsH = 100;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
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
    settings.loadFromFile("img/settings.png", renderer);
}

void Menu::afficherMenu() // affichage du menu.
{
    background.draw(renderer, 0, 0, DimWindowX, DimWindowY, 0);
    startButton.draw(renderer, startButtonX, startButtonY, startButtonW, startButtonH, 0);
    quitButton.draw(renderer, quitButtonX, quitButtonY, quitButtonW, quitButtonH, 0);
    settings.draw(renderer, settingsX, settingsY, settingsW, settingsH, 0);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Menu::destructMenu() // destruction de toute les instances SDL (sans SDL_Quit).
{
    TTF_CloseFont(font_default);
    background.~Image();
    startButton.~Image();
    quitButton.~Image();
    settings.~Image();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
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
    bool click = false;
    int x, y; // position de la souris.
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
            case SDL_MOUSEMOTION:
                x = events.motion.x; // .. on récupère la position de la souris.
                y = events.motion.y; // si on bouge la souris.
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT) // on detecte le clique gauche.
                {
                    click = true;
                }
                break;
            default:
                break;
            }
        }
        // Ici on tests si le clique de la souris était dans un bouton ou non.
        if ((x > startButtonX) && (x < startButtonX + startButtonW) && (y > startButtonY) && (y < startButtonY + startButtonH) && click)
        {
            destructMenu(); // on efface le menu.
            launchSim();    // on lance la simulation.
            x = 0;          // on reset la position de la souris.
            y = 0;
            initMenu(); // on réinitialise le menu.
            click = false;
        }

        else if ((x > quitButtonX) && (x < quitButtonX + quitButtonW) && (y > quitButtonY) && (y < quitButtonY + quitButtonH) && click)
        { // on quitte le menu.
            quit = true;
        }
        afficherMenu(); // si aucune des conditions n'est remplies, on continue d'afficher le menu.
    }
    destructMenu(); // si on sort de la boucle, on détruit le menu.
    SDL_Quit();     // on quitte la SDL.
}