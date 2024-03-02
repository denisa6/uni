#include "Redo.h"
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Redo* createRedoElem(char* operation, char* type, char* destination, char* departure_date, char* changed_destination, int price)
{
	Redo* e = (Redo*)malloc(sizeof(Redo));
	if (e == NULL)
		return NULL;

	e->operation = (char*)malloc(sizeof(char) * (strlen(operation)) + 1);
	if (e->operation != NULL)
		strcpy(e->operation, operation);

	e->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	if (e->type != NULL)
		strcpy(e->type, type);

	e->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	if (e->destination != NULL)
		strcpy(e->destination, destination);

	e->departure_date = (char*)malloc(sizeof(char) * (strlen(departure_date) + 1));
	if (e->departure_date != NULL)
		strcpy(e->departure_date, departure_date);

	e->changed_destination = (char*)malloc(sizeof(char) * (strlen(changed_destination) + 1));
	if (e->changed_destination != NULL)
		strcpy(e->changed_destination, changed_destination);

	e->price = price;

	return e;
}

void deleteRedoElem(Redo* e)
{
	if (e == NULL)
		return;

	
	free(e->type);
	free(e->destination);
	free(e->departure_date);
	free(e->changed_destination);
	free(e->operation);

	free(e);
}
