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
    // thread de voiture et parking, permettant le lancement indépendant de la conversation de chaque côté.
    thread voiture;
    thread parking;

    // vecteur de message, représentant la conversation.
    vector<Message> conv;

    // booléen permettant de savoir si la conversation est fini ou non.
    bool convOK;

    // exception mutuelle permettant aux threads de ne pas accéder aux données sensibles au même instant.
    mutex conv_mutex;

public:
    //! \brief Constucteur par défaut de Conversation.
    Conversation();

    //! \brief Destructeur de Conversation.
    ~Conversation();

    //! \brief Renvoie le vecteur de Message conv.
    //! \return un vecteur de Message.
    vector<Message> getConv() const;

    //! \brief Démarre une conversation entre deux entités en paramètres.
    //! \param p un parking,
    //! \param v une voiture.
    //! \return un booléen : true si la conversation s'est déroulée sans erreur, false sinon.
    bool manageConv(Parking p, Voiture v);

    void manageConfirm(Parking p, Voiture v,int indPrOK);

    //! \brief Fait appel à manageConversation dans Voiture pour écrire un message approprié à l'état de la conversation.
    //! \param v une voiture.
    void sendMessageVoiture(Voiture v);

    void sendConfirmationV(Voiture v, int indPrOK);

    void sendConfirmationP(Parking p);

    //! \brief Fait appel à manageConversation dans Parking pour écrire un message approprié à l'état de la conversation.
    //! \param p un parking.
    void sendMessageParking(Parking p);

    //! \brief Met à jour les données membres lastNbAgreements,
    //! \brief nbAgreement et profit d'un parking.
    //! \param p le parking qu'on met à jour
    void updateStateCarParkAfterConv (Parking & p);

    //! \brief Stocke la conversation, afin de laisser une trace.
    bool stockConv(const string &fileName, unsigned int nbConv);

    //! \brief Test de régression de la classe Conversation.
    void testRegression();
};

#endif