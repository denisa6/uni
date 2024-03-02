#pragma once
#include "Offer.h"

typedef struct
{
	Offer* offers[100];
	int length;
	int final_lenght;
} OfferRepo;

/// <summary>
/// Creates an OfferRepo.
/// </summary>
OfferRepo* createRepo();

/// <summary>
/// Destroys a given offer repository. The memory is freed.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// </summary>
void destroyRepo(OfferRepo* v);

/// <summary>
/// Finds the offers that contain the given destination string.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "res">Pointer to the OfferRepo that will contain all the offers we are looking for.</param>
/// <param name = "destination">A string, the destination to search for.</param>
/// <returns>res - Pointer to the final OfferRepo.</returns>
OfferRepo* findDestination(OfferRepo* v, OfferRepo* res, char destination[]);

OfferRepo* findTypeAndDate(OfferRepo* v, OfferRepo* res, char type[], int day, int month, int year);

/*
	Adds an offer to the repository of offers.
	Input:	- v - pointer to the OfferRepo
			- o - offer
	Output: 1 - if the offer was sucessfully added
			0 - if the offer could not be added
*/
int add(OfferRepo* v, Offer* o);

/// <summary>
/// Gets the lenght of the array of offers <=> the # of offers.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// </summary>
int getLength(OfferRepo* v);

/*
	Returns the offer on the given position in the offers vector.
	Input:	v - the offer repository;
			pos - integer, the position;
	Output: the offer on the given potision, or an "empty" offer.
*/
Offer* getOfferOnPos(OfferRepo* v, int pos);

/// <summary>
/// Finds the position of the offer that contain the given destination and departure date.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "destination">A string, the destination to search for.</param>
/// <param name = "departure_date">A string, the departure date to search for.</param>
/// <returns> i - The position of the offer; -1 - if there is no such offer.</returns>
int findOfferPos(OfferRepo* v, char* destination, char* departure_date);

/// <summary>
/// Erases the offer on position pos.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "pos">An int, the position of the offer we want to erase.</param>
void erase(OfferRepo* v, int pos);

/// <summary>
/// Updates the destination of an offer.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "pos">An int, the position of the offer.</param>
/// <param name = "new_destination">A string, the new destination of the offer.</param>
void update(OfferRepo* v, int pos, char* new_destination);

/// <summary>
/// Checks if a given destination is already used.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "destination">A string, the destination to check.</param>
/// <returns> 1 - If it is used; 0 - otherwise.</returns>
int checkIfDestinationExists(OfferRepo* v, char destination[]);

/// <summary>
/// Checks if a given departure date is already used.
/// </summary>
/// <param name = "v">Pointer to the OfferRepo.</param>
/// <param name = "departure_date">A string, the date to check.</param>
/// <returns> 1 - If it is used; 0 - otherwise.</returns>
int checkIfDepartureDateExists(OfferRepo* v, char departure_date[]);

void testsOfferRepo();
