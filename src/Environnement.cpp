#include "Environnement.h"

using namespace std;

int Environnement::random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
{                                           // négatif ou positif en fonction des bornes fournies en paramètres.
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
    getUser();
    getNames_SurnamesFromFile();
    initParkings();
    nbConv = 0;
    frames = 0;
    frameParkTime = 0;
    prevtime = 0;
    currentTime = 0;
    realTime = 0;
    deltaTime = 0;
    frametime = 0;
    temps = 0;
    TempsEcoule = 0;
    Secondes = 0;
    Minutes = 0;
    Heures = 0;
    Jours = 0;
    Mois = 0;
    nbUserCreated = 0;
    nbUserSaved = 0;
}

bool Environnement::checkId(int id, string filename)
{
    vector<int> doublons;
    bool ret;
    ifstream fichier("data/User.txt", ios::in);
    if (fichier)
    {
        string ligne; // une variable pour stocker les lignes lues
        // on extrait les lignes une à une
        while (getline(fichier, ligne))
        {
            stringstream ss(ligne); // on crée un flux à partir de la ligne lue
            string token;           // une variable pour stocker les mots lus
            vector<string> tokens;  // un tableau pour stocker les mots lus
            // on extrait les mots un a un
            while (getline(ss, token, ','))
            {
                tokens.push_back(token); // on ajoute le mot lu au tableau
            }
            int id = stoi(tokens[0]);
            doublons.push_back(id);
        }
        fichier.close();

        // on verifie que dans le vector il n'y a pas de doublons
        for (int i = 0; i < doublons.size(); i++)
        {
            for (int j = i + 1; j < doublons.size(); j++)
            {
                if (doublons[i] == doublons[j])
                {
                    doubleUser.push_back(doublons[i]);
                    ret = false;
                }
            }
        }

        ret = true;
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    return ret;
}

Environnement::~Environnement()
{
    saveUser();
    tmpsavedConducteurs.clear(); // suppression des conducteurs temporaires
    savedConducteurs.clear();    // suppression des conducteurs sauvegardés
}

Vec2 Environnement::GetPosbyNodeInd(int indiceCase) const
{
    Vec2 pos;
    pos.x = (indiceCase % (DimWindowX / tailleCase)) * 10;
    pos.y = (indiceCase / (DimWindowX / tailleCase)) * 10;
    return pos;
}

const int Environnement::GetNodeIndbyPos(Vec2 pos) const
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

 void Environnement::Astar(Voiture &v, unsigned int StartInd, unsigned int EndInd, vector<Node *> &nodes)
{
    if (nodes.size() > 0)
    {
        v.deleteNode();
    }
    v.reachGoal = false;
    for (int x = 0; x < DimWindowX / tailleCase; x++)
    {
        for (int y = 0; y < DimWindowY / tailleCase; y++)
        {
            Node* n = new Node;
            if(n == nullptr)
                cout<<"erreur lors de l'allocation"<<endl;
            nodes.push_back(n);
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

            for(int i =0;i<nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours().size();i++)
            {
                delete nodes[x + y * DimWindowX / tailleCase]->getVecNeighbours()[i];
            }

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
    //---------------------------------TrackPath--------------------------------
    // si le pathtab est créé et stocké met le booléen à true
    v.setIs_pathfind(true);
    openList.clear();
    // si le pathtab de la voiture est créé et stocké on supprime les noeuds
}

void Environnement::saveUser()
{
    int i = 0;
    // on ouvre le fichier en mode écritur
    ofstream fichier("data/User.txt", ios::app);
    // on vérifie que l'ouverture a réussi
    if (fichier)
    {
        while (i < tmpsavedConducteurs.size())
        {
            for (auto &C : tmpsavedConducteurs)
            {
                // Si le conducteur est deja enregistré
                // on écrit dans le fichier
                fichier << C.getId() << ",";
                fichier << C.getName() << ",";
                fichier << C.getSurname() << ",";
                fichier << C.getMaxPrice() << ",";
                fichier << C.getAge() << ",";
                fichier << C.getParkTime() << ";";

                i++;
                fichier << endl;
            }
        }

        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Environnement::getUser()
{
    int i = 0;
    ifstream fichier("data/User.txt", ios::in);
    if (fichier)
    {
        string ligne; // une variable pour stocker les lignes lues
        // on extrait les lignes une à une
        while (getline(fichier, ligne))
        {
            stringstream ss(ligne); // on crée un flux à partir de la ligne lue
            string token;           // une variable pour stocker les mots lus
            vector<string> tokens;  // un tableau pour stocker les mots lus
            // on extrait les mots un a un
            while (getline(ss, token, ','))
            {
                tokens.push_back(token); // on ajoute le mot lu au tableau
            }
            int id = stoi(tokens[0]);
            string name = tokens[1];
            string surname = tokens[2];
            double maxPrice = stod(tokens[3]);
            int age = stoi(tokens[4]);
            float parkTime = stof(tokens[5]);
            savedConducteurs.push_back(Utilisateur(maxPrice, id, name, surname, age, parkTime)); // on ajoute le conducteur au tableau de conducteurs enregistrés
            nbUserSaved++;
        }

        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void Environnement::getNames_SurnamesFromFile()
{
    ifstream FemaleNamesFile("resources/female.names", ios::in);
    if (FemaleNamesFile)
    {
        string ligne; // une variable pour stocker les lignes lues
        // on stocke les noms de femmes dans le vecteur f_NameList
        while (getline(FemaleNamesFile, ligne))
        {
            f_NameList.push_back(ligne); // on ajoute le nom lu au tableau de noms de femmes
        }

        FemaleNamesFile.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier : <female.names> !" << endl;
    }

    ifstream MaleNamesFile("resources/male.names", ios::in);
    if (MaleNamesFile)
    {
        string ligne; // une variable pour stocker les lignes lues
        // on stocke les noms d'hommes dans le vecteur m_NameList
        while (getline(MaleNamesFile, ligne))
        {
            m_NameList.push_back(ligne); // on ajoute le nom lu au tableau de noms d'hommes
        }

        MaleNamesFile.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier : <male.names> !" << endl;
    }

    ifstream SurnamesFile("resources/sur.names", ios::in);
    if (SurnamesFile)
    {
        string ligne; // une variable pour stocker les lignes lues
        // on stocke les noms de famille dans le vecteur s_NameList
        while (getline(SurnamesFile, ligne))
        {
            SurnameList.push_back(ligne); // on ajoute le nom lu au tableau de noms de famille
        }

        SurnamesFile.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier : <sur.names> !" << endl;
    }
}

float Environnement::randomParkTime()
{
    float new_Parktime = 0;
    // On simule un pourcentage qui définie le temps de stationnement de l'utilisateur.
    float res = rand() % 100;

    // Si le pourcentage est inferieur à 20, on met le temps de stationnement entre 15 minutes et 1 heure
    if (res <= 20)
    {
        new_Parktime = (rand() % 45 + 15);
        new_Parktime = new_Parktime / 60;
    }
    // Si le pourcentage est inferieur à 50 et supperieur a 10, on met le temps de stationnement entre 1 et 5 heures
    else if (res <= 50)
    {
        new_Parktime = (rand() % 240 + 60) / 60;
    }
    // Si le pourcentage est supperieur a 50, on met le temps de stationnement entre 5 et 12 heures
    else
    {
        new_Parktime = (rand() % 420 + 300) / 60;
    }

    return new_Parktime;
}

string Environnement::getName(string gender)
{
    string ReturnName;

    int rand = random(0, 100);

    if (rand <= 50)
    {
        ReturnName = f_NameList[random(0, f_NameList.size())];
    }
    else
    {
        ReturnName = m_NameList[random(0, m_NameList.size())];
    }

    return ReturnName;
}

string Environnement::getSurname()
{
    string ReturnSurname = SurnameList[random(0, SurnameList.size())];
    return ReturnSurname;
}

int Environnement::CreateRandomId()
{
    int id = 0;
    bool idAlreadyUsed = false;
    do
    {
        id = random(0, 7000);
        // On vérifie que l'id n'est pas déjà utilisé
        for (auto &C : SimuConducteurs)
        {
            // Si l'id est déjà utilisé, on en crée un nouveau
            if (C.getId() == id)
            {
                id = random(0, 7000);
                idAlreadyUsed = true;
            }
            else
            {
                idAlreadyUsed = false;
            }
        }
    } while (idAlreadyUsed == true);

    return id;
}

void Environnement::initUser(bool quitif)
{
    int pourcentage = 0;
    nbUserSaved = savedConducteurs.size();

    // Si il y'a des conducteurs enregistrés dans le fichier
    if (!savedConducteurs.empty() && quitif == false)
    {
        // Si l'utilisateur est deja apparu dans la simulation on le recupere
        int randomNUM = random(0, nbUserSaved); // On choisit un conducteur au hasard dans le tableau de conducteurs enregistrés
        if (savedConducteurs[randomNUM].AlreadySpawned == true)
        {

            // On simule un pourcentage pour dire que si il est déja apparu dans la simulation, il a une chance de n% de revenir
            pourcentage = rand() % 100;
            if (pourcentage <= 30)
            {
                savedConducteurs[randomNUM].AlreadySpawned = true;            // On dit que le conducteur est deja apparu dans la simulation
                conducteurs.push_back(savedConducteurs[randomNUM]);           // on ajoute le conducteur au tableau de conducteurs
                savedConducteurs.erase(savedConducteurs.begin() + randomNUM); // On supprime le conducteur du tableau de conducteurs enregistrés
                SimuConducteurs.push_back(conducteurs[0]);                    // On ajoute le conducteur au tableau de conducteurs totale de la simulation
                nbUserCreated++;
            }
            // sinon on rappele la fonction pour qu'elle crée un nouveau conducteur
            else
                (initUser(true));
        }
        // Sinon on le récupère des utilisateurs enregistré et on le fait apparaitre pour la première fois dans cette simu
        else
        {
            savedConducteurs[randomNUM].AlreadySpawned = true;            // On dit que le conducteur est deja apparu dans la simulation
            conducteurs.push_back(savedConducteurs[randomNUM]);           // on ajoute le conducteur au tableau de conducteurs
            savedConducteurs.erase(savedConducteurs.begin() + randomNUM); // On supprime le conducteur aléatoire du tableau
            SimuConducteurs.push_back(conducteurs[0]);                    // On ajoute le conducteur au tableau de conducteurs de la simulation
            nbUserCreated++;                                              // On incremente le nombre de conducteurs créés
        }
    }
    // Si tout les conducteurs enregistés ont été créer ou qu'il n'y a pas encore de conducteurs enregistrés
    else
    {
        double price = (double)(random(40, 100) / 10); // on simule des floats en divisants par 10.

        int id = CreateRandomId(); // On crée un id aléatoire différent de ceux déjà utilisés

        string name = getName(); // On crée un nom aléatoire

        string surname = getSurname(); // On crée un prénom aléatoire

        // TODO:
        //  On attribue à l'utilisateur (que l'on crée juste après) un entier initial aléatoire (entre 0 et 5)
        //  de visites de chaque parking (on simule ainsi le passé)
        //  avec les changements cela doit être fait avec les procédures dans parkings.. mais à ce moment là uniquement au premiere ajout de l'utilisateur.

        int age = random(18, 80); // on simule un age aléatoire entre 18 et 80 ans

        float parkTime = randomParkTime(); // on simule un temps de stationnement aléatoire

        Utilisateur u(price, id, name, surname, age, parkTime);
        u.AlreadySpawned = true;
        nbUserCreated++;                  // On incremente le nombre de conducteurs créés
        conducteurs.push_back(u);         // on ajoute l'utilisateur dans le tableau des conducteurs
        SimuConducteurs.push_back(u);     // on ajoute l'utilisateur dans le tableau des conducteurs de la simulation
        tmpsavedConducteurs.push_back(u); // on ajoute l'utilisateur dans le tableau des conducteurs qui sont apparu dans la simulation
    }
}

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

const int Environnement::getPlaceInd(int parkingInd)
{
    // retourne l'indice d'une place aléatoirement entre les places disponibles du parking (recursive)
    int ind = random(0, parkings[parkingInd].getNbPlaces());
    int ret;
    // si la place n'est pas reservée donc pas prise
    if (parkings[parkingInd].getPlacesTab()[ind].getIsReserved() == false)
    {
        ret = ind;
    }
    // sinon si le parkings n'a plus de place disponible
    else if (parkings[parkingInd].getNbAvailablePlaces() == 0 && !parkings[parkingInd].IsFull())
        ret = -1;
    // sinon on rappelle la fonction
    else
        ret = getPlaceInd(parkingInd);
    return ret;
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
    initUser(false);
    Voiture V(conducteurs[conducteurs.size() - 1]);
    for (int i = 0; i < parkings.size(); i++)
    {
        parkings[i].addUsersData(conducteurs[conducteurs.size() - 1]);
    }
    V.indice = voitures.size();

    int Entry = GetEntry();
    V.set_position(GetPosbyNodeInd(Entry) + Vec2(5, 5));

    V.CarColor = random(0, 3);

    V.Exit = GetExit();
    V.setTargetPosition(GetPosbyNodeInd(V.Exit) + Vec2(5, 5));

    V.startTimer = frameParkTime;
    voitures.push_back(V);                                                                                      // Ajout de la voiture dans le tableau de voiture
    Astar(voitures.back(), Entry, GetNodeIndbyPos(voitures.back().getTargetPosition()), voitures.back().nodes); // on lance l'algorithme A* pour trouver le chemin
}

void Environnement::RemoveVoiture(int numVoiture)
{
    // Supprime la voiture du tableau de voiture
    voitures.erase(voitures.begin() + numVoiture);       // On supprime la voiture du tableau
    voitures.shrink_to_fit();                            // On réduit la taille du tableau de voiture
    conducteurs.erase(conducteurs.begin() + numVoiture); // On supprime l'utilisateur du tableau des conducteurs
    conducteurs.shrink_to_fit();                         // On réduit la taille du tableau des conducteurs
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
        int VoiturePosX = voitures[i].get_position().x; // Position de la voiture en x
        if (parkingInd != -1)
        {

            int VoiturePosY = voitures[i].get_position().y;            // Position de la voiture en y
            int TargetParkPosX = parkings[parkingInd].getPos().x * 10; // Position de la parking en x
            int TargetParkPosY = parkings[parkingInd].getPos().y * 10; // Position du parking en y
                                                                       // Si la voiture est dans l'enceinte du parking
            if (VoiturePosX >= TargetParkPosX && VoiturePosX <= TargetParkPosX + parkings[parkingInd].getDIMX() * 10 && VoiturePosY >= TargetParkPosY && VoiturePosY <= TargetParkPosY + parkings[parkingInd].getDIMY() * 10)
            {
                inParking = true;                                                                    // La voiture est dans un parking
                int TargetPlacePosX = parkings[parkingInd].getPlacesTab()[placeInd].getPos().x * 10; // Position de la place en x
                int TargetPlacePosY = parkings[parkingInd].getPlacesTab()[placeInd].getPos().y * 10; // Position de la place en y
                // Si la voiture est dans l'enceinte de la place
                if (VoiturePosX >= TargetPlacePosX && VoiturePosX <= TargetPlacePosX + 10 && VoiturePosY >= TargetPlacePosY && VoiturePosY <= TargetPlacePosY + 20)
                {
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
            }
        }
        if (inParking)
        {
            voitures[i].setIs_in(true);
            if (isInPlace)
            {
                voitures[i].setIs_parked(true);
                parkings[parkingInd].getPlacesTab()[placeInd].setIsTaken(true); // on met à jour l'état de la place
                // parkings[parkingInd].getPlacesTab()[placeInd].setIsReserved(true); // on met à jour l'état de la place

                if (voitures[i].derement == true)
                {
                    voitures[i].startTimer = frameParkTime;
                    voitures[i].derement = false;
                }

                voitures[i].setAngle(0);
            }
            else
            {

                // si la voiture quitte la place
                if (voitures[i].derement == false)
                {
                    voitures[i].startTimer = 0;
                    parkings[parkingInd].getPlacesTab()[placeInd].setIsTaken(false);    // on met à jour l'état de la place
                    parkings[parkingInd].getPlacesTab()[placeInd].setIsReserved(false); // on met à jour l'état de la place
                    voitures[i].setIs_parked(false);                                    // on met à jour l'état de la voiture
                    parkings[parkingInd].incrementNbAvailablePlaces();                  // on incrémente le nombre de place disponible
                    voitures[i].derement = true;                                        // on met à jour le booléen
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
        parkings[i].updateSuccessPercentage(); // On met à jour le pourcentage de succès du parking
        parkings[i].reconsiderPrices();        // On met à jour le prix des places
        parkings[i].addToData(realTime);       // On ajoute les données du parking dans le tableau de données
    }

    double avgSuccessPourcent = (double)(parkings[0].getSuccessPourcentage() + parkings[1].getSuccessPourcentage() + parkings[2].getSuccessPourcentage()) / 3;
    ofstream dataAvgSuccessPourcent("data/dataAvgSuccessPourcent.txt", ios::app);
    if (dataAvgSuccessPourcent)
    {
        dataAvgSuccessPourcent << realTime << endl;
        dataAvgSuccessPourcent << avgSuccessPourcent << endl;
    }
    dataAvgSuccessPourcent.close();
}

// Boucle de jeu
void Environnement::Environnement_play()
{
    prevtime = currentTime;
    currentTime = temps;
    /* Booléen que l'on passera à vrai s'il y a eu,
    durant le passage dans cette fonction, au moins une
    conversation entre un Parking et une Voiture. Si le booléen
    est vrai à la fin de la	fonction, on appellera updateStateCarParks
    de Environnement. */
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
                Astar(voitures[i], GetNodeIndbyPos(voitures[i].get_position()), voitures[i].Exit, voitures[i].nodes);
                voitures[i].ChangeTrajToExit = true;
                voitures[i].isMoving = true;
            }
            else if (voitures[i].ChangeTrajToExit == true && GetNodeIndbyPos(voitures[i].get_position()) == voitures[i].Exit)
            {
                voitures[i].isMoving = true;
                savedConducteurs.push_back(voitures[i].User); // on sauvegarde le conducteur pour qu'il puisse être réutilisé
                voitures[i].deleteNode();
                RemoveVoiture(i);
                break;
            }

            else if (voitures[i].getNbFinishedConv() < 1)
            {
                conversation(voitures[i]);
                voitures[i].incrementNbFinishedConv();
                for (int j = 0; j < parkings.size(); j++)
                {
                    parkings[j].incrementNbFinishedConv();
                }
                changeTarget(voitures[i], voitures[i].getParking());
                aConversationHasEnded = true;
                nbConv++;
            }
            if (!voitures[i].reachGoal && voitures[i].isMoving == true)
                voitures[i].MoveToTargetPosition();
            if (voitures[i].reachGoal)
                voitures[i].deleteNode();
        }
    }
    updateStateVoiture();

    if (aConversationHasEnded)
    {
        updateStateCarParks();
    }
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

const vector<pair<double, double>> Environnement::getDataFromFile(string fileName) const
{
    ifstream file(fileName);
    string line1, line2;
    vector<pair<double, double>> data;
    if (file)
    {
        while (getline(file, line1))
        {
            double d1 = stod(line1);
            getline(file, line2);
            double d2 = stod(line2);
            data.push_back(std::make_pair(d1, d2));
        }
    }
    return data;
}

int Environnement::createConv()
{
    Conversation *newConv = new Conversation;
    if(newConv == nullptr)
        cout<<"erreur, pointeur non-alloué (createConv)"<<endl;
    conv.push_back(newConv);
    return conv.size() - 1;
}

void Environnement::deleteConv(int ind)
{
    conv.at(ind)->getConv().clear();
    delete conv.at(ind);
    //conv.at(ind) = nullptr;
    conv.erase(conv.begin() + ind);
    conv.shrink_to_fit();
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
            conv.at(indConv[parkings.size() - 1 - j])->stockConv("Conversation U" + to_string(v.User.getId()) + "P" + to_string(parkings[parkings.size() - 1 - j].getId()), nbConv);

            // On met à jour les données membres lastNbAgreements
            // et profit du Parking.
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
    tabPrice.clear();
    return idBest;
}

void Environnement::changeTarget(Voiture &v, int indPr)
{
    if (indPr != -1 && parkings[indPr].IsFull() == false)
    {
        v.setParking(indPr);
        v.setPlace(getPlaceInd(indPr));                                        // on set la place dans voiture
        Vec2 Placepos = parkings[indPr].getPlacesTab()[v.getPlace()].getPos(); // on récupère la position de la place
        v.setTargetPosition(Placepos * Vec2(10, 10) + Vec2(5, 5));             // on place la cible au milieu de la place.
        parkings[indPr].getPlacesTab()[v.getPlace()].setIsReserved(true);      // la place est réservée, pour pas qu'une autre voiture puisse y aller.
        if (v.derement)
            parkings[indPr].decrementNbAvailablePlaces();                                                                              // on décrémente le nombre de places disponibles.
        Astar(v, GetNodeIndbyPos(v.get_position()), GetNodeIndbyPos(v.getTargetPosition()), v.nodes); // on change la cible de la voiture
    }
    else
    {
        v.Exit = GetExit();
        Astar(v, GetNodeIndbyPos(v.get_position()), v.Exit, v.nodes);
        v.ChangeTrajToExit = true;
    }
}

void Environnement::removeLogs()
{
    ofstream file("data/logs/rmLogs");
    if (std::filesystem::exists("data/logs/rmLogs"))
    {
        system("rm data/logs/*");
        system("rm data/dataAvgSuccessPourcent.txt");
        system("rm data/dataNbPlaceTaken0.txt");
        system("rm data/dataNbPlaceTaken1.txt");
        system("rm data/dataNbPlaceTaken2.txt");
        system("rm data/dataProfit0.txt");
        system("rm data/dataProfit1.txt");
        system("rm data/dataProfit2.txt");
        system("rm data/dataStartingPrice0.txt");
        system("rm data/dataStartingPrice1.txt");
        system("rm data/dataStartingPrice2.txt");
        system("rm data/userData0.txt");
        system("rm data/userData1.txt");
        system("rm data/userData2.txt");
    }
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
    vector<vector<pair<double, double>>> dataTab;
    vector<double> tabMaxProfit;
    vector<double> tabMaxPlace;
    vector<double> tabMaxPrice;
    for (int i = 0; i < 3; i++)
        if (!getDataFromFile("data/dataProfit" + to_string(i) + ".txt").empty())
            tabMaxProfit.push_back(searchMaxInPair(getDataFromFile("data/dataProfit" + to_string(i) + ".txt")));

    for (int i = 0; i < 3; i++)
        if (!getDataFromFile("data/dataNbPlaceTaken" + to_string(i) + ".txt").empty())
            tabMaxPlace.push_back(searchMaxInPair(getDataFromFile("data/dataNbPlaceTaken" + to_string(i) + ".txt")));

    for (int i = 0; i < 3; i++)
        if (!getDataFromFile("data/dataStartingPrice" + to_string(i) + ".txt").empty())
            tabMaxPrice.push_back(searchMaxInPair(getDataFromFile("data/dataStartingPrice" + to_string(i) + ".txt")));

    switch (choice)
    {
    case 0:
        for (int i = 0; i < 3; i++)
            dataTab.push_back(getDataFromFile("data/dataProfit" + to_string(i) + ".txt"));
        if (!tabMaxProfit.empty())
            Graph(dataTab[0], dataTab[1], dataTab[2], "Profit parking ", 0, 0, realTime, searchMax(tabMaxProfit) + 1);
        break;
    case 1:
        for (int i = 0; i < 3; i++)
            dataTab.push_back(getDataFromFile("data/dataStartingPrice" + to_string(i) + ".txt"));
        if (!tabMaxPrice.empty())
            Graph(dataTab[0], dataTab[1], dataTab[2], "Evolution prix de départ parking ", 0, 0, realTime, searchMax(tabMaxPrice) + 1);
        break;
    case 2:
        for (int i = 0; i < 3; i++)
            dataTab.push_back(getDataFromFile("data/dataNbPlaceTaken" + to_string(i) + ".txt"));
        if (!tabMaxPlace.empty())
            Graph(dataTab[0], dataTab[1], dataTab[2], "Nombres de places occupées parking ", 0, 0, realTime, searchMax(tabMaxPlace) + 1);
        break;
    case 3:
        Graph(getDataFromFile("data/dataAvgSuccessPourcent.txt"), "Pourcentage de succes moyen", 0, 0, realTime, searchMaxInPair(getDataFromFile("data/dataAvgSuccessPourcent.txt")) + 1);
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
     assert(E.conv.size() == 0);
     cout << "Test de regression de la fonction conversation: OK" << endl;
}
