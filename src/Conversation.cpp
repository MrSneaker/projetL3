#include "Conversation.h"

Conversation::Conversation()
{

}

Conversation::~Conversation()
{

}

vector<Message> Conversation::getConv() const
{
    return conv;
}

void Conversation::sendMessage(const string & subject, float price, const string & sender, const string & recipient)
{
    conv.push_back(Message(price,subject,sender,recipient));
}

void Conversation::startConv(Parking p, Voiture v)
{
    //ceci n'est pas définitif, ceci est un test.    
    voiture = thread (&Conversation::sendMessage,this,"CALL",2.5,"U"+to_string(v.User.getId()),"P"+to_string(p.getId()));
    parking = thread (&Conversation::sendMessage,this,"OFFER",3.2,"P"+to_string(p.getId()),"U"+to_string(v.User.getId()));
    voiture.join();
    parking.join();
}

void Conversation::testRegression()
{
    Conversation c;
    Utilisateur u(6,14,"paulo-test");
    Parking p({10,10},100,3,4,10,10,4);
    Voiture v(u);
    c.startConv(p,v);
    assert(c.conv.size() == 2);
    for(int i = 0;i<c.conv.size();i++)
    {
        cout<<"sender : "<<c.getConv().at(i).getSender()<<endl;
        cout<<"recipient : "<<c.getConv().at(i).getRecipient()<<endl;
        cout<<"date : "<<c.getConv().at(i).getDate()<<endl;
        cout<<"subject : "<<c.getConv().at(i).getSubject()<<endl;
        cout<<"price : "<<c.getConv().at(i).getPrice()<<endl;
        cout<<endl;
    }
    
}