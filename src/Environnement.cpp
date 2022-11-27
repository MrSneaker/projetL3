#include "Environnement.h"

using namespace std;

int Environnement::random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
                                            // négatif ou positif en fonction des bornes fournies en paramètres.
{
    int res;
    if (max - min == 0) // pour éviter les erreurs fatales du à un modulo 0.
        return EXIT_FAILURE;
    if (max - min < 0)
    {
        res = -1 * (min + rand() % (max - min));
    }
    else
        res = min + rand() % (max - min);

    return res;
}

Environnement::Environnement()
{
    removeLogs();
    getMap();
    initParkings();
}

Environnement::~Environnement()
{
}

Vec2 Environnement::GetPosbyNodeInd(int indiceCase) const
{
    Vec2 pos;
    pos.x = (indiceCase % (DimWindowX / tailleCase)) * 10;
    pos.y = (indiceCase / (DimWindowX / tailleCase)) * 10;
    return pos;
}

int Environnement::GetNodeIndbyPos(Vec2 pos) const
{
    int indiceCase;
    indiceCase = (pos.x / tailleCase) + (pos.y / tailleCase) * (DimWindowX / tailleCase);
    return indiceCase;
}

void Environnement::ClockTime()
{
    if (TempsEcoule >= 1.f)
    {
        Secondes++;
        TempsEcoule = 0.f;
    }
    if (Secondes >= 60)
    {
        Minutes++;
        Secondes = 0;
    }
    if (Minutes >= 60)
    {
        Heures++;
        Minutes = 0;
    }
    if (Heures >= 24)
    {
        Jours++;
        Heures = 0;
    }
    if (Jours >= 30)
    {
        Mois++;
        Jours = 0;
    }
}

