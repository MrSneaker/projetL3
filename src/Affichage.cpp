#include "Affichage.h"

#include <iostream>

using namespace std;

Affichage::Affichage()
{
    Environnement Env;
    Env.initParkings();
    environnement = Env;
    
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

    window = SDL_CreateWindow("Park Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    Voiture = IMG_Load("img/Voiture1.png"); // Une voiture
    textureVoiture = SDL_CreateTextureFromSurface(renderer, Voiture);
    SDL_FreeSurface(Voiture);

    environnement.AddVoiture();

    environnement.parkings[0].getPlacesTab()[21].setIsTaken(true);

   
}

void Affichage::AffichagePlateau()
{
    // Test Affichage

    // Affiche l'image des parkings

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

    // Affiche les routes
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

  
    // Affiche les voitures
    SDL_Rect Voiture;
    Voiture.x = environnement.voitures[0].get_position().x;
    Voiture.y = environnement.voitures[0].get_position().y;
    Voiture.w = VoitureSizeW;
    Voiture.h = VoitureSizeH;
    SDL_RenderCopyEx(renderer, textureVoiture, NULL, &Voiture, environnement.voitures[0].getAngle(), NULL, SDL_FLIP_NONE);

    //Quadrillage
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i =0; i<DimWindowX; i+=10){
        SDL_RenderDrawLine(renderer, i, 0, i, DimWindowY);
    }
    for(int i =0; i<DimWindowY; i+=10){
        SDL_RenderDrawLine(renderer, 0, i, DimWindowX, i);
    }

    // Affiche les places de chaque parking
    for (int j = 0; j < environnement.parkings.size(); j++)
    {

        for (int i = 0; i < environnement.parkings[j].getNbPlaces(); i++)
        {
            
            Place.x = environnement.parkings[j].getPlacesTab()[i].getPos().x * 10;
            Place.y = environnement.parkings[j].getPlacesTab()[i].getPos().y * 10;
            Place.w = 10;
            Place.h = 20;

            // Si la place est prise, on affiche une place rouge
            if(environnement.parkings[j].getPlacesTab()[i].getIsTaken()){
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &Place);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &Place);
            }
        }

        //Affiche le centre de chaque parking (pour reglages + test)
        SDL_Rect Center;
        Center.x = environnement.parkings[j].getPos().x * 10 + environnement.parkings[j].getDIMX() * 10 / 2;
        Center.y = environnement.parkings[j].getPos().y * 10 + environnement.parkings[j].getDIMY() * 10 / 2;
        Center.w = 10;
        Center.h = 10;

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Center);

    }

    //Affiche la taille de detection du parking
    for(int i=0; i<environnement.parkings.size(); i++)
    {
        SDL_Rect Park;
        Park.x = environnement.parkings[i].getPos().x * 10;
        Park.y = environnement.parkings[i].getPos().y * 10;
        Park.w = environnement.parkings[i].getDIMX() * 10;
        Park.h = environnement.parkings[i].getDIMY() * 10;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &Park);
    }
        


    //Affiche une barre de menu en bas de l'écran
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

    
    InitAffichage();
    while (display)
    {
        this_thread::sleep_for(chrono::milliseconds(10));

        AffichagePlateau();
        environnement.Environnement_play();

        int X, Y;

        // environnement.voitures[0].MoveToTargetPosition();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // detecte la mouvement de la souris
            case SDL_MOUSEMOTION:
                X = event.motion.x;
                Y = event.motion.y;

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
                    environnement.voitures[0].setSpeed(environnement.voitures[0].getSpeed() + 1); //test
                    
               
              
                    break;
                }
                break;
            }
        }

        //Met la target sur la souris (pour test)
        environnement.voitures[0].setTargetPosition(Vec2(X, Y));

        //Si la valeur Is_in de la voiture est true on modifie la taille de la voiture
        //TODO : Marche pas bien je ne sais pas trop pk  
        //En gros elle boucle nrlm sur tout les parkings mais la elle change que sur le parking 3 alors qu'ont detecte bien si elle est dans les autres parkings ou non
        if(environnement.voitures[0].getIs_in())
        {
            VoitureSizeW = 10;
            VoitureSizeH = 20;
        }
        else
        {
            VoitureSizeW = 20;
            VoitureSizeH = 30;
        }




        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}