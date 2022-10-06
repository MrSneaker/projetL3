#ifndef __CONVERSATION_H__
#define __CONVERSATION_H__

#include <vector>
#include <string>
#include "Message.h"

class Conversation
{
private:
    vector<pair<Message,Message>> conv;
    string stockConvP;
    string stockConvV;
    
public:
    Conversation();
    ~Conversation();

    //! \brief stock la conversation, afin de laisser une trace et permettre au conversants de connaître leur actions passé.
    void stockConv();
};


#endif