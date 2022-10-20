#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <time.h>

using namespace std;

class Message
{

private:


    unsigned int messageNumber;
    // - Numéro du message dans la conversation.
    // - Le 1er message porte le numéro 0, et le numéro de chaque nouveau message
    // sera l'entier suivant (0, 1, 2, 3, etc.).


    clock_t date;
    // "Date-heure" courante du message

    float price;
    // Tarif horaire proposé dans le message

    string subject;

    // - Type du message : par exemple : "appel", "offre", "acceptation", "refus", "contre-offre"...

    // - L'idée est que la négociation devra être parfaitement normée, comme l'est un échange de messages
    // automatiques dans le cadre d'un protocol internet. A chaque type de message, le receveur doit savoir
    // exactement quels types de message il peut envoyer en réponse. Il faut avoir en tête qu'il y a une sorte
    // d'arbre des possibilités, par exemple : après un "appel" vient une "offre", puis soit un "acceptation",
    // soit un "refus", soit une "contre-offre"...





    string sender;

    // - Expéditeur du message

    // - De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking





    string recipient;

    // - Destinataire du message

    // - De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking







public:
    //! \brief constructeur par défaut du message
    Message();
    //! \brief 1er constructeur à paramètres du message
    //! \brief Utilisé pour créer le 1er message d'une conversation
    Message(string aSender, string aRecipient);
    //! \brief 2e constructeur à paramètres du message
    //! \brief Utilisé pour créer tout les messages qui ne sont pas
    //! \brief le 1er message d'une conversation
    Message(unsigned int eMessageNumber, float aPrice, string aSubject, string aSender, string aRecipient);
    //! \brief destructeur du message
    ~Message();
    //! \brief procédure de récupération du numéro du message
    const unsigned int& getMessageNumber() const;
    //! \brief procédure de récupération de l'objet du message
    const string& getSubject() const;
    //! \brief procédure de récupération de la date du message
    clock_t getDate() const;
    //! \brief procédure de récupération du tarif indiqué dans le message
    float getPrice() const;
    //! \brief procédure de récupération de l'expéditeur du message
    const string &getSender() const;
    //! \brief procédure de récupération du destinataire du message
    const string &getRecipient() const;

    void test_regresion();
};

#endif