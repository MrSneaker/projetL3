#include "Menu.h"

Menu::Menu() // on met toutes les textures à NULL.
{
    startButtonX = 350;
    startButtonY = 150;
    startButtonW = 300;
    startButtonH = 150;

    quitButtonX = 350;
    quitButtonY = 550;
    quitButtonW = 300;
    quitButtonH = 150;

    settingsX = 350;
    settingsY = 350;
    settingsW = 300;
    settingsH = 150;

    price1 = 8;
    defPrice1 = 8;

    price2 = 8;
    defPrice2 = 8;

    price3 = 8;
    defPrice3 = 8;

    userPrice = 10;
    defUserPrice = 10;

    userPriceInf = 4;
    defUserPriceInf = 4;

    tpsAppVoiture = 5;
    defTpsApp = 5;
}

Menu::~Menu()
{
}

void Menu::initMenu() // on initialise la SDL.
{
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
    font_default = TTF_OpenFont("font/arial.ttf", 50);
    font_param = TTF_OpenFont("font/arial.ttf", 30);
}

void Menu::initTexture() // initialisation des textures.
{
    background.loadFromFile("img/background.png", renderer);
    startButton.loadFromFile("img/start.png", renderer);
    quitButton.loadFromFile("img/exitMenu.png", renderer);
    settings.loadFromFile("img/settings.png", renderer);
    plus.loadFromFile("img/plus.png", renderer);
    minus.loadFromFile("img/minus.png", renderer);
    settingsBack.loadFromFile("img/settingsBack.png", renderer);
    okButton.loadFromFile("img/OK.png", renderer);
    cancelButton.loadFromFile("img/cancel.png", renderer);
    clearButton.loadFromFile("img/clear.png", renderer);
}

void Menu::showMenu() // affichage du menu.
{
    background.draw(renderer, 0, 0, DimWindowX, DimWindowY, 0);
    startButton.draw(renderer, startButtonX, startButtonY, startButtonW, startButtonH, 0);
    quitButton.draw(renderer, quitButtonX, quitButtonY, quitButtonW, quitButtonH, 0);
    settings.draw(renderer, settingsX, settingsY, settingsW, settingsH, 0);
}

void Menu::destructMenu() // destruction de toute les instances SDL (sans SDL_Quit).
{
    TTF_CloseFont(font_default);
    TTF_CloseFont(font_param);
    background.~Image();
    startButton.~Image();
    quitButton.~Image();
    settings.~Image();
    minus.~Image();
    plus.~Image();
    settingsBack.~Image();
    okButton.~Image();
    cancelButton.~Image();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
}

void Menu::launchSim()
{
    Environnement env(price1, price2, price3, userPrice, userPriceInf, tpsAppVoiture);
    Affichage sim(env);
    sim.AffichageSimulation();
}

void Menu::setToDef()
{
    price1 = defPrice1;
    price2 = defPrice2;
    price3 = defPrice3;
    userPrice = defUserPrice;
    userPriceInf = defUserPriceInf;
    tpsAppVoiture = defTpsApp;
}

void Menu::saveValue()
{
    defPrice1 = price1;
    defPrice2 = price2;
    defPrice3 = price3;
    defUserPrice = userPrice;
    defUserPriceInf = userPriceInf;
    defTpsApp = tpsAppVoiture;
}

