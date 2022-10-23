#include "Voiture.h"

#include <iostream>
#include <string.h>

const int REDUCTION_FACTOR = 0.5;

// Constructeur de la classe Voiture
Voiture::Voiture()
{
}

Voiture::Voiture(Utilisateur U)
{
    User = U;
    speed = 5;
    Is_in = false;
    Is_parked = false;
    Is_pathfind = false;
    parking = 0;
    place = 0;
    width = 1;
    height = 2;
    indice = 0;
    position = Vec2(0, 0);
}

// Destructeur de la classe Voiture
Voiture::~Voiture()
{
}

// Déplace la voiture vers la droite
void Voiture::MoveRight()
{
    position.x += speed;
    setAngle(270);
}

// Déplace la voiture vers la gauche
void Voiture::MoveLeft()
{
    position.x -= speed;
    setAngle(90);
}

// Déplace la voiture vers le haut
void Voiture::MoveUp()
{
    position.y += speed;
    setAngle(0);
}

// Déplace la voiture vers le bas
void Voiture::MoveDown()
{
    position.y -= speed;
    setAngle(180);
}

void Voiture::setAngle(int new_angle)
{
    angle = new_angle;
}

int Voiture::getAngle()
{
    return angle;
}

// Renvoie la position (x;y) de la voiture
Vec2 Voiture::get_position()
{
    return position;
}

// Modifie la position (x;y) de la voiture
void Voiture::set_position(Vec2 new_pos)
{
    position = new_pos;
}

// Modifie la position de la cible (parking / place / sortie)
void Voiture::setTargetPosition(Vec2 new_pos)
{
    TargetPosition = new_pos;
}

Vec2 Voiture::getTargetPosition()
{
    return TargetPosition;
}

// // Déplace la voiture vers la position de la cible (parking / place / sortie)
// // On changer la position de la cible quand la voiture entre dans le parking
// // Nouvelle position cible = position place de parking etc.
bool Voiture::MoveToTargetPosition()
{
    if (pathTab.size() > 0)
    {
        Node *Current = pathTab[pathTab.size() - 1];
        if (Current->getNodepos().x * 10 + 5 > position.x)
        {
            MoveRight();
        }
        else if (Current->getNodepos().x * 10 + 5 < position.x)
        {
            MoveLeft();
        }
        else if (Current->getNodepos().y * 10 + 5 > position.y)
        {
            MoveUp();
        }
        else if (Current->getNodepos().y * 10 + 5 < position.y)
        {
            MoveDown();
        }
        else
        {
            pathTab.pop_back();
        }
    }
}

