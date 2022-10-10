#ifndef __CONVERSATION_H__
#define __CONVERSATION_H__

#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include "Message.h"
#include "Voiture.h"
#include "Parking.h"

class Conversation
{
private:
    thread parking;
    thread voiture;
    vector<Message> conv;
    string stockConvP;
    string stockConvV;
    
public:
    Conversation();
    ~Conversation();
    vector<Message> getConv() const;
    //! \brief démarre une conversation entre deux entités en paramètres.
    //! \param p un parking,
    //! \param v une voiture.
    void startConv(Parking p, Voiture v);
    void sendMessage(const string & subject, float price, const string & sender, const string & recipient);
    //! \brief stock la conversation, afin de laisser une trace et permettre au conversants de connaître leur actions passé.
    void stockConv();
    void testRegression();
};


#endif