#include "Message.h"
#include <iostream>

using namespace std;

Message::Message (float aPrice, string aTypeOfMessage, string aSubject, string & aSender, string & aRecipient) :
    date (clock ()), price (aPrice), typeOfMessage (aTypeOfMessage), subject (aSubject), sender (aSender), recipient (aRecipient) {}

Message::~Message () {}

string Message::getSubject() const {
    return subject;
}
clock_t Message::getDate() const {
    return date;
}

clock_t Message::getPrice() const {
    return price;
}


void Message::test_regresion() {
    
}