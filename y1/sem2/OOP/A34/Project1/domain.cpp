#define _CRT_SECURE_NO_WARNINGS
#include "Offer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Offer* createOffer(char* type, char* destination, char* departure_date, int price)
{
	Offer* o = (Offer*)malloc(sizeof(Offer));
	if (o == NULL)
		return NULL;
	
	o->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	if (o->type != NULL)
		strcpy(o->type, type);
	o->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	if (o->destination != NULL)
		strcpy(o->destination, destination);
	o->departure_date = (char*)malloc(sizeof(char) * (strlen(departure_date) + 1));
	if (o->departure_date != NULL)
		strcpy(o->departure_date, departure_date);

	o->price = price;
	return o;
}

void deleteOffer(Offer* o)
{
	if (o == NULL)
		return;

	// free the memory which was allocated for the component fields
	free(o->type);
	free(o->destination);
	free(o->departure_date);

	// free the memory which was allocated for the offer structure
	free(o);
}

void updateOffer(Offer* o, char* new_destination)
{
	strcpy(o->destination, new_destination);
}

char* getType(Offer* o)
{
	if (o == NULL)
		return NULL;
	return o->type;
}

char* getDestination(Offer* o)
{
	if (o == NULL)
		return NULL;
	return o->destination;
}

char* getDepartureDate(Offer* o)
{
	if (o == NULL)
		return NULL;
	return o->departure_date;
}

int getPrice(Offer* o)
{
	if (o == NULL)
		return -1;
	return o->price;
}

void toString(Offer* o, char str[])
{
	if (o == NULL)
		return;
	sprintf(str, "type: %s, destination: %s, date: %s, price: %d", o->type, o->destination, o->departure_date, o->price);
}