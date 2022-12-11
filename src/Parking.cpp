#include "Parking.h"

// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking(Vec2 position, float minimumPrice, float startPrice, int DimX, int DimY, int id)
{
    pos = (position);
    minPrice = (minimumPrice);
    startingPrice = (startPrice);
    isFull = (false);
    nbTotalVisits = (0);
    DIMX = DimX;
    DIMY = DimY;
    nbPlaces = ((DIMX / 2 - 1) * (DIMY / 4));
    nbAvailablePlaces = (nbPlaces);
    idP = (id);
    successPercentage = 100;
    successPercentageLastConv = 100;
    lastNbAgreements = 0;
    lastNbFinishedConv = 0;
    profit = 0;
    nbFinishedConv = 0;
    nbAgreement = 0;
    lastNbAgreements = 0;
    lastNbFinishedConv = 0;
    initPlace(position.x + 1, position.y + 1);
}

Parking::Parking()
{
}

Parking::~Parking()
{
}

// ACCESSEURS

vector<Place> &Parking::getPlacesTab()
{
    return placesTab;
}

int Parking::getNbPlaces() const
{
    return nbPlaces;
}

int Parking::getNbAvailablePlaces() const
{
    return nbAvailablePlaces;
}

int Parking::getMinPrice() const
{
    return minPrice;
}

int Parking::getStartingPrice() const
{
    return startingPrice;
}

const double &Parking::getProfit() const
{
    return profit;
}

const int &Parking::getDIMX() const
{
    return DIMX;
}

const int &Parking::getDIMY() const
{
    return DIMY;
}

const int &Parking::getId() const
{
    return idP;
}

bool Parking::IsFull()
{
    if (nbAvailablePlaces == 0)
    {
        isFull = true;
    }
    else
    {
        isFull = false;
    }
    return isFull;
}

const int &Parking::getNbTotalVisits() const
{
    return nbTotalVisits;
}

const Vec2 &Parking::getPos() const
{
    return pos;
}

const double &Parking::getSuccessPourcentage() const
{
    return successPercentage;
}

// MUTATEURS
void Parking::decrementNbAvailablePlaces()
{
    nbAvailablePlaces--;
    IsFull();
}

void Parking::incrementNbAvailablePlaces()
{
    nbAvailablePlaces++;
    IsFull();
}

void Parking::setNbAvailablePlaces(int nb)
{
    nbAvailablePlaces = nb;
    IsFull();
}

void Parking::incrementNbAgreements()
{
    nbAgreement++;
    lastNbAgreements++;
}

void Parking::incrementNbFinishedConv()
{
    nbFinishedConv++;
    lastNbFinishedConv++;
}

void Parking::updateProfit(double aPrice, float parkTime)
{
    float realParkTime = (parkTime * 10);
    // cout<<"parTime : "<<parkTime<<endl;
    // cout<<"realParkTime : "<<realParkTime<<endl;
    double nbMinutesParked = (double)(realParkTime / 60);
    // cout<<"aPrice : "<<aPrice<<endl;
    // cout<<"nbMinutes : "<<nbMinutesParked<<endl;
    profit += (aPrice * nbMinutesParked);
    // cout<<profit<<endl;
}

void Parking::updateSuccessPercentage()
{

    if (nbFinishedConv > 0)
    {
        successPercentageLastConv = (lastNbAgreements * 100 / lastNbFinishedConv);
        successPercentage = nbAgreement * 100 / nbFinishedConv;
    }
    if (nbFinishedConv % 10 == 0)
    {
        lastNbAgreements = 0;
        lastNbFinishedConv = 0;
    }
}

void Parking::setMinPrice(float minimumPrice)
{
    minPrice = minimumPrice;
}

void Parking::setStartingPrice(float startPrice)
{

    startingPrice = startPrice;
}

