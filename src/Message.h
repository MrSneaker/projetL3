#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <time.h>

using namespace std;


class Message
{



private:


    clock_t date;
    // "Date-heure" courante du message

    float price;
    // Tarif horaire proposé dans le message




    string typeOfMessage;

    // - Type du message : par exemple : "appel", "offre", "acceptation", "refus", "contre-offre"...

    // - L'idée est que la négociation devra être parfaitement normée, comme l'est un échange de messages
    // automatiques dans le cadre d'un protocol internet. A chaque type de message, le receveur doit savoir
    // exactement quels types de message il peut envoyer en réponse. Il faut avoir en tête qu'il y a une sorte
    // d'arbre des possibilités, par exemple : après un "appel" vient une "offre", puis soit un "acceptation", soit un "refus",
    // soit une "contre-offre"...




    string sender;

    // - Expéditeur du message

    // - De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking






    string recipient;

    // - Destinataire du message

    // - De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking



    string subject;

    // - Pas forcément nécessaire. Cette donnée pourrait nous permettre de stocker
    // des informations plus détaillées sur le message.

    // - Objet du message (comme l'objet d'un mail)





public:
    //! \brief constructeur de Message
    Message(float aPrice = 1, string aTypeOfMessage = "CALL", string aSubject = "Message sans objet");
    //! \brief destructeur du message
    ~Message();
    //! \brief procédure de récupération de l'objet du message
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