void Environnement::Astar(Voiture &v, unsigned int StartInd, unsigned int EndInd)
{
    vector<Node *> nodes;

    for (int x = 0; x < DimWindowX / tailleCase; x++)
    {
        for (int y = 0; y < DimWindowY / tailleCase; y++)
        {
            nodes.push_back(new Node());
        }
    }
    for (int x = 0; x < DimWindowX / tailleCase; x++)
    {
        for (int y = 0; y < DimWindowY / tailleCase; y++)
        {
            nodes[x + y * DimWindowX / tailleCase]->setNodepos(Vec2(x, y));
            nodes[x + y * DimWindowX / tailleCase]->setisVisited(false);
            nodes[x + y * DimWindowX / tailleCase]->setParent(nullptr);
            nodes[x + y * DimWindowX / tailleCase]->indice = x + y * DimWindowX / tailleCase;

            if (map[y][x] == '1')
                nodes[x + y * DimWindowX / tailleCase]->setisObstacle(true);
            else
                nodes[x + y * DimWindowX / tailleCase]->setisObstacle(false);
        }
    }
    // Si une place est prise elle devient un obstacle
    for (int i = 0; i < parkings.size(); i++)
    {
        for (int j = 0; j < parkings[i].getPlacesTab().size(); j++)
        {
            unsigned int PlacePosX = parkings[i].getPlacesTab()[j].getPos().x * tailleCase;
            unsigned int PlacePosY = parkings[i].getPlacesTab()[j].getPos().y * tailleCase;
            unsigned int NoeudPlace = GetNodeIndbyPos(Vec2(PlacePosX, PlacePosY));
            if (parkings[i].getPlacesTab()[j].getIsTaken() == true && parkings[i].getPlacesTab()[j].getIsReserved() == true)
            {

                nodes[NoeudPlace]->setisObstacle(true);       // on met à jour l'état du noeud
                nodes[NoeudPlace + 100]->setisObstacle(true); // on met à jour l'état du noeud
            }
            else
            {
                nodes[NoeudPlace]->setisObstacle(false);       // on met à jour l'état du noeud
                nodes[NoeudPlace + 100]->setisObstacle(false); // on met à jour l'état du noeud
            }
        }
    }

    for (int x = 0; x < DimWindowX / tailleCase; x++)
    {
        for (int y = 0; y < DimWindowY / tailleCase; y++)
        {
            nodes[x + y * DimWindowX / tailleCase]->setisVisited(false);

            nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().clear();
        }
    }

    vector<Node *> openList;
    openList.clear();
    v.getpathTab().clear();
    v.setIs_pathfind(false);

    Node *currentNode;
    Node *StartNode = nodes[StartInd];
    Node *EndNode = nodes[EndInd];

    for (int x = 0; x < DimWindowX / tailleCase; x++)
    {
        for (int y = 0; y < DimWindowY / tailleCase; y++)
        {
            nodes[x + y * DimWindowX / tailleCase]->setisVisited(false);
            nodes[x + y * DimWindowX / tailleCase]->localGoal = INFINITY;
            nodes[x + y * DimWindowX / tailleCase]->GlobalGoal = INFINITY;
            nodes[x + y * tailleCase]->setParent(nullptr);

            if (y > 0)
                nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().push_back(nodes[(x + 0) + (y - 1) * DimWindowX / tailleCase]);
            if (y < DimWindowY / tailleCase - 1)
                nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().push_back(nodes[(x + 0) + (y + 1) * DimWindowX / tailleCase]);
            if (x > 0)
                nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().push_back(nodes[(x - 1) + (y + 0) * DimWindowX / tailleCase]);
            if (x < DimWindowX / tailleCase - 1)
                nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().push_back(nodes[(x + 1) + (y + 0) * DimWindowX / tailleCase]);
        }
    }
    auto distance = [](Node *a, Node *b)
    {
        return sqrtf((a->getNodepos().x - b->getNodepos().x) * (a->getNodepos().x - b->getNodepos().x) +
                     (a->getNodepos().y - b->getNodepos().y) * (a->getNodepos().y - b->getNodepos().y));
    };

    auto heuristic = [distance](Node *a, Node *b)
    {
        return distance(a, b);
    };

    currentNode = StartNode;
    StartNode->localGoal = 0.0f;
    StartNode->GlobalGoal = heuristic(StartNode, EndNode);

    openList.push_back(StartNode);

    while (!openList.empty() && currentNode != EndNode && v.getIs_pathfind() == false)
    {
        while (!openList.empty() && openList.front()->getisVisited())
        {
            openList.erase(openList.begin());
        }

        if (openList.empty())
        {
            break;
        }

        currentNode = openList.front();
        currentNode->setisVisited(true);

        // check each of this node's neighbours
        for (auto neighbour : currentNode->getVecNeighbours())
        {
            if (neighbour->getisVisited() == false && neighbour->getisObstacle() == false)
            {
                openList.push_back(neighbour);

                float possiblyLowerGoal = currentNode->localGoal + distance(currentNode, neighbour);

                if (possiblyLowerGoal < neighbour->localGoal)
                {
                    neighbour->setParent(currentNode);

                    neighbour->localGoal = possiblyLowerGoal;

                    neighbour->GlobalGoal = neighbour->localGoal + heuristic(neighbour, EndNode);
                }
            }
        }
    }
    //---------------------------------TrackPath---------------------------------
    Node *current = EndNode; // on commence par le EndNode car on remonte le chemin
    if (current->getParent() == nullptr)
    {
        cout << "Pas de parent" << endl;
    }
    while (current->getParent() != nullptr && v.getIs_pathfind() == false)
    {
        v.getpathTab().push_back(current); // on ajoute le noeud courant au chemin pour le tracer
        current = current->getParent();    // on passe au noeud parent pour continuer le chemin jusqu'au StartNode
    }
    //---------------------------------TrackPath---------------------------------
    v.setIs_pathfind(true);

    openList.clear();
    if (v.getIs_parked() == true)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            delete nodes[i];
        }
        nodes.clear();
        delete StartNode;
        delete EndNode;
    }
}

void Environnement::initUser()
{
    double price = (double)(random(20, 80) / 10); // on simule des floats en divisants par 10.
    unsigned int id = conducteurs.size();         // Marche pas si on supprime un utilisateur du tableau et qu'on en rajoute un.
    string name = "Paulo - " + to_string(id);

    // On attribue à l'utilisateur (que l'on crée juste après) un entier initial aléatoire (entre 0 et 5)
    // de visites de chaque parking (on simule ainsi le passé)
    // avec les changements cela doit être fait avec les procédures dans parkings.. mais à ce moment là uniquement au premiere ajout de l'utilisateur.

    Utilisateur u(price, id, name);
    u.setAge(random(18, 80));
    conducteurs.push_back(u);
}

