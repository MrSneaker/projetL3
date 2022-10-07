#include "Message.h"
#include <iostream>

using namespace std;

Message::Message () : date (clock ()) {}

Message::Message (string & aSubject, float aPrice, string & aTypeOfMessage) :
    subject (aSubject), date (clock ()), price (aPrice), typeOfMessage (aTypeOfMessage) {}

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

string Message::getTypeOfMessage() const {
    return typeOfMessage;
}


void Message::test_regresion() {
    
}