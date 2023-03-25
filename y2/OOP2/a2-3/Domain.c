#include <stdio.h>
#include <string.h>
#include "Domain.h"

Offer createOffer(char type[], char destination[], char departure_date[], int price) {
    ///Function to create an element of type Offer
    /// \param type - the type of the offer
    /// \param destination - the destination of the offer
    /// \param departure_date - the departure date of the offer
    /// \param price - the price of the offer
    /// \return - the new element of type Offer with the given characteristics
    Offer o;
    strcpy(o.type, type);
    strcpy(o.destination, destination);
    strcpy(o.departure_date, departure_date);
    o.price = price;
    return o;
}

char* getType(Offer* o) {
    /// Getter for the type attribute
    /// \param o - the offer
    /// \return - the type of the offer
    return o->type;
}

char* getDestination(Offer* o) {
    /// Getter for the destination attribute
    /// \param o - the offer
    /// \return - the destination of the offer
    return o->destination;
}

char* getDepartureDate(Offer* o) {
    /// Getter for the departure date attribute
    /// \param o - the offer
    /// \return - the departure date
    return o->departure_date;
}

int getPrice(Offer* o) {
    /// Getter for the price attribute
    /// \param o - the offer
    /// \return - the price
    return o->price;
}

void toString(Offer o, char str[]) {
    ///Method to transform the element into a string
    sprintf(str, "Offer of type %s, destination %s, departure date %s, and price %d.", o.type, o.destination, o.departure_date, o.price);
}