void Parking::addUsersData(Utilisateur unUtilisateur)
{

    bool addOk = false; // on initialise un bool sur false, bool qui définit si on ajoute ou non l'utilisateur.
    if (!std::filesystem::exists("data/userData" + to_string(idP) + ".txt"))
    {
        addOk = true; // dans le cas ou le tableau est vide, pas besoin de vérifier donc on ajoute.
    }
    else if (!addOk)
    {
        int id;
        ifstream rUserData("data/userData" + to_string(idP) + ".txt");
        if (rUserData)
        {
            string line;
            while (getline(rUserData, line))
            {
                stringstream ss(line); // on crée un flux à partir de la ligne lue
                string token;          // une variable pour stocker les mots lus
                vector<string> tokens; // un tableau pour stocker les mots lus
                while (getline(ss, token, ','))
                {
                    tokens.push_back(token); // on ajoute le mot lu au tableau
                }
                id = stoi(tokens[0]);

                if (id == unUtilisateur.getId())
                {
                    addOk = false; // si on trouve le meme id deux fois, on ajoute pas.
                    break;
                }
                else
                    addOk = true;
            }
        }
        rUserData.close();
    }
    if (addOk) // si addOk est vraie en fin de procédure, on ajoute alors l'utilisateur.
    {
        ofstream userData("data/userData" + to_string(idP) + ".txt", ios::app);
        if (userData)
        {
            userData << unUtilisateur.getId() << ",";
            userData << unUtilisateur.getParkTime() << ",";
            userData << 0 << endl;
        }
        userData.close();
    }
    // usersTab.push_back(make_pair(0, unUtilisateur));
}

void Parking::addToData(double currentTime)
{
    ofstream dataProfit("data/dataProfit" + to_string(idP) + ".txt", ios::app);
    ofstream dataStartingPrice("data/dataStartingPrice" + to_string(idP) + ".txt", ios::app);
    ofstream dataNbPlaceTaken("data/dataNbPlaceTaken" + to_string(idP) + ".txt", ios::app);
    if (dataProfit)
    {
        dataProfit << currentTime << endl;
        dataProfit << profit << endl;
    }

    if (dataStartingPrice)
    {
        dataStartingPrice << currentTime << endl;
        dataStartingPrice << startingPrice << endl;
    }

    if (dataProfit)
    {
        dataNbPlaceTaken << currentTime << endl;
        dataNbPlaceTaken << (nbPlaces - nbAvailablePlaces) << endl;
    }

    dataProfit.close();
    dataNbPlaceTaken.close();
    dataStartingPrice.close();
}

void Parking::incrementNbTotalVisits()
{
    nbTotalVisits++;
}

void Parking::incrementNbVisitsUser(unsigned int idU)
{
    int id;
    int nbVisit;
    vector<vector<string>> linesData; // un tableau pour stocker les lignes lus
    ifstream rUserData("data/userData" + to_string(idP) + ".txt");
    if (rUserData)
    {
        string line;
        while (getline(rUserData, line))
        {
            stringstream ss(line); // on crée un flux à partir de la ligne lue
            vector<string> tokens; // un tableau pour stocker les mots lus
            string token;          // une variable pour stocker les mots lus
            while (getline(ss, token, ','))
            {
                tokens.push_back(token); // on ajoute le mot lu au tableau
            }
            id = stoi(tokens[0]);
            nbVisit = stoi(tokens[2]);
            if (id == idU)
            {
                // si on trouve le meme id deux fois, on incrémente son nombre de visite.
                nbVisit++;
                tokens[2] = to_string(nbVisit);
            }
            linesData.push_back(tokens);
        }
        rUserData.close();
    }
    ofstream userData("data/userData" + to_string(idP) + ".txt", ios::trunc);
    for (int i = 0; i < linesData.size(); i++)
    {
        if (userData)
        {
            userData << linesData[i].at(0) << ",";
            userData << linesData[i].at(1) << ",";
            userData << linesData[i].at(2) << endl;
        }
    }
    userData.close();
    incrementNbTotalVisits();
}

void Parking::initPlace(int PcornerX, int PcornerY)
{
    int indPl = 1;

    int nbPlCol = DIMX / 2 - 1; //(DIMX-2)*(DIMY-2) / nbPlaces;
    int nbPlLigne = DIMY / 4;   // On divise par 4 car les places font 2 de hauteur et qu'il y'en a 1 toutes les 2 lignes
    // On en repalera dans la semaine Mateo mais dcp la les places sont constuite en fonction de la taille du parking pour le remplir en entier
    // Et non pas du nombre de place
    for (int i = 0; i < nbPlLigne; i++)
    {
        for (int j = 0; j < nbPlCol; j++)
        {
            Place p = Place(Vec2(PcornerX + j * 2, PcornerY + i * 3 + i), indPl);
            placesTab.push_back(p);
            indPl++;
        }
    }
}

