#include "Voiture.h"

#include <iostream>
#include <string.h>
#include <math.h>

// Constructeur de la classe Voiture
Voiture::Voiture()
{
}

Voiture::Voiture(Utilisateur U)
{
    //------------------- Vec2 -------------------
    position = Vec2(0, 0);
    TargetPosition = Vec2(0, 0);
    //------------------- bool -------------------
    Is_in = false;
    Is_parked = false;
    Is_pathfind = false;
    ChangeTrajToExit = false;
    decrement = true;
    reachGoal = false;
    isMoving = true;

    //------------------- float -------------------
    speed = 1;
    startTimer = 0;

    //------------------- int ---------------------
    parking = 0;
    place = 0;
    width = 1;
    height = 2;
    indice = 0;
    nbFinishedConv = 0;
    Exit = 0;
    CarColor = 0;
    //---------------------------------------------
    User = U;

    pathTab.clear();
}


Voiture::~Voiture()
{
}

//--------------------------- Getter + Setter ----------------------------------

void Voiture::setAngle(int new_angle)
{
    angle = new_angle;
}

const int &Voiture::getAngle() const
{
    return angle;
}

void Voiture::set_position(Vec2 new_pos)
{
    position = new_pos;
}

const Vec2 &Voiture::get_position() const
{
    return position;
}

void Voiture::setTargetPosition(Vec2 new_pos)
{
    TargetPosition = new_pos;
}

const Vec2 &Voiture::getTargetPosition() const
{
    return TargetPosition;
}

void Voiture::setCarColor(int new_color)
{
    CarColor = new_color;
}

const int &Voiture::getCarColor() const
{
    return CarColor;
}

const int &Voiture::getSpeed() const
{
    return speed;
}

const int &Voiture::getNbFinishedConv() const
{
    return nbFinishedConv;
}

void Voiture::setSpeed(int new_speed)
{
    speed = new_speed;
}

void Voiture::setIs_in(bool new_is_in)
{
    Is_in = new_is_in;
}

const bool &Voiture::getIs_in() const
{
    return Is_in;
}

void Voiture::setIs_parked(bool new_is_parked)
{
    Is_parked = new_is_parked;
}

const bool &Voiture::getIs_parked() const
{
    return Is_parked;
}

void Voiture::setParking(int new_parking)
{
    parking = new_parking;
}

const int &Voiture::getParking() const
{
    return parking;
}
void Voiture::setIs_pathfind(bool new_is_pathfind)
{
    Is_pathfind = new_is_pathfind;
}

const bool &Voiture::getIs_pathfind() const
{
    return Is_pathfind;
}

void Voiture::setPlace(int new_place)
{
    place = new_place;
}

const int &Voiture::getPlace() const
{
    return place;
}

void Voiture::setwidth(int new_width)
{
    width = new_width;
}

const int &Voiture::getwidth() const
{
    return width;
}

void Voiture::setheight(int new_height)
{
    height = new_height;
}

const int &Voiture::getheight() const
{
    return height;
}

vector<Node *> &Voiture::getpathTab()
{
    return pathTab;
}

//------------------------------------------------------------------------------


void Voiture::MoveRight()
{
    position.x += speed;
    setAngle(270);
}

void Voiture::MoveLeft()
{
    position.x -= speed;
    setAngle(90);
}

void Voiture::MoveUp()
{
    position.y += speed;
    setAngle(0);
}

void Voiture::MoveDown()
{
    position.y -= speed;
    setAngle(180);
}

bool Voiture::MoveToTargetPosition()
{

    if (pathTab.size() > 0)
    {

        Node *Current;
        Current = pathTab[pathTab.size() - 1]; // On r??cup??re le dernier noeud du chemin
        // Donne la position du premier noeud du chemin
        if (Current->getNodepos().x * 10 + 5 > position.x)
        {
            MoveRight();
            return false;
        }
        else if (Current->getNodepos().x * 10 + 5 < position.x) //
        {
            MoveLeft();
            return false;
        }
        else if (Current->getNodepos().y * 10 + 5 > position.y)
        {
            MoveUp();
            return false;
        }
        else if (Current->getNodepos().y * 10 + 5 < position.y)
        {
            MoveDown();
            return false;
        }
        else // Si la voiture est sur le noeud
        {
            Current = nullptr;
            delete Current;
            pathTab.pop_back();
        }
    }
    else
    {
        reachGoal = true;
        isMoving = false;
    }
    return true;
}

