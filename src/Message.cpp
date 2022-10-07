#include "Message.h"
#include <iostream>

using namespace std;

Message::Message (float aPrice, string aTypeOfMessage, string aSubject) :
    date (clock ()), price (aPrice), typeOfMessage (aTypeOfMessage), subject (aSubject) {}

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