bool Parking::isPriceOk(double price) const
{

    bool ok = (price >= minPrice * 0.95);
    // On considère que le prix est acceptable s'il est au plus 5 % trop peu élevé.

    if (ok)
        return true;
    else
        return false;
}

Message Parking::managingConversation(Message *aMessage) const
{

    string senderString = "Car_park_" + to_string(getId());

    if (aMessage != nullptr)
    {
        string recipientString = aMessage->getSender();
        unsigned int idU = extractIntFromString(recipientString);

        double chosenPrice = -2;              // Initialisation avec une valeur arbitraire absurde
        string responseType = "INVALID_TYPE"; // Initialisation avec un type invalide

        double proposedCarPrice = aMessage->getPrice();
        string sentType = aMessage->getSubject();

        if (sentType == "CALL")
        {
            int nbVisit;
            int nbVisitU;
            vector<vector<string>> linesData; // un tableau pour stocker les lignes lus
            ifstream rUserData("data/userData" + to_string(idP) + ".txt");
            if (rUserData)
            {
                double reduc;
                string line;
                while (getline(rUserData, line))
                {
                    stringstream ss(line); // on crée un flux à partir de la ligne lue
                    vector<string> tokens; // un tableau pour stocker les mots lus
                    string token;          // une variable pour stocker les mots lus
                    while (getline(ss, token, ','))
                    {
                        tokens.push_back(token); // on ajoute le mot lu au tableau
                    }
                    int id = stoi(tokens[0]);
                    nbVisit = stoi(tokens[2]);
                    if (id == idU)
                    {
                        // si on trouve le meme id deux fois, on retient le nombre de visite de l'utilisateur.
                        nbVisitU = nbVisit;
                    }
                    linesData.push_back(tokens);
                }
                rUserData.close();
                reduc = (0.05 * nbVisitU) * startingPrice;
                chosenPrice = startingPrice - reduc;
                responseType = "OFFER";
            }
        }

        if (sentType == "COUNTER_OFFER")
        {
            int nbMessage = aMessage->getMessageNumber();
            if (nbMessage > 5)
            {
                chosenPrice = minPrice;
                responseType = "LAST_OFFER";
            }

            else if ((proposedCarPrice <= startingPrice))
            {

                /*
                    Le parking reçoit une proposition de tarif supérieur au tarif minimum qu'il accepte,
                mais il essaie quand même de faire monter le prix (en effet, dans la vie, quand on est vendeur et qu'on négocie le prix
                au marché dans les pays où il est d'usage de négocier, on essaie de faire monter le prix même
                si on a "les moyens" de vendre moins cher). La donnée membre minPrice du Parking
                n'est pas un tarif idéal pour ce dernier : l'idée est plutôt qu'on s'imagine que le parking ne peut
                pas se permettre de vendre moins cher que minPrice, sinon il ne respecte plus ses objectifs financiers.

                    On met quand même une borne supérieure startingPrice. Non pas que le parking ne veut pas vendre
                plus cher que startingPrice, mais il faut bien mettre un point de départ de la négociation
                du côté parking, tout comme il y en a un du côté Utilisateur (variable halfUserMaxPrice locale à la fonction membre managingConversation de Voiture).
                Si proposedCarPrice n'est pas suffisament proche de startingPrice, le parking fera un "pas" vers
                la Voiture en proposant un prix légèrement inférieur strictement à startingPrice (mais strictement supérieur
                à proposedCarPrice).

                */

                double deltaSup = abs(startingPrice - proposedCarPrice);
                double deltaInf = abs(proposedCarPrice - minPrice);

                if (deltaSup < deltaInf)
                {
                    // !!!!! On pourra tester avec d'autres variantes (plus avantageuses pour le parking
                    // [ou pour la voiture ?]) de cette condition.

                    chosenPrice = proposedCarPrice;

                    responseType = "ACCEPT";
                    // [SUGGGESTION :] Cela veut dire que le parking acceptera forcément la voiture S'IL A ENCORE
                    // DE LA PLACE quand la voiture arrivera à son entrée, et ce au prix chosenPrice.
                    // En revanche, cela ne veut pas dire que la voiture va aller dans ce parking (appelons-le "parking A").
                    // Ce n'est pas un accord engageant. En effet, si par la suite, dans une conversation parallèle,
                    // la voiture se met d'accord avec un autre parking pour une offre moins chère avant d'atteindre le parking A,
                    // elle n'ira pas dans le parking A.
                }

                else if (responseType != "LAST_OFFER")
                {
                    double chosenPriceTimes100 = (startingPrice - deltaSup / 2) * 100;
                    double roundedChosenPriceTimes100 = floor(chosenPriceTimes100);
                    double chosenPricePlusOneCent = roundedChosenPriceTimes100 / 100;
                    /* Les 3 lignes ci-dessus permettent d'affecter la valeur startingPrice - deltaSup / 2
                    à chosenPricePlusOneCentime, mais arrondie au centime (i.e. au centième) inférieur. On fait cela car
                    ça n'a pas de sens de proposer un prix plus précis qu'au centime près, et on arrondit
                    vers le bas car le but est que le parking diminue son prix (pour que la négociation avance !). */

                    chosenPrice = chosenPricePlusOneCent - 0.01;
                    /* On retire 1 centime au prix pour être sûr que ce dernier ne stagne pas. */

                    responseType = "COUNTER_OFFER";
                }
            }

            else
            {
                if (proposedCarPrice >= startingPrice)
                {

                    chosenPrice = proposedCarPrice;
                    responseType = "ACCEPT";
                    // [SUGGGESTION :] Cela veut dire que le parking acceptera forcément la voiture S'IL A ENCORE
                    // DE LA PLACE quand la voiture arrivera à son entrée, et ce au prix chosenPrice.
                    // En revanche, cela ne veut pas dire que la voiture va aller dans ce parking (appelons-le "parking A").
                    // Ce n'est pas un accord engageant. En effet, si par la suite, dans une conversation parallèle,
                    // la voiture se met d'accord avec un autre parking pour une offre moins chère avant d'atteindre le parking A,
                    // elle n'ira pas dans le parking A.
                }
            }
        }

        if (sentType == "LAST_OFFER")
        {
            if (isPriceOk(proposedCarPrice))
            {

                chosenPrice = proposedCarPrice;

                responseType = "ACCEPT";
                // [SUGGGESTION :] Cela veut dire que le parking acceptera forcément la voiture S'IL A ENCORE
                // DE LA PLACE quand la voiture arrivera à son entrée, et ce au prix chosenPrice.
                // En revanche, cela ne veut pas dire que la voiture va aller dans ce parking (appelons-le "parking A").
                // Ce n'est pas un accord engageant. En effet, si par la suite, dans une conversation parallèle,
                // la voiture se met d'accord avec un autre parking pour une offre moins chère avant d'atteindre le parking A,
                // elle n'ira pas dans le parking A.
            }

            else
            {
                chosenPrice = -1;
                responseType = "REJECT";
            }
        }

        if (nbAvailablePlaces == 0)
        {
            responseType = "NO_MORE_SPOTS";
            chosenPrice = -1;
        }

        if (sentType == "ACCEPT")
        {

            chosenPrice = proposedCarPrice;

            responseType = "ACCEPT";
            // [SUGGGESTION :] Cela veut dire que le parking acceptera forcément la voiture S'IL A ENCORE
            // DE LA PLACE quand la voiture arrivera à son entrée, et ce au prix chosenPrice.
            // En revanche, cela ne veut pas dire que la voiture va aller dans ce parking (appelons-le "parking A").
            // Ce n'est pas un accord engageant. En effet, si par la suite, dans une conversation parallèle,
            // la voiture se met d'accord avec un autre parking pour une offre moins chère avant d'atteindre le parking A,
            // elle n'ira pas dans le parking A.

            // TO DO : il faudra appeler une fonction qui fait que le parking stocke l'adresse de l'utilisateur
            //         pour savoir que, si ce dernier arrive à son entrée, la négociation a déjà été faite et le prix
            //         décidé.
        }

        if (sentType == "REJECT")
        {

            chosenPrice = -1;

            responseType = "REJECT";
        }

        unsigned int MessageNum = aMessage->getMessageNumber() + 1;
        Message newMessage(MessageNum, chosenPrice, responseType, senderString, recipientString);
        if(responseType == "INVALID_TYPE")
        {
            cout<<"prix prop : "<<proposedCarPrice<<endl;
            cout<<"prix min park : "<<minPrice<<endl;
            cout<<"prix dep park : "<<startingPrice<<endl;
        }
        return newMessage;
    }

    else
    {

        string recipientString = "Unknown user";

        Message newMessage(senderString, recipientString);
        // S'il s'agit du 1er message de la conversation, la voiture ne propose
        // pas de prix (donc on met ce dernier à -1 en appelant le constructeur à 2 paramètres),
        // et le message est de type "CALL" (cf constructeur à 2 paramètres)
        // car la voiture ne fait qu'avertir le parking qu'elle veut démarrer une négociation avec lui.

        return newMessage;
    }
}