// TODO : Création d'utilisateur avec nom différent

void Environnement::initParkings()
{
    // Initialisation des parkings
    // Parametre du constructeur : Vec2 position, int numberOfPlaces, (float minimumPrice, float maximumPrice) a revoir

    // Créer 3 parkings et les ajouter dans le tableau de parkings
    Parking p0(Vec2(1, 1), 3, 8, 44, 38, 0);   // p0
    Parking p1(Vec2(57, 1), 3, 8, 44, 38, 1);  // p1
    Parking p2(Vec2(1, 52), 3, 8, 100, 29, 2); // p2
    parkings.push_back(p0);
    parkings.push_back(p1);
    parkings.push_back(p2);
}

int Environnement::getParkingInd()
{
    // retourne l'indice d'un parking aléatoirement entre les 3
    int ind = random(0, 3);
    switch (ind)
    {
    case 0:
        if (parkings[0].getNbAvailablePlaces() != 0)
            return 0;
        else
        {
            if (parkings[0].IsFull() && parkings[1].IsFull() && parkings[2].IsFull())
                return -1;
            else
                return getParkingInd();
        }
        break;
    case 1:
        if (parkings[1].getNbAvailablePlaces() != 0)
            return 1;
        else
        {
            if (parkings[0].IsFull() && parkings[1].IsFull() && parkings[2].IsFull())
                return -1;
            else
                return getParkingInd();
        }
        break;
    case 2:
        if (parkings[2].getNbAvailablePlaces() != 0)
            return 2;
        else
        {
            if (parkings[0].IsFull() && parkings[1].IsFull() && parkings[2].IsFull())
                return -1;
            else
                return getParkingInd();
        }
        break;
    default:
        return -1;
        break;
    }
}

int Environnement::getPlaceInd(int parkingInd)
{
    // retourne l'indice d'une place aléatoirement entre les places disponibles du parking
    // sauf si place déjà prise
    int ind = random(0, parkings[parkingInd].getNbPlaces());

    if (parkings[parkingInd].getPlacesTab()[ind].getIsReserved() == false)
        return ind;
    else
        getPlaceInd(parkingInd);
    if (parkings[parkingInd].getNbAvailablePlaces() == 0 && !parkings[parkingInd].IsFull())
        return -1;
}

const int Environnement::GetEntry()
{
    // En renvoie le noeud d'une des 3 entrées aléatoirement
    int entry = random(0, 3);
    switch (entry)
    {
    case 0:
        return 4700;
        break;
    case 1:
        return 4299;
        break;
    case 2:
        return 47;
        break;
    default:
        return 0;
        break;
    }
}

const int Environnement::GetExit()
{
    // En renvoie le noeud d'une des 3 sorties aléatoirement
    int exit = random(0, 3);
    switch (exit)
    {
    case 0:
        return 4200;
        break;
    case 1:
        return 4799;
        break;
    case 2:
        return 52;
        break;
    default:
        return 52;
        break;
    }
}

void Environnement::AddVoiture()
{
    initUser();
    Voiture V(conducteurs[conducteurs.size() - 1]);
    V.indice = voitures.size(); // TODO : Faire en sorte qu'ont ai un nombre fini d'utilisateur qui tourne en boucle

    int Entry = GetEntry();
    V.set_position(GetPosbyNodeInd(Entry) + Vec2(5, 5));

    V.CarColor = random(0, 3);

    V.Exit = GetExit();
    V.setTargetPosition(GetPosbyNodeInd(V.Exit) + Vec2(5, 5));

    V.startTimer = frameParkTime;
    voitures.push_back(V); // Ajout de la voiture dans le tableau de voiture

    Astar(voitures.back(), Entry, GetNodeIndbyPos(voitures.back().getTargetPosition())); // on lance l'algorithme A* pour trouver le chemin

    voitures.back().dejaspawn = true;
    for (int i = 0; i < parkings.size(); i++)
    {
        Utilisateur newUser = conducteurs[conducteurs.size() - 1];
        parkings[i].addUsersTab(newUser);
    }
}