void Voiture::deleteNode()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] != nullptr)
        {
            delete nodes[i];
            nodes[i] = nullptr;
        }
    }
    nodes.clear();
    reachGoal = false;
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
            if (proposedParkPrice > userMaxPrice && nbMessage - 1 > 5)
            {
                chosenPrice = userMaxPrice;
                responseType = "LAST_OFFER";
            }
            double reducedUserMaxPrice = userMaxPrice / 2;
            // !!!!! On pourra tester avec d'autres variantes (plus avantageuses pour la voiture
            // [ou pour le parking ?]) de cette affectation, comme par exemple userMaxPrice / 3
            // (on nommerait alors la variable thirdOfUserMaxPrice ["third" pour "tiers" et non "troisi??me"]
            // au lieu de halfUserMaxPrice).

            if (reducedUserMaxPrice < proposedParkPrice <= userMaxPrice)
            {

                /*
                    L'utilisateur re??oit une proposition de tarif inf??rieur au tarif max qu'il accepte,
                mais il essaie quand m??me de faire baisser le prix (en effet, dans la vie, quand on n??gocie le prix
                au march?? dans les pays o?? il est d'usage de n??gocier, on essaie de faire baisser le prix m??me
                si on a "les moyens" de payer plus cher). La donn??e membre maxPrice de l'Utilisateur
                n'est pas un tarif id??al pour ce dernier : l'id??e est plut??t qu'on s'imagine que l'utilisateur ne peut
                pas se permettre de payer plus que maxPrice, sinon il ne respecte plus son budget.

                    On met quand m??me une borne inf??rieure halfUserMaxPrice. Non pas que l'utilisateur ne veut pas payer
                moins cher que halfUserMaxPrice, mais il faut bien mettre un point de d??part de la n??gociation
                du c??t?? utilisateur, tout comme il y en a un du c??t?? Parking (donn??e membre startingPrice).
                Si proposedParkPrice n'est pas suffisament proche de halfUserMaxPrice, la voiture fera un "pas" vers
                le Parking en proposant un prix l??g??rement sup??rieur strictement ?? halfUserMaxPrice (mais strictement inf??rieur
                ?? proposedParkPrice).

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
                    // Ce n'est pas une acceptation engageante. En effet, si par la suite, dans une conversation parall??le,
                    // on accepte une offre moins ch??re avant d'atteindre le parking A, on n'ira pas dans le parking A.
                }

                else if (responseType != "LAST_OFFER")
                {

                    double chosenPriceTimes100 = (reducedUserMaxPrice + deltaSup / 3) * 100;
                    double roundedChosenPriceTimes100 = ceil(chosenPriceTimes100);
                    double chosenPriceMinusOneCentime = roundedChosenPriceTimes100 / 100;
                    /* Les 3 lignes ci-dessus permettent d'affecter la valeur reducedUserMaxPrice + deltaSup / 3
                    ?? chosenPriceMinusOneCentime, mais arrondie au centime (i.e. au centi??me) sup??rieur. On fait cela car
                    ??a n'a pas de sens de proposer un prix plus pr??cis qu'au centime pr??s, et on arrondit
                    vers le haut car le but est que la voiture augmente son prix (pour que la n??gociation avance !). */

                    chosenPrice = chosenPriceMinusOneCentime + 0.01;
                    /* On ajoute 1 centime au prix pour ??tre s??r que ce dernier ne stagne pas. */

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
                // (ce n'est pas une acceptation engageante). En effet, si par la suite, dans une conversation parall??le,
                // on accepte une offre moins ch??re avant d'atteindre le parking A, on n'ira pas dans le parking A.
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
            // (ce n'est pas une acceptation engageante). En effet, si par la suite, dans une conversation parall??le,
            // on accepte une offre moins ch??re avant d'atteindre le parking A, on n'ira pas dans le parking A.
        }

        if (sentType == "REJECT" || sentType == "NO_MORE_SPOTS")
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
        // pas de prix (donc on met ce dernier ?? -1 en appelant le constructeur ?? 2 param??tres),
        // et le message est de type "CALL" (cf constructeur ?? 2 param??tres)
        // car la voiture ne fait qu'avertir le parking qu'elle veut d??marrer une n??gociation avec lui.

        return newMessage;
    }
}

Message Voiture::confirmConversation(Message *aMessage, int indPrOK) const
{
    string senderString = "User_" + to_string(User.getId());    // "Nom de l'User : User_1" par exemple
    string recipientString = aMessage->getSender();             // "Nom du parking : Parking_1" par exemple
    unsigned int messageNum = aMessage->getMessageNumber() + 1; // num??ro du message ?? envoyer
    double price = aMessage->getPrice();                        // prix propos?? par le parking
    string subject;                                             // sujet du message ?? envoyer
    int indPr;                                                  // indice du parking
    indPr = extractIntFromString(recipientString);              // on extrait l'indice du parking dans le nom du parking
    if (indPr == indPrOK)
    {
        subject = "CONFIRM_ACCEPT";
    }
    else
    {
        subject = "RENOUNCE";
        price = -1;
    }
    return Message(messageNum, price, subject, senderString, recipientString);
}

float Voiture::bestPrice(vector<float> tabPrice)
{
    float min = tabPrice.at(0); 
    float tmp = 0;
    for (int i = 0; i < tabPrice.size(); i++)
    {
        if (tabPrice[i] < min)
        {
            if (tabPrice[i] != tmp)
                min = tabPrice[i];
        }
        tmp = tabPrice[i];
    }
    return min;
}

void Voiture::incrementNbFinishedConv()
{
    nbFinishedConv++;
}

int Voiture::extractIntFromString(string aString) const
{
    const char *charString = aString.c_str();
    int anInt;
    while (*charString)
    {
        if ((*charString >= '0') && (*charString <= '9'))

        {
            anInt = atoi(charString);
        }

        charString++;
    }
    return anInt;
}

bool Voiture::isPriceOk(double price, Utilisateur User) const
{
    double u_price = User.getMaxPrice();

    bool ok = (price <= u_price + 0.05 * u_price);
    // On consid??re que le prix est acceptable s'il est au plus 5 % trop cher.

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

// -----------------------------------------------------------------------------------------------
// Test de regression la classe Voiture
void Voiture::test_regresion()
{

    std::cout << "Test de regression de la classe Voiture" << std::endl;

    // test constructeur avec parametre
    std::cout << "Test constructeur avec parametre" << std::endl;
    Utilisateur u1(2.54, 34, "Zidane", "Zinedine", 1, 2);
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

    // Test de la fonction isPriceOk()
    std::cout << "Test de la fonction isPriceOk()" << std::endl;
    Utilisateur u(2.54, 0, "Zidane", "Zinedine", 1, 2);
    Voiture v2(u);
    bool test = isPriceOk(3, User);
    assert(test == false);
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