Message Parking::confirmConversation(Message *aMessage)
{
    string senderString = "Car_Park_" + to_string(getId());
    string recipientString = aMessage->getSender();
    unsigned int messageNum = aMessage->getMessageNumber() + 1;
    double price = aMessage->getPrice();
    string subject;

    if (aMessage->getSubject() == "CONFIRM_ACCEPT")
    {
        subject = "OK_TO_PARK";
    }

    else
    {
        subject = "ABORT";
        price = -1;
    }

    return Message(messageNum, price, subject, senderString, recipientString);
}

void Parking::reconsiderPrices()
{
    if (successPercentageLastConv < 50)
    {
        bool limit = false;
        double reductionStartPrice = (50 - successPercentage) / 100 * startingPrice;
        if (startingPrice - reductionStartPrice >= minPrice)
            setStartingPrice(startingPrice - reductionStartPrice);
        else
            limit = true;

        if (limit)
        {
            setMinPrice(minPrice * 0.98);
        }
    }
    else if (successPercentageLastConv > 70)
    {
        double augNbPlDependance;
        unsigned int nbPlacesTaken = (nbPlaces - nbAvailablePlaces);
        if (nbPlacesTaken != 0)
            augNbPlDependance = (((double)(nbPlacesTaken * 100 / nbPlaces) + 1) / 100);
        else
            augNbPlDependance = 1;

        double augmentation = 1.2 + augNbPlDependance;
        if (minPrice < 7)
        {
            setMinPrice(augmentation * minPrice);
            setStartingPrice(augmentation * startingPrice);
        }
    }
}