void Environnement::RemoveVoiture(int numVoiture)
{
    voitures.erase(voitures.begin() + numVoiture);
}

void Environnement::updateStateVoiture()
{
    // On parcours le tableau de voitures
    for (int i = 0; i < voitures.size(); i++)
    {
        // On met à jour l'état de la place ou la voiture se trouve -> pour que quand elle passe sur une place et ne reste pas considere comme non libre
        // parkings[voitures[i].getParking()].getPlacesTab()[voitures[i].getPlace()].setIsTaken(false);
        bool inParking = false; // booléen qui permet de savoir si la voiture est dans un parking ou non
        bool isInPlace = false; // booléen qui permet de savoir si la voiture est dans une place ou non
        int parkingInd = voitures[i].getParking();
        int placeInd = voitures[i].getPlace();

        int VoiturePosX = voitures[i].get_position().x;            // Position de la voiture en x
        int VoiturePosY = voitures[i].get_position().y;            // Position de la voiture en y
        int TargetParkPosX = parkings[parkingInd].getPos().x * 10; // Position de la parking en x
        int TargetParkPosY = parkings[parkingInd].getPos().y * 10; // Position du parking en y

        // Si la voiture est dans l'enceinte du parking
        if (VoiturePosX >= TargetParkPosX && VoiturePosX <= TargetParkPosX + parkings[parkingInd].getDIMX() * 10 && VoiturePosY >= TargetParkPosY && VoiturePosY <= TargetParkPosY + parkings[parkingInd].getDIMY() * 10)
        {

            // cout << "Voiture " << i << " est dans le parking " << j << endl;
            inParking = true;                                                                    // La voiture est dans un parking
            int TargetPlacePosX = parkings[parkingInd].getPlacesTab()[placeInd].getPos().x * 10; // Position de la place en x
            int TargetPlacePosY = parkings[parkingInd].getPlacesTab()[placeInd].getPos().y * 10; // Position de la place en y

            // Si la voiture est dans l'enceinte de la place
            if (VoiturePosX >= TargetPlacePosX && VoiturePosX <= TargetPlacePosX + 10 && VoiturePosY >= TargetPlacePosY && VoiturePosY <= TargetPlacePosY + 20)
            {

                isInPlace = true; // La voiture est dans une place
            }
            else
                isInPlace = false; // La voiture n'est pas dans une place
        }

        if (inParking)
        {
            voitures[i].setIs_in(true);
            if (isInPlace)
            {
                voitures[i].setIs_parked(true);
                parkings[parkingInd].getPlacesTab()[placeInd].setIsTaken(true); // on met à jour l'état de la place
                if (voitures[i].derement == true)
                {
                    voitures[i].startTimer = frameParkTime;
                    // cout << "Parking : " << voitures[i].getParking() << " Nb place libre : " << parkings[voitures[i].getParking()].getNbAvailablePlaces() << endl;
                    voitures[i].derement = false;
                }

                voitures[i].setAngle(0);
            }
            else
            {
                parkings[parkingInd].getPlacesTab()[placeInd].setIsTaken(false); // on met à jour l'état de la place
                voitures[i].setIs_parked(false);
                if (voitures[i].derement == false)
                {
                    parkings[parkingInd].incrementNbAvailablePlaces();
                    cout << "Parking : " << voitures[i].getParking() << " Nb place libre : " << parkings[voitures[i].getParking()].getNbAvailablePlaces() << endl;
                    voitures[i].derement = true;
                }
            }
        }
        else
            voitures[i].setIs_in(false);

        // Si la valeur Is_in de la voiture est true on modifie la taille de la voiture

        if (voitures[i].getIs_in())
        {
            voitures[i].setwidth(10);
            voitures[i].setheight(20);
        }
        else
        {
            voitures[i].setwidth(20);
            voitures[i].setheight(30);
        }
    }
}

