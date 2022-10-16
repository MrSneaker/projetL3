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

void Conversation::sendMessageVoiture(Voiture v)
{
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

void Conversation::manageConversation(Voiture v, Parking p)
{
    conv_mutex.lock();
    int i = 0;
    while (convOK)
    {
        conv_mutex.unlock();
        sendMessageVoiture(v);
        sendMessageParking(p);
        conv_mutex.lock();
    }
}

void Conversation::startConv(Parking p, Voiture v)
{

    //  lancement de la conv
    //  TODO: on doit tout faire dans un thread et pas deux, et gérer le sens de la conversation dans sendMessage (à renommer).
    //  pour éviter les problèmes de sens de conversation.
    conversation = thread(&Conversation::manageConversation, this, v, p);
    if (conversation.joinable())
    {
        conversation.join();
    }

    else
        cout << "pb de join conversation" << endl;
}

bool Conversation::stockConv(const string &fileName)
{
    if (conversation.joinable() == false)
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
    Utilisateur u(5, 14, "paulo-test");
    Utilisateur u1(6, 15, "paulo-test2");
    Parking p({10, 10}, 100, 3, 4, 10, 10, 4);
    Voiture v(u);
    Voiture v1(u1);
    c.startConv(p, v);
    c1.startConv(p, v1);
    cout << c.stockConv("convTest") << endl;
    cout << c1.stockConv("convTest2") << endl;
}