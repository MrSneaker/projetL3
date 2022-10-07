#include "Message.h"
#include <iostream>

using namespace std;

Message::Message () : date (clock ()) {}

Message::Message (string & aSubject, float aPrice, string & aSender, string & aRecipient ) :
    subject (aSubject), date (clock ()), price (aPrice), sender (aSender), recipient (aRecipient) {}

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