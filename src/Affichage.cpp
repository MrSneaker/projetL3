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
    Voiture2.~Image();
    Voiture3.~Image();
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
    const char *text = Msg.c_str(); // convertir string en char

    if (Msg == "")
    {
        ostringstream Val;                      // convertir float en string
        Val << Valeur;                          //
        string val = MsgWithValeur + Val.str(); // concatener les deux strings
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

    font_UserCard = TTF_OpenFont("font/arial.ttf", 12);

    if (font_UserCard == nullptr)
    {
        cout << "Failed to load img/Arial.ttf in 12 SDL_TTF Error: " << TTF_GetError() << endl;
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
    Voiture2.loadFromFile("img/Voiture2.png", renderer);
    Voiture3.loadFromFile("img/Voiture3.png", renderer);
    // Donne à pause une image
    Pause.loadFromFile("img/Pause.png", renderer);
    // Donne à play une image
    Play.loadFromFile("img/Play.png", renderer);
    // Donne à speedup une image
    SpeedUp.loadFromFile("img/SpeedUp.png", renderer);
    // Donne à Exit une image
    Exit.loadFromFile("img/Exit.png", renderer);
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
    // Avec l'angle
    for (int i = 0; i < environnement.voitures.size(); i++)
    {
        unsigned int w = environnement.voitures[i].getwidth();
        unsigned int h = environnement.voitures[i].getheight();
        unsigned int x = environnement.voitures[i].get_position().x - w / 2;
        unsigned int y = environnement.voitures[i].get_position().y - h / 2;
        int angle = environnement.voitures[i].getAngle();

        switch (environnement.voitures[i].CarColor)
        {
        case 0:
            Voiture.draw(renderer, x, y, w, h, angle);
            break;
        case 1:
            Voiture2.draw(renderer, x, y, w, h, angle);
            break;
        case 2:
            Voiture3.draw(renderer, x, y, w, h, angle);
            break;
        }
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
    //    for (int j = 0; j < environnement.voitures[i].getpathTab().size(); j++)
    //    {
    //        SDL_Rect rect;
    //        rect.x = environnement.voitures[i].getpathTab()[j]->getNodepos().x * 10;
    //        rect.y = environnement.voitures[i].getpathTab()[j]->getNodepos().y * 10;
    //        rect.w = 10;
    //        rect.h = 10;
    //        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    //        SDL_RenderFillRect(renderer, &rect);
    //    }
    // }

    //------------------ Affiche menu ----------------------------------------------------
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

    // SDL_RenderDrawLine(renderer, 0, 857.5, 1000, 857.5);

    // Affichage du temps
    AfficherTexte(font_default, "", "", int(environnement.Secondes), 566, 845.5, 0, 0, 0);
    // Si Minutes > 0 afficher Minutes
    if (environnement.Minutes > 0)
    {
        AfficherTexte(font_default, ":", "", 0, 554, 845.5, 0, 0, 0);
        AfficherTexte(font_default, "", "", int(environnement.Minutes), 522, 845.5, 0, 0, 0);
    }
    // Si Heures > 0 afficher Heures
    if (environnement.Heures > 0)
    {
        AfficherTexte(font_default, ":", "", 0, 510, 845.5, 0, 0, 0);
        AfficherTexte(font_default, "", "", int(environnement.Heures), 478, 845.5, 0, 0, 0);
    }
    // Si Jours > 0 afficher Jours
    if (environnement.Jours > 0)
    {
        AfficherTexte(font_default, ":", "", 0, 466, 845.5, 0, 0, 0);
        AfficherTexte(font_default, "", "", int(environnement.Jours), 434, 845.5, 0, 0, 0);
    }

    // Si Mois > 0 afficher Mois
    if (environnement.Mois > 0)
    {
        AfficherTexte(font_default, ":", "", 0, 422, 845.5, 0, 0, 0);
        AfficherTexte(font_default, "", "", int(environnement.Mois), 390, 845.5, 0, 0, 0);
    }

    // Boutton Exit
    Exit.draw(renderer, ExitX, ExitY, ExitW, ExitH, 0);

    //---------------------------------------------------------------------------------------
}

int Affichage::AffichageUserCard(unsigned int Vind)
{

    SDL_Rect UserCard;
    UserCard.x = environnement.voitures[Vind].get_position().x;
    UserCard.y = environnement.voitures[Vind].get_position().y-150;
    UserCard.w = 100;
    UserCard.h = 150;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &UserCard);

    //on affiche son nom
    AfficherTexte(font_UserCard, environnement.voitures[Vind].User.getName(), "", 0, UserCard.x + 10, UserCard.y + 10, 0, 0, 0);
    //on affiche son Age 
    AfficherTexte(font_UserCard, "", "Age: ", environnement.voitures[Vind].User.getAge(), UserCard.x + 10, UserCard.y + 30, 0, 0, 0);
    //on affiche son temps de stationnement
    AfficherTexte(font_UserCard, "", "ParkTime: ", environnement.voitures[Vind].User.getParkTime(), UserCard.x + 10, UserCard.y + 50, 0, 0, 0);
    //on affiche son prix max
    AfficherTexte(font_UserCard, "", "Prix max: ", environnement.voitures[Vind].User.getMaxPrice(), UserCard.x + 10, UserCard.y + 70, 0, 0, 0);


    //Si on clic en haut a droite de la carte on la supprime
    AfficherTexte(font_UserCard, "X", "", 0, UserCard.x + 90, UserCard.y, 0, 0, 0);
    if(XC > UserCard.x + 90 && XC < UserCard.x + 100 && YC > UserCard.y && YC < UserCard.y + 10)
    {
        return -1;
    }

    return 0;
}

void Affichage::AffichageSimulation()
{
    bool display = true;
    bool ispress = false;
    bool speedUp = false;
    bool DisplayUserCard = false;
    int CarInd = 0;

    float beginTick = SDL_GetTicks();

    InitAffichage();

    while (display)
    {

        environnement.temps = ((SDL_GetTicks() - beginTick)); // récup le temps toute les secondes

        AffichagePlateau();
        environnement.Environnement_play();

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

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    XC = event.button.x;
                    YC = event.button.y;
                    ispress = true;
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
                    break;
                case SDLK_p:

                    break;
                }
                break;
            }
        }
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
        else if (Xm > 853 && Xm < 985 && Ym > 815 && Ym < 885)
        {
            ExitX = 853 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
            ExitY = 830 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
            ExitW = 132 + 5;     // on ajoute 5 de chaque coté
            ExitH = 55 + 5;      // on ajoute 5 de chaque coté
        }
        else
        {
            PauseX = 50;
            PauseY = 830;
            PauseW = 43;
            PauseH = 55;
            SpeedUpX = 150;
            SpeedUpY = 830;
            SpeedUpW = 43;
            SpeedUpH = 55;
            ExitX = 853;
            ExitY = 830;
            ExitW = 132;
            ExitH = 55;
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
                    int VX = environnement.voitures[i].get_position().x;
                    int VY = environnement.voitures[i].get_position().y;
                    int VW = environnement.voitures[i].getwidth();
                    int VH = environnement.voitures[i].getheight();
                    // Si on clique sur une voiture
                    if (environnement.voitures[i].getAngle() == 90 || environnement.voitures[i].getAngle() == 270)
                    {
                        if (XC > VX - VH / 2 && XC < VX + VH / 2 && YC > VY - VW / 2 && YC < VY + VW / 2)
                        {
                            cout<<"voiture "<<i<<endl;
                            DisplayUserCard = true;
                            CarInd = i;
                        }

                    }
                    else
                    {
                        if (XC > VX - VW / 2 && XC < VX + VW / 2 && YC > VY - VH / 2 && YC < VY + VH / 2)
                        {
                            cout << "Voiture : " << i << endl;
                            DisplayUserCard = true;
                            CarInd = i;
                        }

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

            //------------------ Bouton Exit ------------------
            if (XC > 853 && XC < 985 && YC > 815 && YC < 885)
            {
                display = false;
            }
            //--------------------------------------------------

            ispress = false;
        }

        if(DisplayUserCard == true)
        {
            if(AffichageUserCard(CarInd) == -1)
                DisplayUserCard = false;
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}