void Environnement::updateStateCarParks()
{
    // On parcourt le tableau de Parkings
    for (int i = 0; i < parkings.size(); i++)
    {
        parkings[i].updateSuccessPercentage();
        parkings[i].reconsiderPrices();
        parkings[i].addToData(realTime);
    }

    double avgSuccessPourcent = (double)(parkings[0].getSuccessPourcentage() + parkings[1].getSuccessPourcentage() + parkings[2].getSuccessPourcentage()) / 3;
    dataAvgSuccessPourcent.push_back(make_pair(realTime, avgSuccessPourcent));
}

// Boucle de jeu
void Environnement::Environnement_play()
{

    prevtime = currentTime;
    currentTime = temps;
    bool aConversationHasEnded = false;

    if (Pause == false)
    {
        // fonction de frametime
        deltaTime = (currentTime - prevtime) / 1000.f;

        if (SpeedUp == true)
        {
            deltaTime *= 5;
            // Minutes +=1;
        }

        frametime += deltaTime;
        TempsEcoule += deltaTime;
        frameParkTime += deltaTime;
        realTime += deltaTime;
        ClockTime();
        // Affiche une voiture toutes les 5 secondes un seul fois
        if (frametime >= 5.0f)
        {
            AddVoiture();
            frametime = 0;
        }

        for (int i = 0; i < voitures.size(); i++)
        {

            if (voitures[i].getIs_parked() == true && (frameParkTime - voitures[i].startTimer) >= voitures[i].User.getParkTime() * 10 && voitures[i].ChangeTrajToExit == false)
            {
                // la voiture sort du parking
                voitures[i].setIs_parked(false);

                voitures[i].Exit = GetExit();
                Astar(voitures[i], GetNodeIndbyPos(voitures[i].get_position()), voitures[i].Exit);
                voitures[i].ChangeTrajToExit = true;
            }
            if (voitures[i].getpathTab().size() == 0 && voitures[i].getIs_parked() == false && voitures[i].isMoving == false)
            {
                cout << "Erreur : La voiture " << i << " n'a pas de trajet" << endl;
                voitures[i].exist = false;
                RemoveVoiture(i);
            }
            if (voitures[i].ChangeTrajToExit == true && GetNodeIndbyPos(voitures[i].get_position()) == voitures[i].Exit)
            {
                voitures[i].exist = false;
                RemoveVoiture(i);
            }

            if (voitures[i].getNbFinishedConv() < 1 && voitures[i].exist)
            {
                conversation(voitures[i]);
                voitures[i].incrementNbFinishedConv();

                for (int j = 0; j < parkings.size(); j++)
                {
                    parkings[j].incrementNbFinishedConv();
                }

                changeTarget(voitures[i], voitures[i].getParking());
                aConversationHasEnded = true;
            }
            if (voitures[i].exist)
                voitures[i].MoveToTargetPosition();
        }
    }

    updateStateVoiture();

    if (aConversationHasEnded)
        updateStateCarParks();
}

void Environnement::getMap()
{
    ifstream MaMap("map.txt", ios::in);
    int i = 0;
    if (MaMap)
    {
        while (getline(MaMap, map[i], '\n'))
        {
            i++;
        }
        MaMap.close();
    }
}

int Environnement::createConv()
{
    Conversation *newConv = new Conversation;
    conv.push_back(newConv);
    return conv.size() - 1;
}

void Environnement::deleteConv(int ind)
{
    delete conv.at(ind);
    conv.erase(conv.begin() + ind);
}

void Environnement::conversation(Voiture &v)
{
    int indConv[parkings.size()];
    bool isFinished = false;
    for (int i = 0; i < parkings.size(); i++)
    {
        indConv[i] = createConv();
        isFinished = conv.at(indConv[i])->manageConv(parkings[i], v);
    }
    v.setParking(chosenPark(conv, v));
    for (int j = 0; j < parkings.size(); j++)
    {
        conv.at(indConv[parkings.size() - 1 - j])->manageConfirm(parkings[parkings.size() - 1 - j], v, v.getParking());
        if (isFinished)
        {
            conv.at(indConv[parkings.size() - 1 - j])->stockConv("Conversation U" + to_string(v.User.getId()) + "P" + to_string(parkings[parkings.size() - 1 - j].getId()));

            conv.at(indConv[parkings.size() - 1 - j])->updateStateCarParkAfterConv(parkings[parkings.size() - 1 - j]);
        }

        deleteConv(indConv[parkings.size() - 1 - j]);
    }
}

