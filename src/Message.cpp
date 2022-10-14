#include "Message.h"
#include <iostream>

using namespace std;

Message::Message (string aSender, string aRecipient) :
    date (clock ()), price (-1), subject ("CALL"),
    sender (aSender), recipient (aRecipient) {}

Message::Message (float aPrice, string aSubject, string aSender, string aRecipient) :
    date (clock ()), price (aPrice), subject (aSubject),
    sender (aSender), recipient (aRecipient) {}

Message::Message () : date (clock ()), price (-21),
                      subject ("UNKNOWN SUBJECT"),
                      sender ("UNKNOWN SENDER"),
                      recipient ("UNKNOWN RECIPIENT") {}

Message::~Message () {}

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