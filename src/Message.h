#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <time.h>

using namespace std;

class Message
{

private:

    unsigned int messageNumber; // Numéro du message dans la conversation.
    // - Le 1er message porte le numéro 0, et le numéro de chaque nouveau message
    // sera l'entier suivant (0, 1, 2, 3, etc.).

    clock_t date; // "Date-heure" courante du message

    float price; // Tarif horaire proposé dans le message

    string subject;     // Type du message, les types utilisés étant :
    /*
        - "UNKNOWN SUBJECT" : type d'initilisation dans le constructeur

        - "INVALID_TYPE" : type d'initialisation dans managingConversation

        - "CALL" : type du 1er message d'une négociation

        - "NO_MORE_SPOTS" : indique à la voiture que le parking n'a plus
                            de place libre

        - "OFFER" : type du 1er message proposant un prix valide

        - "COUNTER_OFFER" : type d'un message proposant un prix en réponse à une offre

        - "LAST_OFFER" : indique que l'entité laisse une dernière chance
                         à l'autre entité de proposer un prix acceptable

        - "ACCEPT" : indique que l'entité accepte le prix proposé

        - "REJECT" : indique que l'une des 2 entités met fin à la négociation
                     car ces dernières n'ont pas réussi à se mettre d'accord sur le prix

        - "CONFIRM_ACCEPT" : indique au parking que ce dernier est celui
                             que la voiture a choisi, après que les 2 entités se
                             sont mises d'accord sur le prix

        - "RENOUNCE" : indique que la voiture a choisi un autre parking,
                       moins cher que celui auquel elle s'adresse, avec
                       qui elle s'était cependant mise d'accord sur le prix

        - "OK_TO_PARK" : indique que le parking confirme qu'il est prêt
                        à accueillir la voiture, après que les 2 entités se sont
                        mises d'accord sur le prix et que la voiture a indiqué
                        au parking que ce dernier est celui qu'elle a choisi

        - "ABORT" : indique que le parking met fin à la négociation,
                    après que les 2 entités se sont mises d'accord sur le prix mais
                    que la voiture a indiqué avoir choisi un autre parking

    */

    // Une négociation est parfaitement normée, comme l'est un échange de messages
    // automatiques dans le cadre d'un protocol internet. A chaque type de message, le receveur sait
    // exactement quels types de message il peut envoyer en réponse. Il y a un arbre des possibilités
    // bien précis (cf diagramme dans le dossier doc de ce projet).





    string sender;      // Expéditeur du message
    // De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking





    string recipient;       // Destinataire du message
    // De la forme "Utilisateur_" + id_utilisateur, ou "Parking_" + id_parking







public:

    //! \brief constructeur par défaut du message
    Message();

    //! \brief 1er constructeur à paramètres du message
    //! \brief Utilisé pour créer le 1er message d'une conversation
    //! \param aSender expéditeur du message
    //! \param aRecipient destinataire du message
    Message(string aSender, string aRecipient);

    //! \brief 2e constructeur à paramètres du message
    //! \brief Utilisé pour créer tout les messages qui ne sont pas
    //! \brief le 1er message d'une conversation
    //! \param aMessageNumber numéro du message
    //! \param aPrice prix proposé
    //! \param aSubject type du message
    //! \param aSender expéditeur du message
    //! \param aRecipient destinataire du message
    Message(unsigned int aMessageNumber, float aPrice, string aSubject,
            string aSender, string aRecipient);

    //! \brief Constructeur par copie
    //! \param aMessage message copié
    Message (const Message & aMessage);

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
    const string& getSender() const;

    //! \brief procédure de récupération du destinataire du message
    const string& getRecipient() const;

    //! \brief test de régression de la classe Message.
    void test_regresion();
};

#endif