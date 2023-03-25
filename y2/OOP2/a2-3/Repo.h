#pragma once
#include <stdbool.h>
#include "Domain.h"
#include "DynamicArray.h"

typedef struct {
    DynamicArray dynamicArray;
}Repository;

Repository createRepository();
void addOffer(Repository* offer_list, Offer offer);
int findByType(Repository* offer_list, char type[]);
int findByDestinationAndDepartureDate(Repository* offer_list, char destination[], char departure_date[]);
void deleteOffer(Repository* offer_list, int delete_index);
void updateOffer(Repository* offer_list, int update_index, Offer updated_offer);
