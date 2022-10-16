#ifndef __CONVERSATION_H__
#define __CONVERSATION_H__

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include "Message.h"
#include "Voiture.h"
#include "Parking.h"

class Conversation
{
private:
    thread conversation;
    vector<Message> conv;
    string stockConvP;
    string stockConvV;
    bool convOK;
    mutex conv_mutex;
    mutex convOK_mutex;

public:
    Conversation();
    ~Conversation();
    vector<Message> getConv() const;
    //! \brief démarre une conversation entre deux entités en paramètres.
    //! \param p un parking,
    //! \param v une voiture.
    void startConv(Parking p, Voiture v);
    void sendMessageVoiture (Voiture v);
    void sendMessageParking (Parking p);
    void manageConversation(Voiture v, Parking p);
    //! \brief stock la conversation, afin de laisser une trace.
    bool stockConv(const string& fileName);
    void testRegression();
};

#endif