int Parking::extractIntFromString(string aString) const
{
    const char *charString = aString.c_str(); // On convertit la string en char*
    string anIntTmp;
    int anInt;
    while (*charString)
    {
        // On avance dans la string jusqu'à trouver le premier chiffre
        if ((*charString >= '0') && (*charString <= '9'))
        {
            // On convertit le char* en int
            anIntTmp += *charString;
        }
        charString++;
    }
    anInt = stoi(anIntTmp);
    return anInt;
}

void Parking::testRegression()
{
    Parking p1(Vec2(1, 1), 0.4, 0.4, 40, 36, 1);

    // test de la focntion getPlacesTab
    assert(p1.getPlacesTab().size() == p1.placesTab.size());
    assert(p1.getPlacesTab()[0].getPos().x == p1.placesTab[0].getPos().x);
    assert(p1.getPlacesTab()[0].getPos().y == p1.placesTab[0].getPos().y);
    assert(p1.getPlacesTab()[0].getIndP() == p1.placesTab[0].getIndP());
    assert(p1.getPlacesTab()[0].getIsTaken() == p1.placesTab[0].getIsTaken());

    p1.getPlacesTab()[0].setIsTaken(false);
    cout << "Etat de la place 1 : " << p1.getPlacesTab()[0].getIsTaken() << endl;
    cout << "Etat de la place 1 : " << p1.placesTab[0].getIsTaken() << endl;

    p1.placesTab[0].setIsTaken(true);
    cout << "Etat de la place 1 : " << p1.placesTab[0].getIsTaken() << endl;
    cout << "Etat de la place 1 : " << p1.getPlacesTab()[0].getIsTaken() << endl;
    assert(p1.getPlacesTab()[0].getIsTaken() == p1.placesTab[0].getIsTaken());
    Utilisateur u1(2.5, 1, "paulo-1", " pilo", 20, 2);
    Utilisateur u2(2.5, 2, "paulo-2", " pilo", 20, 2);
    p1.addUsersData(u1);
    p1.addUsersData(u2);
    p1.addUsersData(u1);
    p1.incrementNbVisitsUser(u1.getId());
    p1.incrementNbVisitsUser(u1.getId());
    assert(p1.nbTotalVisits == 2);
}