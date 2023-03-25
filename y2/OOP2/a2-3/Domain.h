#pragma once
typedef struct {
    char type[50];
    char destination[50];
    char departure_date[50];
    int price;
} Offer;

Offer createOffer(char type[], char destination[], char departure_date[], int price);
char* getType(Offer* o);
char* getDestination(Offer* o);
char* getDepartureDate(Offer* o);
int getPrice(Offer* o);
void toString(Offer o, char str[]);