void Menu::afficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, unsigned char r, unsigned char g, unsigned char b, int a)
{

    // return;
    SDL_Color color = {r, g, b};
    const char *text = Msg.c_str(); // convertir string en char

    if (Msg == "")
    {
        ostringstream Val;                      // convertir float en string
        Val << Valeur;                          //
        string val = MsgWithValeur + Val.str(); // concatener les deux strings
        text = val.c_str();
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_SetSurfaceAlphaMod(surface, a);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w = w;
    int h = h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dstrect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Menu::showSettings()
{
    settingsBack.draw(renderer, 150, 50, 700, 700, 0);
    afficherTexte(font_default, "Settings", "", 0, 400, 70, 255, 255, 255, 255);

    afficherTexte(font_param, "Prix de depart parking 1 :", "", 0, 200, 130, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", price1, 550, 130, 255, 255, 255, 255);
    plus.draw(renderer, 670, 130, 30, 30, 0);
    minus.draw(renderer, 630, 140, 30, 10, 0);

    afficherTexte(font_param, "Prix de depart parking 2 :", "", 0, 200, 170, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", price2, 550, 170, 255, 255, 255, 255);
    plus.draw(renderer, 670, 170, 30, 30, 0);
    minus.draw(renderer, 630, 180, 30, 10, 0);

    afficherTexte(font_param, "Prix de depart parking 3 :", "", 0, 200, 210, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", price3, 550, 210, 255, 255, 255, 255);
    plus.draw(renderer, 670, 210, 30, 30, 0);
    minus.draw(renderer, 630, 220, 30, 10, 0);

    afficherTexte(font_param, "Temps d'apparition voiture(sec) :", "", 0, 200, 270, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", tpsAppVoiture, 640, 270, 255, 255, 255, 255);
    plus.draw(renderer, 750, 270, 30, 30, 0);
    minus.draw(renderer, 710, 280, 30, 10, 0);

    afficherTexte(font_param, "Prix max possible utilisateurs :", "", 0, 200, 330, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", userPrice, 615, 330, 255, 255, 255, 255);
    plus.draw(renderer, 720, 330, 30, 30, 0);
    minus.draw(renderer, 680, 340, 30, 10, 0);

    afficherTexte(font_param, "Prix min possible utilisateurs :", "", 0, 200, 370, 255, 255, 255, 255);
    afficherTexte(font_param, "", "", userPriceInf, 615, 370, 255, 255, 255, 255);
    plus.draw(renderer, 720, 370, 30, 30, 0);
    minus.draw(renderer, 680, 380, 30, 10, 0);

    afficherTexte(font_param, "Reset data utilisateur :", "", 0, 200, 430, 255, 255, 255, 255);
    clearButtonX = 520;
    clearButtonY = 410;
    clearButtonW = 100;
    clearButtonH = 75;
    clearButton.draw(renderer, clearButtonX, clearButtonY, clearButtonW, clearButtonH, 0);

    plus.draw(renderer, 720, 370, 30, 30, 0);
    minus.draw(renderer, 680, 380, 30, 10, 0);

    okButtonX = 700;
    okButtonY = 650;
    okButtonW = 100;
    okButtonH = 75;
    okButton.draw(renderer, okButtonX, okButtonY, okButtonW, okButtonH, 0);

    cancelButtonX = 500;
    cancelButtonY = 650;
    cancelButtonW = 100;
    cancelButtonH = 75;
    cancelButton.draw(renderer, cancelButtonX, cancelButtonY, cancelButtonW, cancelButtonH, 0);
}

void Menu::menuLoop()
{
    initMenu();        // on initialise la SDL.
    bool quit = false; // condition du while.
    bool showSet = false;
    int xc, yc, xm, ym; // position de la souris.
    xc = 0;
    yc = 0;
    xm = 0;
    ym = 0;
    showMenu(); // on affiche le Menu.
    while (!quit)
    {
        showMenu();                    // si aucune des conditions n'est remplies, on continue d'afficher le menu.
        while (SDL_PollEvent(&events)) // boucle d'évènements SDL.
        {
            switch (events.type)
            {
            case SDL_QUIT:   // si on ferme la fenêtre..
                quit = true; // .. on ferme la fenêtre.
                break;
            case SDL_MOUSEMOTION:
                xm = events.motion.x;
                ym = events.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT) // on detecte le clique gauche.
                {
                    xc = events.motion.x; // .. on récupère la position de la souris.
                    yc = events.motion.y;
                }
                break;
            default:
                break;
            }
        }
        // Ici on tests si le clique de la souris était dans un bouton ou non.
        if ((xc > startButtonX) && (xc < startButtonX + startButtonW) && (yc > startButtonY) && (yc < startButtonY + startButtonH) && !showSet)
        {
            destructMenu(); // on efface le menu.
            launchSim();    // on lance la simulation.
            xc = 0;         // on reset la position de la souris.
            yc = 0;
            initMenu(); // on réinitialise le menu.
        }
        else if ((xc > settingsX) && (xc < settingsX + settingsW) && (yc > settingsY) && (yc < settingsY + settingsH) && !showSet)
        {
            showSet = true;
            xc = 0;
            yc = 0;
        }
        else if ((xc > quitButtonX) && (xc < quitButtonX + quitButtonW) && (yc > quitButtonY) && (yc < quitButtonY + quitButtonH) && !showSet)
        { // on quitte le menu.
            quit = true;
        }
        if (showSet)
        {
            showSettings();
            if (xc > okButtonX && xc < okButtonX + okButtonW && yc > okButtonY && yc < okButtonY + okButtonH)
            {
                saveValue();
                showSet = false;
                xc = 0;
                yc = 0;
            }
            else if (xc > cancelButtonX && xc < cancelButtonX + cancelButtonW && yc > cancelButtonY && yc < cancelButtonY + cancelButtonH)
            {
                setToDef();
                showSet = false;
                xc = 0;
                yc = 0;
            }
            else if (xc > 670 && xc < 670 + 30 && yc > 130 && yc < 130 + 30)
            {
                price1 += 0.5;
                xc = 0;
                yc = 0;
            }
            else if (xc > 630 && xc < 630 + 40 && yc > 135 && yc < 135 + 25)
            {
                price1 -= 0.5;
                if (price1 < 0.5)
                {
                    price1 = 0.5;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > 670 && xc < 670 + 30 && yc > 170 && yc < 170 + 30)
            {
                price2 += 0.5;
                xc = 0;
                yc = 0;
            }
            else if (xc > 630 && xc < 630 + 40 && yc > 175 && yc < 175 + 25)
            {
                price2 -= 0.5;
                if (price2 < 0.5)
                {
                    price2 = 0.5;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > 670 && xc < 670 + 30 && yc > 210 && yc < 210 + 30)
            {
                price3 += 0.5;
                xc = 0;
                yc = 0;
            }
            else if (xc > 630 && xc < 630 + 40 && yc > 215 && yc < 215 + 25)
            {
                price3 -= 0.5;
                if (price3 < 0.5)
                {
                    price3 = 0.5;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > 750 && xc < 750 + 30 && yc > 270 && yc < 270 + 30)
            {
                tpsAppVoiture += 0.5;
                xc = 0;
                yc = 0;
            }
            else if (xc > 710 && xc < 710 + 40 && yc > 275 && yc < 275 + 25)
            {
                tpsAppVoiture -= 0.5;
                if (tpsAppVoiture < 2)
                {
                    tpsAppVoiture = 2;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > 720 && xc < 720 + 30 && yc > 330 && yc < 330 + 30)
            {
                userPrice += 0.5;
                xc = 0;
                yc = 0;
            }
            else if (xc > 680 && xc < 680 + 40 && yc > 335 && yc < 335 + 25)
            {
                userPrice -= 0.5;
                if (userPrice < 2)
                {
                    userPrice = 2;
                }
                else if (userPrice < userPriceInf)
                {
                    userPriceInf -= 0.5;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > 720 && xc < 720 + 30 && yc > 370 && yc < 370 + 30)
            {
                userPriceInf += 0.5;
                xc = 0;
                yc = 0;
                if (userPriceInf > userPrice)
                {
                    userPrice += 0.5;
                }
            }
            else if (xc > 680 && xc < 680 + 40 && yc > 375 && yc < 375 + 25)
            {
                userPriceInf -= 0.5;
                if (userPriceInf < 2)
                {
                    userPriceInf = 2;
                }
                xc = 0;
                yc = 0;
            }
            else if (xc > clearButtonX && xc < clearButtonX + clearButtonW && yc > clearButtonY && yc < clearButtonY + clearButtonH)
            {
                if (std::filesystem::exists("data/User.txt"))
                    system("rm data/User.txt");
            }
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    destructMenu(); // si on sort de la boucle, on détruit le menu.
    SDL_Quit();     // on quitte la SDL.
}