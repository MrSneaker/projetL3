
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
    Exit.~Image();
    SpeedUp.~Image();
    UserCard.~Image();
    ParkSheet.~Image();
    Clock.~Image();
    Calendar.~Image();

    TTF_Quit();

    SDL_Quit();
}

// Affiche du texte selon l'entrée
void Affichage::AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b, int a)
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

    font_Time = TTF_OpenFont("font/arial.ttf", 18);

    if (font_Time == nullptr)
    {
        cout << "Failed to load img/Arial.ttf in 18 SDL_TTF Error: " << TTF_GetError() << endl;
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

    font_Calendar = TTF_OpenFont("font/arial.ttf", 9);

    if (font_Calendar == nullptr)
    {
        cout << "Failed to load img/Arial.ttf in 9 SDL_TTF Error: " << TTF_GetError() << endl;
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
    // Donne à UserCard une image
    UserCard.loadFromFile("img/UserCard.png", renderer);
    // Donne à ParkSheet une image
    ParkSheet.loadFromFile("img/ParkSheet.png", renderer);
    // Donne à Clock une image
    Clock.loadFromFile("img/Clock.png", renderer);
    // Donne à Calendar une image
    Calendar.loadFromFile("img/Calendar.png", renderer);
    // Donne à MenuArrow une image
    MenuArrow.loadFromFile("img/MenuArrow.png", renderer);
}

void Affichage::AffichagePlateau()
{
    // Test Affichage

    // ------------------ Affiche l'image des parkings ------------------

    P1.draw(renderer, environnement.parkings[0].getPos().x * 10 - 10, environnement.parkings[0].getPos().y * 10 - 10,
            environnement.parkings[0].getDIMX() * 10, environnement.parkings[0].getDIMY() * 10 + 10, 0);
    P2.draw(renderer, environnement.parkings[1].getPos().x * 10 - 10, environnement.parkings[1].getPos().y * 10 - 10,
            environnement.parkings[1].getDIMX() * 10, environnement.parkings[1].getDIMY() * 10 + 10, 0);

    P3.draw(renderer, environnement.parkings[2].getPos().x * 10 - 10, environnement.parkings[2].getPos().y * 10 - 10,
            environnement.parkings[2].getDIMX() * 10, environnement.parkings[2].getDIMY() * 10, 0);
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
    Banner.h = 8;
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &Banner);
    SDL_Rect Banner2;
    Banner2.x = 0;
    Banner2.y = 808;
    Banner2.w = 1000;
    Banner2.h = 3;
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

    // Affichage du temps

    Calendar.draw(renderer, 442, 808, 48, 40, 0);
    // Si Mois > 0 afficher Mois
    if (environnement.Mois > 0)
    {
        AfficherTexte(font_Time, "", "", int(environnement.Mois), 456, 822, 0, 0, 0, 255);
    }
    else
    {
        AfficherTexte(font_Time, "00", "", 0, 456, 822, 0, 0, 0, 255);
    }

    AfficherTexte(font_Calendar, "MONTH", "", 0, 449, 847, 0, 0, 0, 255);

    Calendar.draw(renderer, 510, 808, 48, 40, 0);
    // Si Jours > 0 afficher Jours
    if (environnement.Jours > 0)
    {
        AfficherTexte(font_Time, "", "", int(environnement.Jours), 524, 822, 0, 0, 0, 255);
    }
    else
    {
        AfficherTexte(font_Time, "00", "", 0, 524, 822, 0, 0, 0, 255);
    }
    AfficherTexte(font_Calendar, "DAY", "", 0, 525, 847, 0, 0, 0, 255);

    Clock.draw(renderer, 450, 848, 100, 62, 0);

    AfficherTexte(font_Time, "", " : ", int(environnement.Secondes), 509, 868, 255, 0, 0, 255);

    // Si Minutes > 0 afficher Minutes
    if (environnement.Minutes > 0)
    {
        AfficherTexte(font_Time, "", " : ", int(environnement.Minutes), 476.5, 868, 255, 0, 0, 255);
    }
    else
    {
        AfficherTexte(font_Time, " : 00", "", 0, 476.5, 868, 255, 0, 0, 255);
    }

    // Si Heures > 0 afficher Heures
    if (environnement.Heures > 0)
    {
        AfficherTexte(font_Time, "", "", int(environnement.Heures), 458, 868, 255, 0, 0, 255);
    }
    else
    {
        AfficherTexte(font_Time, "00", "", 0, 458, 868, 255, 0, 0, 255);
    }

    // Boutton Exit
    Exit.draw(renderer, ExitX, ExitY, ExitW, ExitH, 0);

    if (environnement.Pause == true)
    {
        for (int i = 0; i < environnement.parkings.size(); i++)
        {
            int x = environnement.parkings[i].getPos().x * 10 + environnement.parkings[i].getDIMX() * 10 - 60;
            int y = environnement.parkings[i].getPos().y * 10 + environnement.parkings[i].getDIMY() * 10 - 60;
            int w = 40;
            int h = 50;
            ParkSheet.draw(renderer, x, y, w, h, 0);
        }

        MenuArrow.draw(renderer, MenuArrowX, MenuArrowY, MenuArrowW, MenuArrowH, MenuArrowAngle);
    }

    //---------------------------------------------------------------------------------------
}

