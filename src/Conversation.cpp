#include "Conversation.h"

Conversation::Conversation()
{
    // on ouvre la conversation.
    convOK = true;
}

Conversation::~Conversation()
{
}

vector<Message> Conversation::getConv() const
{
    return conv;
}

void Conversation::sendMessageVoiture(Voiture v)
{
    // On bloque le mutex durant l'execution de la fonction, il est libéré.
    lock_guard<mutex> guard(conv_mutex);
    string sub;
    Message toSend;
    if (conv.size() == 0)
    {
        toSend = v.managingConversation(nullptr);
    }
    else
    {
        toSend = v.managingConversation(&conv.at(conv.size() - 1));
    }

    sub = toSend.getSubject();

    if (sub == "ACCEPT" || sub == "REJECT" || sub == "UNKNOWN SUBJECT" || sub == "INVALID_TYPE")
    {
        convOK = false;
    }
    conv.push_back(toSend);
}

void Conversation::sendMessageParking(Parking p)
{
    // On fait dormir le sleep 5 milisecondes pour éviter qu'il empiète sur la voiture.
    this_thread::sleep_for(chrono::milliseconds(5));
    // On bloque le mutex durant l'execution de la procédure, il est libéré.
    lock_guard<mutex> guard(conv_mutex);
    // sujet testé en fin de procédure pour mettre à jour convOK.
    string sub;
    // le nouveau message envoyé.
    Message toSend;

    if (conv.size() == 0)
    {
        toSend = p.managingConversation(nullptr);
    }
    else
    {
        toSend = p.managingConversation(&conv.at(conv.size() - 1));
    }

    sub = toSend.getSubject();

    if (sub == "ACCEPT" || sub == "REJECT" || sub == "UNKNOWN SUBJECT" || sub == "INVALID_TYPE")
    {
        convOK = false;
    }
    conv.push_back(toSend);
}

bool Conversation::manageConv(Parking p, Voiture v)
{
    //on bloque le mutex pour ne pas avoir de conflit dans les threads avec convOK.
    lock_guard<mutex> guard(conv_mutex); 
    //  lancement de la conversation, tant qu'elle est valide.
    while (convOK)
    {
        //on débloque le mutex pour laisser les threads fonctionner.
        conv_mutex.unlock();
        voiture = thread(&Conversation::sendMessageVoiture, this, v);
        parking = thread(&Conversation::sendMessageParking, this, p);
        if (voiture.joinable())
        {
            voiture.join();
        }
        else
            return false;
        if (parking.joinable())
        {
            parking.join();
        }
        else
            return false;
        //on rebloque le mutex en fin de boucle pour permettre la vérification de condition.
        conv_mutex.lock();
    }
    return true;
}

bool Conversation::stockConv(const string &fileName)
{
    //si les threads sont terminés, on peut stocker leur conversation.
    if (voiture.joinable() == false && parking.joinable() == false)
    {
        //nom du fichier.
        string newName = "data/logs/" + fileName + ".txt";
        //ouverture du fichier.
        ofstream stockFile(newName.c_str());
        //si le fichier est ouvert on écrit les informations de la conversation.
        if (stockFile.is_open())
        {
            for (int i = 0; i < conv.size(); i++)
            {
                stockFile << "messageNumber : " << conv.at(i).getMessageNumber() << endl;
                stockFile << "sender : " << conv.at(i).getSender() << endl;
                stockFile << "recipient : " << conv.at(i).getRecipient() << endl;
                stockFile << "date : " << conv.at(i).getDate() << endl;
                stockFile << "subject : " << conv.at(i).getSubject() << endl;
                stockFile << "price : " << conv.at(i).getPrice() << endl;
                stockFile << "-----------------------------------------------------" << endl;
            }
            //on retourne vrai quand on fini de tout écrire.
            return true;
        }
        // sinon on retourne false.
        else
            return false;
    }
    //sinon on retourne false.
    else
        return false;
}


void Conversation::testRegression()
{
    Conversation c, c1, c2;
    Utilisateur u(3.5, 14, "paulo-test");
    Utilisateur u1(6, 15, "paulo-test2");
    Utilisateur u2(2, 16, "paulo-test3");
    Parking p({10, 10}, 100, 3, 4, 10, 10, 4);
    Voiture v(u);
    Voiture v1(u1);
    Voiture v2(u2);
    c.manageConv(p, v);
    c1.manageConv(p, v1);
    c2.manageConv(p, v2);
    assert(c.convOK == false);
    assert(c1.convOK == false);
    assert(c2.convOK == false);
    c.stockConv("convTest");
    c1.stockConv("convTest2");
    c2.stockConv("convTest3");
}