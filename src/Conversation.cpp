#include "Conversation.h"

Conversation::Conversation()
{
    convOK = true;
}

Conversation::~Conversation()
{
}

vector<Message> Conversation::getConv() const
{
    return conv;
}

void Conversation::sendMessage(bool isACar, Voiture v, Parking p)
{
    lock_guard<mutex> guard(conv_mutex);
    string sub;
    Message toSend;
    if (isACar)
    {
        if (conv.size() == 0)
        {
            toSend = v.managingConversation(nullptr);
        }

        else
        {
            toSend = v.managingConversation(&conv.at(conv.size() - 1));
        }
    }
    else
    {
        if (conv.size() == 0)
        {
            toSend = p.managingConversation(nullptr);
        }
        else
        {
            toSend = p.managingConversation(&conv.at(conv.size() - 1));
        }
    }
    sub = toSend.getSubject();
    if (sub == "ACCEPT" || sub == "REJECT" || sub == "UNKNOWN SUBJECT" || sub == "INVALID_TYPE")
    {
        convOK = false;
    }
    conv.push_back(toSend);
}

void Conversation::startConv(Parking p, Voiture v)
{
    conv_mutex.lock();
    while (convOK)
    {
        conv_mutex.unlock();
        // lancement de la conv
        // TODO: on doit tout faire dans un thread et pas deux, et gérer le sens de la conversation dans sendMessage (à renommer).
        // pour éviter les problèmes de sens de conversation.
        voiture = thread(&Conversation::sendMessage, this, true, v, p);
        parking = thread(&Conversation::sendMessage, this, false, v, p);
        if (voiture.joinable())
            voiture.join();
        else
            cout << "pb de join V" << endl;
        if (parking.joinable())
            parking.join();
        else
            cout << "pb de join P" << endl;
        conv_mutex.lock();
    }
}

bool Conversation::stockConv(const string &fileName)
{
    string newName = "data/"+fileName + ".txt";
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
            stockFile <<"-----------------------------------------------------"<< endl;
        }
        return true;
    }
    else return false;
}

void Conversation::testRegression()
{
    Conversation c;
    Utilisateur u(2.5, 14, "paulo-test");
    Parking p({10, 10}, 100, 3, 4, 10, 10, 4);
    Voiture v(u);
    c.startConv(p, v);
    c.stockConv("convTest");
}