int Affichage::AffichageUserCard(unsigned int Vind)
{

    SDL_Rect User_Card;
    if (environnement.voitures[Vind].get_position().x + 250 > 1000)
    {
        User_Card.x = environnement.voitures[Vind].get_position().x - 250;
    }
    else
    {
        User_Card.x = environnement.voitures[Vind].get_position().x;
    }
    if (environnement.voitures[Vind].get_position().y - 150 < 0)
    {
        User_Card.y = environnement.voitures[Vind].get_position().y;
    }
    else
        User_Card.y = environnement.voitures[Vind].get_position().y - 150;
    User_Card.w = 250;
    User_Card.h = 150;
    UserCard.draw(renderer, User_Card.x, User_Card.y, User_Card.w, User_Card.h, 0);

    // on affiche son nom
    AfficherTexte(font_UserCard, environnement.voitures[Vind].User.getName(), "", 0, User_Card.x + 125, User_Card.y + 50, 0, 0, 0, 255);
    // on affiche son Age
    AfficherTexte(font_UserCard, "", "Age: ", environnement.voitures[Vind].User.getAge(), User_Card.x + 125, User_Card.y + 70, 0, 0, 0, 255);
    // on affiche son temps de stationnement
    AfficherTexte(font_UserCard, "", "ParkTime: ", environnement.voitures[Vind].User.getParkTime(), User_Card.x + 125, User_Card.y + 90, 0, 0, 0, 255);
    // on affiche son prix max
    AfficherTexte(font_UserCard, "", "Prix max: ", environnement.voitures[Vind].User.getMaxPrice(), User_Card.x + 125, User_Card.y + 110, 0, 0, 0, 255);

    // Si on clic en haut a droite de la carte on la supprime
    AfficherTexte(font_UserCard, "X", "", 0, User_Card.x + 230, User_Card.y + 10, 0, 0, 0, 255);
    if (XC > User_Card.x + 230 && XC < User_Card.x + 240 && YC > User_Card.y + 10 && YC < User_Card.y + 20)
    {
        return -1;
    }

    return 0;
}