int Environnement::chosenPark(vector<Conversation *> c, Voiture v)
{
    string bestSender = "";
    int idBest;
    vector<float> tabPrice;
    for (int i = 0; i < c.size(); i++)
    {
        if (c.at(i)->getConv().at(c.at(i)->getConv().size() - 1).getSubject() == "ACCEPT")
            tabPrice.push_back(c.at(i)->getConv().at(c.at(i)->getConv().size() - 1).getPrice());
    }
    if (tabPrice.size() != 0)
    {
        float best = v.bestPrice(tabPrice);
        for (int j = 0; j < c.size(); j++)
        {
            float tmp = c.at(j)->getConv().at(c.at(j)->getConv().size() - 1).getPrice();
            if (best == tmp)
            {
                bestSender = c.at(j)->getConv().at(c.at(j)->getConv().size() - 1).getSender();
            }
        }
        idBest = v.extractIntFromString(bestSender);
    }
    else
        idBest = -1;
    return idBest;
}

void Environnement::changeTarget(Voiture &v, int indPr)
{
    if (indPr != -1 && parkings[indPr].IsFull() == false)
    {
        v.setParking(indPr);
        v.setPlace(getPlaceInd(indPr));
        Vec2 Placepos = parkings[indPr].getPlacesTab()[v.getPlace()].getPos();
        v.setTargetPosition(Placepos * Vec2(10, 10) + Vec2(5, 5));        // on place la cible au milieu de la place.
        parkings[indPr].getPlacesTab()[v.getPlace()].setIsReserved(true); // la place est réservée, pour pas qu'une autre voiture puisse y aller.
        if (v.derement)
            parkings[indPr].decrementNbAvailablePlaces(); // on décrémente le nombre de places disponibles.
        Astar(v, GetNodeIndbyPos(v.get_position()), GetNodeIndbyPos(v.getTargetPosition()));
    }
    else
    {
        v.Exit = GetExit();
        Astar(v, GetNodeIndbyPos(v.get_position()), v.Exit);
        v.ChangeTrajToExit = true;
    }
}

void Environnement::removeLogs()
{
    if (std::filesystem::exists("data/logs/Conversation U0P0.txt"))
        system("rm data/logs/*");
}

double Environnement::searchMaxInPair(vector<pair<double, double>> tab)
{
    double max = tab.at(0).second;
    double tmp = 0;
    for (int i = 0; i < tab.size(); i++)
    {
        if (tab[i].second > max)
        {
            if (tab[i].second != tmp)
                max = tab[i].second;
        }
        tmp = tab[i].second;
    }
    return max;
}

double Environnement::searchMax(vector<double> tab)
{
    double max = tab.at(0);
    double tmp = 0;
    for (int i = 0; i < tab.size(); i++)
    {
        if (tab[i] > max)
        {
            if (tab[i] != tmp)
                max = tab[i];
        }
        tmp = tab[i];
    }
    return max;
}

void Environnement::makeGraph(int choice)
{

    vector<double> tabMaxProfit;
    vector<double> tabMaxPlace;
    vector<double> tabMaxPrice;
    for (int i = 0; i < 3; i++)
        if (!parkings[i].getDataProfit().empty())
            tabMaxProfit.push_back(searchMaxInPair(parkings[i].getDataProfit()));

    for (int i = 0; i < 3; i++)
        if (!parkings[i].getDataNbPlaceTaken().empty())
            tabMaxPlace.push_back(searchMaxInPair(parkings[i].getDataNbPlaceTaken()));

    for (int i = 0; i < 3; i++)
        if (!parkings[i].getDataStartingPrice().empty())
            tabMaxPrice.push_back(searchMaxInPair(parkings[i].getDataStartingPrice()));

    switch (choice)
    {
    case 0:
        if (!tabMaxProfit.empty())
            Graph(parkings[0].getDataProfit(), parkings[1].getDataProfit(), parkings[2].getDataProfit(), "Profit parking ", 0, 0, realTime, searchMax(tabMaxProfit));
        break;
    case 1:
        if (!tabMaxPrice.empty())
            Graph(parkings[0].getDataStartingPrice(), parkings[1].getDataStartingPrice(), parkings[2].getDataStartingPrice(), "Evolution prix de départ parking ", 0, 0, realTime, searchMax(tabMaxPrice));
        break;
    case 2:
        if (!tabMaxPlace.empty())
            Graph(parkings[0].getDataNbPlaceTaken(), parkings[1].getDataNbPlaceTaken(), parkings[2].getDataNbPlaceTaken(), "Nombres de places occupées parking ", 0, 0, realTime, searchMax(tabMaxPlace));
        break;
    case 3:
        if (!dataAvgSuccessPourcent.empty())
            Graph(dataAvgSuccessPourcent, "Pourcentage de succes moyen", 0, 0, realTime, searchMaxInPair(dataAvgSuccessPourcent));
        break;
    default:
        break;
    }
}

