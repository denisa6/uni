#include <string.h>
#include "Repo.h"


void initialiseRepo(Repository* offer_list) {
    /// Function to initialise the repository with 10 entries
    /// \param offer_list - the repository in which the data is stored

    Offer offer1 = createOffer("seaside", "Constanta", "12/05/2023", 250);
    Offer offer2 = createOffer("seaside", "Florida", "04/05/2024", 375);
    Offer offer3 = createOffer("mountain", "Alps", "13/12/2025", 100);
    Offer offer4 = createOffer("city break", "New York", "21/07/2023", 359);
    Offer offer5 = createOffer("seaside", "Rhode Island", "25/05/2025", 400);
    Offer offer6 = createOffer("city break", "Los Angeles", "26/10/2023", 500);
    Offer offer7 = createOffer("mountain", "Brasov", "31/01/2024", 150);
    Offer offer8 = createOffer("city break", "Amsterdam", "08/08/2023", 275);
    Offer offer9 = createOffer("city break", "Rome", "30/11/2023", 300);
    Offer offer10 = createOffer("mountain", "Austria", "27/02/2026", 168);

    addOffer(offer_list, offer1);
    addOffer(offer_list, offer2);
    addOffer(offer_list, offer3);
    addOffer(offer_list, offer4);
    addOffer(offer_list, offer5);
    addOffer(offer_list, offer6);
    addOffer(offer_list, offer7);
    addOffer(offer_list, offer8);
    addOffer(offer_list, offer9);
    addOffer(offer_list, offer10);
}

Repository createRepository() {
    ///Function to create a repository
    /// \return - the new repository
    Repository offer_list;
    DynamicArray array = createDynamicArray(10); // create the dynamic array with initial capacity of 10
    offer_list.dynamicArray = array;
    initialiseRepo(&offer_list);
    return offer_list;
}

void addOffer(Repository* offer_list, Offer offer) {
    ///Function to add an offer to the repository
    /// \param offer_list - the repository
    /// \param offer - the element to be added
    addElement(&offer_list->dynamicArray, offer);
}

int findByType(Repository* offer_list, char type[]) {
    ///Function to find an element's index based on its name
    /// \param offer_list - the repository
    /// \param type - the type of the offer to be found
    /// \return - the index of the searched element
    int searched_index = -1;
    int index = 0;
    while (index < offer_list->dynamicArray.length && searched_index == -1) { // repeat the search while there are still elements and the element that we look for is not found
        if (strcmp(getType(&offer_list->dynamicArray.data[index]), type) == 0) {
            searched_index = index;
        }
        index++;
    }
    return searched_index;
}

int findByDestinationAndDepartureDate(Repository* offer_list, char destination[], char departure_date[]) {
    ///Function to find an element's index based on its destination and departure date
    /// \param offer_list - the repository
    /// \param destination - the destination of the offer
    /// \param departure_date - the departure date of the offer
    /// \return - the index of the searched element
    int searched_index = -1;
    int index = 0;
    while (index < offer_list->dynamicArray.length && searched_index == -1) { // repeat the search while there are still elements and the element that we look for is not found
        if (strcmp(getDestination(&offer_list->dynamicArray.data[index]), destination) == 0 && strcmp(getDepartureDate(&offer_list->dynamicArray.data[index]), departure_date) == 0) {
        searched_index = index;
        }
        index++;
    }
    return searched_index;
}

void deleteOffer(Repository* offer_list, int delete_index) {
    ///Function to delete an element based on its index
    ///\param offer_list - the repository
    ///\param delete_index - the index of the element to be deleted
    deleteElement(&offer_list->dynamicArray, delete_index);
}

void updateOffer(Repository* offer_list, int update_index, Offer updated_offer) {
    ///Function to update an element based on its index with the characteristics of another element
    ///\param offer_list - the repository
    ///\param delete_index - the index of the element to be updated
    ///\param updated_offer - the element with the new characteristics
    updateElement(&offer_list->dynamicArray, update_index, updated_offer);
}
