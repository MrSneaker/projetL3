#include "Conversation.h"

Conversation::Conversation()
{

}

Conversation::~Conversation()
{

}

void Conversation::sendMessage(string & subject, float price, string & sender, string & recipient)
{
    conv.push_back(Message(subject,price,sender,recipient));
}

void Conversation::startConv(Parking p, Voiture v)
{
    //ceci n'est pas définitif, ceci est un test.    
    voiture = thread (sendMessage,"CALL",2.5,"U"+to_string(v.User.getId()),"P"+to_string(p.getId()));
    parking = thread (sendMessage,"OFFER",3.2,"P"+to_string(p.getId()),"U"+to_string(v.User.getId()));
    voiture.join();
    parking.join();
}