#include "Message.h"
#include <iostream>

using namespace std;

Message::Message (string aSender, string aRecipient) :
    messageNumber (0), date (clock ()/CLOCKS_PER_SEC), price (-1), subject ("CALL"),
    sender (aSender), recipient (aRecipient) {}

Message::Message (unsigned int eMessageNumber, float aPrice, string aSubject, string aSender, string aRecipient) :
    messageNumber (eMessageNumber), date (clock ()/CLOCKS_PER_SEC), price (aPrice), subject (aSubject),
    sender (aSender), recipient (aRecipient) {}

Message::Message () : messageNumber (0), date (clock ()/CLOCKS_PER_SEC), price (-21),
                      subject ("UNKNOWN SUBJECT"),
                      sender ("UNKNOWN SENDER"),
                      recipient ("UNKNOWN RECIPIENT") {}

Message::Message (const Message & aMessage) : messageNumber (aMessage.messageNumber),
                                              date (aMessage.date),
                                              price (aMessage.price),
                                              subject (aMessage.subject),
                                              sender (aMessage.sender),
                                              recipient (aMessage.recipient)
{
}

Message::~Message () {}

const unsigned int& Message::getMessageNumber() const {
    return messageNumber;
}

const string& Message::getSubject() const {
    return subject;
}
clock_t Message::getDate() const {
    return date;
}

float Message::getPrice() const {
    return price;
}

const string& Message::getSender() const {
    return sender;
}

const string& Message::getRecipient() const {
    return recipient;
}


void Message::test_regresion() {
    
}