Message Voiture::managingConversation(Message *aMessage) const
{

    string senderString = "User_" + to_string(User.getId());

    if (aMessage != nullptr)
    {

        string recipientString = aMessage->getSender();

        double chosenPrice = -2;              // Initialisation avec une valeur arbitraire absurde
        string responseType = "INVALID_TYPE"; // Initialisation avec un type invalide

        double proposedParkPrice = aMessage->getPrice();
        string sentType = aMessage->getSubject();

        if (sentType == "OFFER" || sentType == "COUNTER_OFFER")
        {
            float userMaxPrice = User.getMaxPrice();
            float nbMessage = aMessage->getMessageNumber();
            if ((proposedParkPrice > userMaxPrice) || (nbMessage >= 20))
            {
                chosenPrice = userMaxPrice;
                responseType = "LAST_OFFER";
            }
            double reducedUserMaxPrice = userMaxPrice / 2;
            // !!!!! On pourra tester avec d'autres variantes (plus avantageuses pour la voiture
            // [ou pour le parking ?]) de cette affectation, comme par exemple userMaxPrice / 3
            // (on nommerait alors la variable thirdOfUserMaxPrice ["third" pour "tiers" et non "troisième"]
            // au lieu de halfUserMaxPrice).

            if (reducedUserMaxPrice < proposedParkPrice <= userMaxPrice)
            {

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

                double deltaInf = abs(reducedUserMaxPrice - proposedParkPrice);
                double deltaSup = abs(proposedParkPrice - userMaxPrice);

                if (deltaInf < deltaSup)
                {
                    // !!!!! On pourra tester avec d'autres variantes (plus avantageuses pour la voiture
                    // [ou pour le parking ?]) de cette condition

                    chosenPrice = proposedParkPrice;

                    responseType = "ACCEPT";
                    // [SUGGGESTION :] Cela ne veut pas dire qu'on va aller dans le parking en question (appelons-le "parking A").
                    // Ce n'est pas une acceptation engageante. En effet, si par la suite, dans une conversation parallèle,
                    // on accepte une offre moins chère avant d'atteindre le parking A, on n'ira pas dans le parking A.
                }

                else if (responseType != "LAST_OFFER")
                {
                    chosenPrice = reducedUserMaxPrice + deltaInf / 3;
                    responseType = "COUNTER_OFFER";
                }
            }

            else
            {

                if (proposedParkPrice <= reducedUserMaxPrice)
                {
                    chosenPrice = proposedParkPrice;
                    responseType = "ACCEPT";
                }
            }
        }

        else if (sentType == "LAST_OFFER")
        {

            if (isPriceOk(proposedParkPrice, User))
            {

                chosenPrice = proposedParkPrice;

                responseType = "ACCEPT";
                // [SUGGGESTION :] Cela ne veut pas dire qu'on va aller dans le parking en question (appelons-le "parking A")
                // (ce n'est pas une acceptation engageante). En effet, si par la suite, dans une conversation parallèle,
                // on accepte une offre moins chère avant d'atteindre le parking A, on n'ira pas dans le parking A.
            }

            else
            {
                chosenPrice = -1;
                responseType = "REJECT";
            }
        }

        if (sentType == "ACCEPT")
        {

            chosenPrice = proposedParkPrice;

            responseType = "ACCEPT";
            // [SUGGGESTION :] Cela ne veut pas dire qu'on va aller dans le parking en question (appelons-le "parking A")
            // (ce n'est pas une acceptation engageante). En effet, si par la suite, dans une conversation parallèle,
            // on accepte une offre moins chère avant d'atteindre le parking A, on n'ira pas dans le parking A.

            // TO DO : il faudra appeler une fonction qui fait que la voiture stocke l'adresse ou l'id (ou je ne sais quoi
            //         qui lui permet d'identifier le parking) du parking, ainsi que le prix accepté, pour que la voiture
            //         puisse ensuite comparer les prix acceptés dans les différentes conversations, et ainsi se diriger
            //         vers le parking lui ayant proposé le meilleur prix.
        }

        if (sentType == "REJECT")
        {

            chosenPrice = -1;

            responseType = "REJECT";
        }

        unsigned int MessageNum = aMessage->getMessageNumber() + 1;
        Message newMessage(MessageNum, chosenPrice, responseType, senderString, recipientString);
        return newMessage;
    }

    else
    {

        string recipientString = "Unknown car park";

        Message newMessage(senderString, recipientString);
        // S'il s'agit du 1er message de la conversation, la voiture ne propose
        // pas de prix (donc on met ce dernier à -1 en appelant le constructeur à 2 paramètres),
        // et le message est de type "CALL" (cf constructeur à 2 paramètres)
        // car la voiture ne fait qu'avertir le parking qu'elle veut démarrer une négociation avec lui.

        return newMessage;
    }
}

bool Voiture::isPriceOk(double price, Utilisateur User) const
{
    double u_price = User.getMaxPrice();

    bool ok = (price <= u_price + 0.05 * u_price);
    // On considère que le prix est acceptable s'il est au plus 5 % trop cher.

    if (ok)
        return true;
    else
        return false;
}

void Voiture::UserGetInfos()
{
    // Donne les infos du conducteur
    std::cout << "Nom : " << User.getName() << std::endl;
    std::cout << "ID : " << User.getId() << std::endl;
    std::cout << "Temps de stationnement : " << User.getParkTime() << std::endl;
    std::cout << "Prix max : " << User.getMaxPrice() << std::endl;
}

float Voiture::getSpeed()
{
    return speed;
}

void Voiture::setSpeed(float new_speed)
{
    speed = new_speed;
}

void Voiture::setIs_in(bool new_is_in)
{
    Is_in = new_is_in;
}

bool Voiture::getIs_in()
{
    return Is_in;
}

void Voiture::setIs_parked(bool new_is_parked)
{
    Is_parked = new_is_parked;
}

bool Voiture::getIs_parked()
{
    return Is_parked;
}

void Voiture::setParking(int new_parking)
{
    parking = new_parking;
}

int Voiture::getParking()
{
    return parking;
}
bool Voiture::setIs_pathfind(bool new_is_pathfind)
{
    Is_pathfind = new_is_pathfind;
}

bool Voiture::getIs_pathfind()
{
    return Is_pathfind;
}

// set place
void Voiture::setPlace(int new_place)
{
    place = new_place;
}

// get place
int Voiture::getPlace()
{
    return place;
}

// set Width
void Voiture::setwidth(int new_width)
{
    width = new_width;
}

// get Width
int Voiture::getwidth()
{
    return width;
}

// set Height
void Voiture::setheight(int new_height)
{
    height = new_height;
}

// get Height
int Voiture::getheight()
{
    return height;
}

