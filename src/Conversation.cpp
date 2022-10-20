#include "Conversation.h"

Conversation::Conversation()
{
    //on ouvre la conversation.
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
    //On bloque le mutex durant l'execution de la fonction, il est libéré.
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
    cout << sub << endl;
    conv.push_back(toSend);
}

void Conversation::sendMessageParking(Parking p)
{
    // On fait dormir le sleep 5 milisecondes pour éviter qu'il empiète sur la voiture.
    this_thread::sleep_for(chrono::milliseconds(5));
    lock_guard<mutex> guard(conv_mutex);
    string sub;
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
    cout << sub << endl;
    conv.push_back(toSend);
}

void Conversation::manageConv(Parking p, Voiture v)
{

    //  lancement de la conv
    conv_mutex.lock();
    while (convOK)
    {
        conv_mutex.unlock();
        voiture = thread(&Conversation::sendMessageVoiture, this, v);
        parking = thread(&Conversation::sendMessageParking, this, p);
        if (voiture.joinable())
        {
            voiture.join();
        }
        else
            cout << "pb de join V" << endl;
        if (parking.joinable())
        {
            parking.join();
        }
        else
            cout << "pb de join P" << endl; 
        conv_mutex.lock();
    }
}

bool Conversation::stockConv(const string &fileName)
{
    if (voiture.joinable() == false && parking.joinable() == false)
    {
        string newName = "data/logs/" + fileName + ".txt";
        ofstream stockFile(newName.c_str());
        if (stockFile.is_open())
        {
            for (int i = 0; i < conv.size(); i++)
            {
                stockFile << "sender : " << conv.at(i).getSender() << endl;
                stockFile << "recipient : " << conv.at(i).getRecipient() << endl;
                stockFile << "date : " << conv.at(i).getDate() << endl;
                stockFile << "subject : " << conv.at(i).getSubject() << endl;
                stockFile << "price : " << conv.at(i).getPrice() << endl;
                stockFile << "-----------------------------------------------------" << endl;
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void Conversation::testRegression()
{
    Conversation c, c1;
    Utilisateur u(4.5, 14, "paulo-test");
    Utilisateur u1(6, 15, "paulo-test2");
    Parking p({10, 10}, 100, 3, 4, 10, 10, 4);
    Voiture v(u);
    Voiture v1(u1);
    c.manageConv(p, v);
    c1.manageConv(p, v1);
    assert(c.convOK == false);
    assert(c1.convOK == false);
    c.stockConv("convTest");
    c1.stockConv("convTest2");
}