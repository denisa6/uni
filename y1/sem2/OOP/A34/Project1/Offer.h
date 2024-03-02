#pragma once

typedef struct
{
	char* type;
	char* destination;
	char* departure_date;
	int price;
} Offer;

Offer* createOffer(char* type, char* destination, char* departure_date, int price);
void deleteOffer(Offer* o); // the memory is freed
void updateOffer(Offer* o, char* new_destination);
char* getType(Offer* o);
char* getDestination(Offer* o);
char* getDepartureDate(Offer* o);
int getPrice(Offer* o);
void toString(Offer* o, char str[]);