int Affichage::AffichageParkingCard(unsigned int ParkInd)
{
    SDL_Rect rect;
    rect.x = environnement.parkings[ParkInd].getPos().x * 10;
    rect.y = environnement.parkings[ParkInd].getPos().y * 10;
    rect.w = environnement.parkings[ParkInd].getDIMX() * 10 - 20;
    rect.h = environnement.parkings[ParkInd].getDIMY() * 10 - 20;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);
    SDL_RenderFillRect(renderer, &rect);

    // on affiche son id
    AfficherTexte(font_default, "", "ID: ", environnement.parkings[ParkInd].getId(), rect.x + 10, rect.y + 10, 255, 255, 255, 180);
    // on affiche son prix min
    AfficherTexte(font_default, "", "Prix min: ", environnement.parkings[ParkInd].getMinPrice(), rect.x + 10, rect.y + 40, 255, 255, 255, 180);
    // on affiche son nombre de places restantes / total
    AfficherTexte(font_default, "", "Places: ", environnement.parkings[ParkInd].getNbAvailablePlaces(), rect.x + 10, rect.y + 70, 255, 255, 255, 180);
    AfficherTexte(font_default, "", " / ", environnement.parkings[ParkInd].getNbPlaces(), rect.x + 142, rect.y + 70, 255, 255, 255, 180);

    // Si on sors de la carte on la supprime
    if (Xm < rect.x || Xm > rect.x + rect.w || Ym < rect.y || Ym > rect.y + rect.h + 10)
    {
        return -1;
    }
    return 0;
}