vector<Node *> &Voiture::getpathTab()
{
    return pathTab;
}



// -----------------------------------------------------------------------------------------------
// Test de regression la classe Voiture
void Voiture::test_regresion()
{

    std::cout << "Test de regression de la classe Voiture" << std::endl;

    // test constructeur avec parametre
    std::cout << "Test constructeur avec parametre" << std::endl;
    Utilisateur u1(2.54, 34, "Zidane");
    Voiture v1(u1);
    v1.User.setParkTime(2);
    assert(v1.User.getId() == 34);
    assert(v1.User.getMaxPrice() == 2.54);
    assert(v1.User.getName() == "Zidane");
    assert(v1.User.getParkTime() == 2);
    std::cout << "Test constructeur avec parametre OK" << std::endl;

    // Test de la fonction MoveRight()
    std::cout << "Test de la fonction MoveRight()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveRight();
    assert(position.x == 1 && position.y == 0);
    std::cout << "Test de la fonction MoveRight() OK" << std::endl;

    // Test de la fonction MoveLeft()
    std::cout << "Test de la fonction MoveLeft()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveLeft();
    assert(position.x == -1 && position.y == 0);
    std::cout << "Test de la fonction MoveLeft() OK" << std::endl;

    // Test de la fonction MoveUp()
    std::cout << "Test de la fonction MoveUp()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveUp();
    assert(position.x == 0 && position.y == 1);
    std::cout << "Test de la fonction MoveUp() OK" << std::endl;

    // Test de la fonction MoveDown()
    std::cout << "Test de la fonction MoveDown()" << std::endl;
    position.x = 0;
    position.y = 0;
    speed = 1;
    MoveDown();
    assert(position.x == 0 && position.y == -1);
    std::cout << "Test de la fonction MoveDown() OK" << std::endl;

    // test de la fonction set_position()
    std::cout << "Test de la fonction set_position()" << std::endl;
    position.x = 0;
    position.y = 0;
    Vec2 new_pos;
    new_pos.x = 3;
    new_pos.y = 5;
    set_position(new_pos);
    assert(position.x == 3 && position.y == 5);
    std::cout << "Test de la fonction set_position() OK" << std::endl;

    // Test de la fonction get_position()
    std::cout << "Test de la fonction get_position()" << std::endl;
    Vec2 new_pos2 = {2, 5};
    set_position(new_pos2);
    Vec2 pos = get_position();
    assert(pos.x == 2 && pos.y == 5);
    std::cout << "Test de la fonction get_position() OK" << std::endl;

    // Test de la fonction setTargetPosition()
    std::cout << "Test de la fonction setTargetPosition()" << std::endl;
    TargetPosition.x = 0;
    TargetPosition.y = 0;
    Vec2 new_pos3;
    new_pos3.x = 3;
    new_pos3.y = 5;
    setTargetPosition(new_pos3);
    assert(TargetPosition.x == 3 && TargetPosition.y == 5);
    std::cout << "Test de la fonction setTargetPosition() OK" << std::endl;

    // Test de la fonction getTargetPosition()
    std::cout << "Test de la fonction getTargetPosition()" << std::endl;
    Vec2 new_pos4 = {2, 5};
    setTargetPosition(new_pos4);
    Vec2 pos2 = getTargetPosition();
    assert(pos2.x == 2 && pos2.y == 5);
    std::cout << "Test de la fonction getTargetPosition() OK" << std::endl;

    // test de la fonction MoveToTargetPosition()
    std::cout << "Test de la fonction MoveToTargetPosition" << std::endl;
    position.x = 0;
    position.y = 0;
    TargetPosition.x = 3;
    TargetPosition.y = 5;
    speed = 1;
    while (MoveToTargetPosition() == false)
    {
        continue;
    }
    assert(position.x == 3 && position.y == 5);
    std::cout << "Test de la fonction MoveToTargetPosition() OK" << std::endl;

    // Test de la fonction isPriceOk()
    std::cout << "Test de la fonction isPriceOk()" << std::endl;
    Utilisateur u(2.54, 0, "lol");
    Voiture v2(u);
    bool test = isPriceOk(3, User);
    assert(test == true);
    std::cout << "Test de la fonction isPriceOk() OK" << std::endl;

    // test de la fonction setIs_in()
    std::cout << "Test de la fonction setIs_in()" << std::endl;
    setIs_in(true);
    assert(getIs_in() == true);
    std::cout << "Test de la fonction setIs_in() OK" << std::endl;

    // test de la fonction getIs_in()
    std::cout << "Test de la fonction getIs_in()" << std::endl;
    setIs_in(false);
    assert(getIs_in() == false);
    std::cout << "Test de la fonction getIs_in() OK" << std::endl;
}
