#include "Parking.h"

// CONSTRUCTEUR et DESTRUCTEUR

Parking::Parking(Vec2 position, int numberOfPlaces, float minimumPrice, float startPrice, int DIMX, int DIMY, int id)
    : pos(position), nbPlaces(numberOfPlaces), minPrice(minimumPrice),
      startingPrice(startPrice), nbAvailablePlaces(numberOfPlaces),
      isFull(false), nbTotalVisits(0), DIMX(DIMX), DIMY(DIMY), idP(id)
{

    initPlace(1, 1, position.x + 1, position.y + 1);
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

int Parking::getDIMX() const
{
    return DIMX;
}

int Parking::getDIMY() const
{
    return DIMY;
}

int Parking::getId() const
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

vector<int> Parking::getConversationsTab() const
{
    return conversationsTab;
}

vector<pair<int, Utilisateur *>> Parking::getUsersTab() const
{
    return usersTab;
}

int Parking::getNbTotalVisits() const
{
    return nbTotalVisits;
}

Vec2 Parking::getPos() const
{
    return pos;
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

void Parking::setMinPrice(float minimumPrice)
{
    minPrice = minimumPrice;
}

void Parking::setStartingPrice(float startPrice)
{

    startingPrice = startPrice;
}

void Parking::setConversationsTab()
{
}

void Parking::addUsersTab(Utilisateur *unUtilisateur)
{
    bool addOk = false; // on initialise un bool sur false, bool qui définit si on ajoute ou non l'utilisateur.
    if (usersTab.size() == 0)
        addOk = true; // dans le cas ou le tableau est vide, pas besoin de vérifier donc on ajoute.
    for (int i = 0; i < usersTab.size(); i++)
    {
        if (usersTab[i].second->getId() == unUtilisateur->getId())
        {
            addOk = false; // si on trouve le meme id deux fois, on ajoute pas.
            break;
        }
        else
            addOk = true;
    }
    if (addOk) // si addOk est vraie en fin de procédure, on ajoute alors l'utilisateur.
        usersTab.push_back(make_pair(0, unUtilisateur));
}

void Parking::incrementNbTotalVisits()
{
    nbTotalVisits++;
}

void Parking::incrementNbVisitsTab(Utilisateur *unUtilisateur)
{
    for (int i = 0; i < usersTab.size(); i++)
    {
        if (usersTab.at(i).second->getId() == unUtilisateur->getId())
        {
            usersTab.at(i).first++;
        }
    }
    incrementNbTotalVisits();
}

void Parking::initPlace(int nbPlLigne, int nbPlCol, int PcornerX, int PcornerY)
{
    int indPl = 1;

    nbPlCol = DIMX / 2 - 1; //(DIMX-2)*(DIMY-2) / nbPlaces;
    nbPlLigne = DIMY / 4;   // On divise par 4 car les places font 2 de hauteur et qu'il y'en a 1 toutes les 2 lignes
    // On en repalera dans la semaine Mateo mais dcp la les places sont constuite en fonction de la taille du parking pour le remplir en entier
    // Et non pas du nombre de place

    for (int i = 0; i < nbPlLigne; i++)
    {
        for (int j = 0; j < nbPlCol; j++)
        {
            Place p = Place(Vec2(PcornerX + j * 2, PcornerY + i * 3 + i), indPl, false);
            placesTab.push_back(p);
            indPl++;
        }
    }
}




bool Parking::isPriceOk(double price) const
{

    bool ok = (price >= minPrice - 0.05 * minPrice);
    // On considère que le prix est acceptable s'il est au plus 5 % trop peu élevé.

    if (ok)
        return true;
    else
        return false;
}







Message Parking::managingConversation (Message* aMessage) const {

    string senderString = "Car_park_" + to_string (getId ());
    string recipientString = "User_" + aMessage -> getSender ();

    float chosenPrice = -2; // Initialisation avec une valeur arbitraire absurde
    string responseType = "INVALID_TYPE"; // Initialisation avec un type invalide

    double proposedCarPrice = aMessage ->getPrice ();
    string sentType = aMessage -> getSubject ();



    if (sentType == "CALL") {
        chosenPrice = startingPrice;
        responseType = "OFFER";
    }


    if (sentType == "COUNTER_OFFER") {


        if (minPrice < proposedCarPrice <= startingPrice) {

            /*
                L'utilisateur reçoit une proposition de tarif inférieur au tarif max qu'il accepte,
            mais il essaie quand même de faire baisser le prix (en effet, dans la vie, quand on négocie le prix
            au marché dans les pays où il est d'usage de négocier, on essaie de faire baisser le prix même
            si on a "les moyens" de payer plus cher). La donnée membre maxPrice de l'Utilisateur
            n'est pas un tarif idéal pour ce dernier : l'idée est plutôt qu'on s'imagine que l'utilisateur ne peut
            pas se permettre de payer plus que maxPrice, sinon il ne respecte plus son budget.

                On met quand même une borne inférieure halfUserMaxPrice. Non pas que l'utilisateur ne veut pas payer
            moins cher que halfUserMaxPrice, mais il faut bien mettre un point de départ de la négociation
            du côté utilisateur, tout comme il y en a un du côté Parking (donnée membre startingPrice).
            Si proposedParkPrice n'est pas suffisament proche de halfUserMaxPrice, la voiture fera un "pas" vers
            le Parking en proposant un prix légèrement supérieur strictement à halfUserMaxPrice (mais strictement inférieur
            à proposedParkPrice).

            */

           float deltaSup = abs (startingPrice - proposedCarPrice);
           float deltaInf = abs (proposedCarPrice - minPrice);
            
            if (deltaSup < deltaInf) {
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

            else {

                chosenPrice = startingPrice - deltaSup / 2;
                responseType = "COUNTER_OFFER";

            }

        }

        else {

            if (proposedCarPrice >= startingPrice) {

                chosenPrice = proposedCarPrice;
                responseType = "ACCEPT";

            }


        }
        
    }






    if (sentType == "LAST_OFFER") {

        if (isPriceOk (proposedCarPrice)) {

            chosenPrice = proposedCarPrice;

            responseType = "ACCEPT";
            // [SUGGGESTION :] Cela veut dire que le parking acceptera forcément la voiture S'IL A ENCORE
            // DE LA PLACE quand la voiture arrivera à son entrée, et ce au prix chosenPrice.
            // En revanche, cela ne veut pas dire que la voiture va aller dans ce parking (appelons-le "parking A").
            // Ce n'est pas un accord engageant. En effet, si par la suite, dans une conversation parallèle,
            // la voiture se met d'accord avec un autre parking pour une offre moins chère avant d'atteindre le parking A,
            // elle n'ira pas dans le parking A.

        }

        else {
            chosenPrice = -1;
            responseType = "REJECT";
        }

    }

    if (sentType == "ACCEPT") {

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


    if (sentType == "REJECT") {

        chosenPrice = -1;

        responseType = "REJECT";

    }





    Message newMessage (chosenPrice, responseType, senderString, recipientString);
    return newMessage;

}















void Parking::testRegression()
{
    Parking p1(Vec2(1, 1), 180, 0.4, 0.4, 40, 36,1);

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

    Utilisateur u1(2.5, 1, "paulo-1");
    Utilisateur u2(2.5, 2, "paulo-2");
    p1.addUsersTab(&u1);
    p1.addUsersTab(&u2);
    p1.addUsersTab(&u1);
    assert(p1.usersTab.size() == 2);
    p1.incrementNbVisitsTab(&u1);
    p1.incrementNbVisitsTab(&u1);
    assert(p1.getUsersTab().at(0).first == 2);
    assert(p1.nbTotalVisits == 2);
}