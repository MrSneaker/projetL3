#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <time.h>

using namespace std;


class Message
{
private:
    string subject; // Pas forcément nécessaire
    clock_t date;
    float price;
    string typeOfMessage;
    string sender; // expéditeur du message
    string recipient; // destinataire du message
public:
    //! \brief constructeur du message.
    Message();
    //! \brief constructeur à paramètre de Message.
    Message(string & aSubject, float aPrice, string & aTypeOfMessage);
    //! \brief destructeur du message.
    ~Message();
    //! \brief objet du message.
    string getSubject() const;
    //! \brief procédure de récupération de la date du message
    clock_t getDate() const;
    //! \brief procédure de récupération du tarif indiqué dans le message
    clock_t getPrice() const;
    //! \brief procédure de récupération du type du message
    string getTypeOfMessage() const;


    void test_regresion();
    
};


#endif