int Affichage::AffichageGraphMenu()
{

    // On affiche la barre de menu
    SDL_Rect MenuBar;
    MenuBar.x = 0;
    MenuBar.y = 0;
    MenuBar.w = 1000;
    MenuBar.h = 50;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 200);
    SDL_RenderFillRect(renderer, &MenuBar);

    // On affiche le boutton de menu deroulant des graphiques
    SDL_Rect GraphMenu;
    GraphMenu.x = 5;
    GraphMenu.y = 5;
    GraphMenu.w = 200;
    GraphMenu.h = 40;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 200);
    SDL_RenderFillRect(renderer, &GraphMenu);
    AfficherTexte(font_default, "GRAPHIQUES >", "", 0, 15, 13, 0, 0, 0, 255);
    // Hover sur le boutton
    if (Xm > 5 && Xm < 205 && Ym > 5 && Ym < 45)
    {
        SDL_Rect GraphMenuHover;
        GraphMenuHover.x = 5;
        GraphMenuHover.y = 5;
        GraphMenuHover.w = 200;
        GraphMenuHover.h = 40;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 100);
        SDL_RenderFillRect(renderer, &GraphMenuHover);
    }

    if (DisplayUnrolledMenu)
    {
        //----------------------------------Boutton 1---------------------------------------------------------

        // On affiche le boutton 1 de menu deroulant des graphiques (Profit)
        SDL_Rect Button1;
        Button1.x = 5;
        Button1.y = 45;
        Button1.w = 200;
        Button1.h = 40;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 200);
        SDL_RenderFillRect(renderer, &Button1);
        AfficherTexte(font_default, "PROFIT", "", 0, 15, 53, 0, 0, 0, 255);
        // Hover sur le boutton
        if (Xm > 5 && Xm < 205 && Ym > 45 && Ym < 85)
        {
            SDL_Rect Button1Hover;
            Button1Hover.x = 5;
            Button1Hover.y = 45;
            Button1Hover.w = 200;
            Button1Hover.h = 40;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 100);
            SDL_RenderFillRect(renderer, &Button1Hover);
        }

        //----------------------------------Boutton 2---------------------------------------------------------

        // On affiche le boutton 2 de menu deroulant des graphiques (Prix)
        SDL_Rect Button2;
        Button2.x = 5;
        Button2.y = 85;
        Button2.w = 200;
        Button2.h = 40;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 200);
        SDL_RenderFillRect(renderer, &Button2);
        AfficherTexte(font_default, "PRIX", "", 0, 15, 93, 0, 0, 0, 255);
        // Hover sur le boutton
        if (Xm > 5 && Xm < 205 && Ym > 85 && Ym < 125)
        {
            SDL_Rect Button2Hover;
            Button2Hover.x = 5;
            Button2Hover.y = 85;
            Button2Hover.w = 200;
            Button2Hover.h = 40;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 100);
            SDL_RenderFillRect(renderer, &Button2Hover);
        }

        //----------------------------------Boutton 3---------------------------------------------------------

        // On affiche le boutton 3 de menu deroulant des graphiques (NombreDePlaces)
        SDL_Rect Button3;
        Button3.x = 5;
        Button3.y = 125;
        Button3.w = 200;
        Button3.h = 40;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 200);
        SDL_RenderFillRect(renderer, &Button3);
        AfficherTexte(font_default, "NB PLACES", "", 0, 15, 133, 0, 0, 0, 255);
        // Hover sur le boutton
        if (Xm > 5 && Xm < 205 && Ym > 125 && Ym < 165)
        {
            SDL_Rect Button3Hover;
            Button3Hover.x = 5;
            Button3Hover.y = 125;
            Button3Hover.w = 200;
            Button3Hover.h = 40;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 100);
            SDL_RenderFillRect(renderer, &Button3Hover);
        }
    }

    if (XC > 470 && XC < 530 && YC > 60 && YC < 80)
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
    bool DisplayParkingCard = false;
    bool DisplayGraphMenu = false;
    int CarInd = 0;
    int ParkInd = 0;

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
                    // Clear la console
                    // printf("\33[H\33[2J");
                    // environnement.AddVoiture();
                    break;
                case SDLK_p:

                    break;
                }
                break;
            }
        }
        // si la souris est sur le bouton pause / play
        if (Xm > 50 && Xm < 93 && Ym > 826 && Ym < 881)
        {
            PauseX = 50 - 5 / 2;  // on decale le bouton de la moitier la largueur ajouté -> plus propre
            PauseY = 826 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
            PauseW = 43 + 5;      // on ajoute 5 de chaque coté
            PauseH = 55 + 5;      // on ajoute 5 de chaque coté
        }
        else if (Xm > 150 && Xm < 193 && Ym > 826 && Ym < 881)
        {
            SpeedUpX = 150 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
            SpeedUpY = 826 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
            SpeedUpW = 43 + 5;      // on ajoute 5 de chaque coté
            SpeedUpH = 55 + 5;      // on ajoute 5 de chaque coté
        }
        else if (Xm > 853 && Xm < 985 && Ym > 826 && Ym < 881)
        {
            ExitX = 853 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
            ExitY = 826 - 5 / 2; // on decale le bouton de la moitier la hauteur ajouté
            ExitW = 132 + 5;     // on ajoute 5 de chaque coté
            ExitH = 55 + 5;      // on ajoute 5 de chaque coté
        }
        else if (Xm > 470 && Xm < 530 && Ym > 20 && Ym < 40 && environnement.Pause == true && !DisplayGraphMenu)
        {
            MenuArrowX = 470 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
            MenuArrowY = 20 - 5 / 2;  // on decale le bouton de la moitier la hauteur ajouté
            MenuArrowW = 60 + 5;      // on ajoute 5 de chaque coté
            MenuArrowH = 20 + 5;      // on ajoute 5 de chaque coté
        }
        else if (Xm > 470 && Xm < 530 && Ym > 60 && Ym < 80 && environnement.Pause == true && DisplayGraphMenu)
        {
            MenuArrowX = 470 - 5 / 2; // on decale le bouton de la moitier la largueur ajouté -> plus propre
            MenuArrowY = 60 - 5 / 2;  // on decale le bouton de la moitier la hauteur ajouté
            MenuArrowW = 60 + 5;      // on ajoute 5 de chaque coté
            MenuArrowH = 20 + 5;      // on ajoute 5 de chaque coté
        }
        else
        {
            PauseX = 50;
            PauseY = 826;
            PauseW = 43;
            PauseH = 55;
            SpeedUpX = 150;
            SpeedUpY = 826;
            SpeedUpW = 43;
            SpeedUpH = 55;
            ExitX = 853;
            ExitY = 826;
            ExitW = 132;
            ExitH = 55;
            MenuArrowX = 470;
            if (DisplayGraphMenu)
            {
                MenuArrowY = 20 + 40;
                MenuArrowAngle = 180;
            }
            else
            {
                MenuArrowY = 20;
                MenuArrowAngle = 0;
            }
            MenuArrowW = 60;
            MenuArrowH = 20;
        }

        if (ispress == true)
        {
            //------------------ Bouton pause ------------------
            if (XC > 50 && XC < 93 && YC > 826 && YC < 881)
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
                            cout << "voiture " << i << endl;
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
                // Si on clique sur la ParkSheet pour afficher les infos du parkings
                for (int i = 0; i < environnement.parkings.size(); i++)
                {
                    int InfoParkX = environnement.parkings[i].getPos().x * 10 + environnement.parkings[i].getDIMX() * 10 - 60;
                    int InfoParkY = environnement.parkings[i].getPos().y * 10 + environnement.parkings[i].getDIMY() * 10 - 60;
                    int InfoParkW = 40;
                    int InfoParkH = 50;
                    if (XC > InfoParkX && XC < InfoParkX + InfoParkW && YC > InfoParkY && YC < InfoParkY + InfoParkH)
                    {
                        cout << "Parking : " << i << endl;
                        DisplayParkingCard = true;
                        ParkInd = i;
                    }
                }

                // Si on clique sur la fleche pour afficher le menu des graphs
                if (XC > 470 && XC < 530 && YC > 20 && YC < 40)
                {
                    MenuArrowX = 470;
                    MenuArrowY = 20 + 60;
                    MenuArrowW = 60;
                    MenuArrowH = 20;
                    DisplayGraphMenu = true;
                }

                //-------------------------------------------------Graphs-------------------------------------------------
                if (DisplayGraphMenu)
                {
                    // Si on clic sur le boutton pour afficher le menu deroulant des graphs
                    if (XC > 5 && XC < 205 && YC > 5 && YC < 45)
                    {
                        DisplayUnrolledMenu = !DisplayUnrolledMenu;
                    }

                    // Si on clic sur le boutton 1 pour afficher le graph Profit
                    if (XC > 5 && XC < 205 && YC > 45 && YC < 85 && DisplayUnrolledMenu)
                    {
                        environnement.makeGraph(0);
                    }
                    // Si on clic sur le boutton 2 pour afficher le graph Prix
                    else if (XC > 5 && XC < 205 && YC > 85 && YC < 125 && DisplayUnrolledMenu)
                    {
                        environnement.makeGraph(1);
                    }
                    // Si on clic sur le boutton 3 pour afficher le graph Nb places
                    else if (XC > 5 && XC < 205 && YC > 125 && YC < 165 && DisplayUnrolledMenu)
                    {
                        environnement.makeGraph(2);
                    }
                }
                //--------------------------------------------------------------------------------------------------------
            }
            //----------------------------------------------------

            //------------------ Bouton speed ------------------
            if (XC > 150 && XC < 193 && YC > 826 && YC < 881)
            {
                environnement.SpeedUp = !environnement.SpeedUp;
            }
            //--------------------------------------------------

            //------------------ Bouton Exit ------------------
            if (XC > 853 && XC < 985 && YC > 826 && YC < 881)
            {
                display = false;
            }
            //--------------------------------------------------

            ispress = false;
        }

        if (environnement.Pause)
        {
            if (DisplayUserCard == true)
            {
                if (AffichageUserCard(CarInd) == -1)
                    DisplayUserCard = false;
            }
            if (DisplayParkingCard == true)
            {
                if (AffichageParkingCard(ParkInd) == -1)
                    DisplayParkingCard = false;
            }
            if (DisplayGraphMenu == true)
            {
                if (AffichageGraphMenu() == -1)
                    DisplayGraphMenu = false;
            }
        }
        else 
        {   
            // Si on est plus en pause, on cache tout et remet a la position de base les boutons
            DisplayUserCard = false;
            DisplayParkingCard = false;
            DisplayGraphMenu = false;
            DisplayUnrolledMenu = false;
            MenuArrowAngle = 0;
            MenuArrowX = 470;
            MenuArrowY = 20;
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}