void Environnement::test_regresion()
{

    // test de regression de la classe Environnement
    Environnement E;

    assert(E.parkings.size() == 3);
    cout << "Test de regression de la fonction initParking() : OK" << endl;

    for (int i = 0; i < 10; i++)
    {
        E.AddVoiture();
    }
    assert(E.voitures.size() == 10);
    E.RemoveVoiture(0);
    assert(E.voitures.size() == 9);

    cout << "Test de regression de des fonction Add/RemoveVoiture (): OK" << endl;

    int a = E.createConv();
    assert(E.conv.size() == 1);
    E.deleteConv(a);
    assert(E.conv.size() == 0);
    cout << "Test de regression de des fonction createConv/deleteConv: OK" << endl;

    for (int i = 0; i < E.voitures.size(); i++)
    {
        E.conversation(E.voitures.at(i));
    }

    /*// Affiche les infos du noeud 47
    cout << "Noeud 47 : " << endl;
    cout << "Position : " << E.nodes[47]->getNodepos().x << " " << E.nodes[47]->getNodepos().y << endl;
    cout << "fcost : " << E.nodes[47]->getFcost() << endl;
    cout << "gcost : " << E.nodes[47]->getGcost() << endl;
    cout << "hcost : " << E.nodes[47]->getHcost() << endl;

    // Affiche les infos du noeud 4299
    cout << "Noeud 4299 : " << endl;
    cout << "Position : " << E.nodes[4299]->getNodepos().x << " " << E.nodes[4299]->getNodepos().y << endl;
    cout << "fcost : " << E.nodes[4299]->getFcost() << endl;
    cout << "gcost : " << E.nodes[4299]->getGcost() << endl;
    cout << "hcost : " << E.nodes[4299]->getHcost() << endl;
    */

    // cout << "Longueur de la map : " << map[0].length() << endl;
    // cout<<"map[][] : "<<map[42][99]<<endl;
    // affiche le pathTab en mode texxte sur la map
    //  for(int i=0; i<E.pathTab.size(); i++)
    //  {
    //  	map[E.pathTab[i]->getNodepos().y][E.pathTab[i]->getNodepos().x] = '#';
    //  }
    //  cout << "Longueur de la map : " << map[0].length() << endl;
    //  cout<<"map[][] : "<<map[42][99]<<endl;
    //  affiche le pathTab en mode texxte sur la map
    //   for(int i=0; i<E.pathTab.size(); i++)
    //   {
    //   	map[E.pathTab[i]->getNodepos().y][E.pathTab[i]->getNodepos().x] = '#';
    //   }

    E.AddVoiture();
    E.AddVoiture();

    for (int i = 0; i < E.voitures.size(); i++)
    {
        cout << "Voiture " << i << " : "
             << "pathTab.size() : " << E.voitures[i].getpathTab().size() << endl;
        E.Astar(E.voitures[i], 47, 1721);
        cout << "la" << endl;
        cout << "Voiture : " << i << " : "
             << " getpathTab() size : " << E.voitures[0].getpathTab().size() << endl;
        for (int j = 0; j < E.voitures[i].getpathTab().size(); j++)
        {
            cout << "Noeud " << j << " : " << E.voitures[i].getpathTab()[j]->getNodepos().x << " " << E.voitures[i].getpathTab()[j]->getNodepos().y << endl;
        }
    }
}
