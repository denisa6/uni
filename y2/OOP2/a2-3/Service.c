#include <string.h>
#include <stdlib.h>
#include "service.h"

bool check_if_valid_type(char type[]) {
    ///Function to check if the offer is valid
    ///\param destination - the name of the destination
    ///\param departure_date - the departure date
    ///\return - true if it is valid, false otherwise
    const char* Types[] = { "seaside", "mountain", "city break" };
    int index = 0;
    bool valid = false;
    while (index < sizeof(Types) / sizeof(const char*) && valid == false) {
        if (strcmp(type, Types[index]) == 0)
            valid = true;
        index++;
    }
    return valid;
}

bool check_if_after_given_date(char offer_date[], char given_date[]) {
    ///Function to check if an offer is departing after a given date
    ///\param offer_date - the departure date of the offer
    ///\param given_date - the date to compare with
    ///\return - true if the departure date is after the given date, false otherwise
    bool valid = false;
    char offer_day_string[3] = "", offer_month_string[3] = "", offer_year_string[5] = "", given_day_string[3] = "", given_month_string[3] = "", given_year_string[5] = "";
    offer_day_string[0] = offer_date[0];
    offer_day_string[1] = offer_date[1];
    offer_month_string[0] = offer_date[3];
    offer_month_string[1] = offer_date[4];
    offer_year_string[0] = offer_date[6];
    offer_year_string[1] = offer_date[7];
    offer_year_string[2] = offer_date[8];
    offer_year_string[3] = offer_date[9];

    given_day_string[0] = given_date[0];
    given_day_string[1] = given_date[1];
    given_month_string[0] = given_date[3];
    given_month_string[1] = given_date[4];
    given_year_string[0] = given_date[6];
    given_year_string[1] = given_date[7];
    given_year_string[2] = given_date[8];
    given_year_string[3] = given_date[9];

    int offer_day = atoi(offer_day_string), offer_month = atoi(offer_month_string), offer_year = atoi(offer_year_string);
    int given_day = atoi(given_day_string), given_month = atoi(given_month_string), given_year = atoi(given_year_string);

    if (offer_year > given_year)
        return true;
    else if (offer_year == given_year) {
        if (offer_month > given_month)
            return true;
        else if (offer_month == given_month) {
            if (offer_day > given_day)
                return true;
            else
                return false;
        }
    }
    return valid;
}

int add_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char type[], char destination[], char departure_date[], int price) {
    ///ADD functionality
    ///Service function to create the new element and pass it to be added to the list.
    /// \param offer_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param type - type of the offer ("seaside", "mountain" or "city break")
    /// \param destination - destination of the offer
    /// \param departure_date - departure date of the offer
    /// \param price - price of the offer
    /// \return - 1 if the offer already exists, 2 if the type is not valid, 0 if the offer was added successfully
    int index;
    for (index = 0; index < offer_list->dynamicArray.length; index++) {
        if (strcmp(getDestination(&offer_list->dynamicArray.data[index]), destination) == 0 && strcmp(getDepartureDate(&offer_list->dynamicArray.data[index]), departure_date) == 0) // check if we already have the country
            return 1;
    }
    if (check_if_valid_type(type) == false) // check if the type is valid
        return 2;
    Offer new_offer = createOffer(type, destination, departure_date, price); // create the element
    addUndoElement(undo_redo_repo, offer_list); // pass the current repo to the undo repo
    addOffer(offer_list, new_offer);
    return 0;
}

bool delete_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char destination[], char departure_date[]) {
    /// DELETE functionality
    /// Service function to identify and delete the required element given by the user.
    /// \param offer_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param destination - destination of the offer to be deleted\
    /// \param departure_date - departure date of the offer
    /// \return - false if the element does not exist, true if it exist and it was deleted
    int deleted_index = findByDestinationAndDepartureDate(offer_list, destination, departure_date); // find the index of the element to be deleted
    if (deleted_index == -1)
        return false;
    else {
        addUndoElement(undo_redo_repo, offer_list); // pass the current repo to the undo repo
        deleteOffer(offer_list, deleted_index);
        return true;
    }
}

int update_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char new_destination[], char type[], char old_destination[], char departure_date[], int price) {
    ///UPDATE functionality
    ///Service function to update the destination of a specific country.
    /// \param offer_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param new_destination - the new destination of the offer
    /// \param type - the type of the offer
    /// \param old_destination - the destination of the offer to be updated
    /// \param departure_date - the departure date of the offer
    /// \param price - the price of the offer
    /// \return - 2 if the offer is not valid, 1 if the offer to be updated does not exist, 0 if it exists and it was updated
    if (check_if_valid_type(type) == false) // check if the continent is valid
        return 2;
    int update_index = findByDestinationAndDepartureDate(offer_list, old_destination, departure_date); // find the index of the element to be updated
    if (update_index == -1)
        return 1;
    Offer updated_offer = createOffer(type, new_destination, departure_date, price); // create the new element
    addUndoElement(undo_redo_repo, offer_list); // pass the current repo to the undo repo
    updateOffer(offer_list, update_index, updated_offer);
    return 0;
}


int filter_offer(Repository* offer_list, const char filter_string[], const char given_date[], Offer valid_offers[]) {
    ///Filter functionality
    ///Function to filter by a given string and deaprture date to be after a given date
    /// \param offer_list - the repository in which the elements are stored
    /// \param filter_string - the string by which the types are filtered
    /// \param valid_offers - the array in which the valid offers will be stored
    /// \return - the number of elements from the valid_offers array
    int counter = 0;
    int index;
    if (filter_string[0] == '\0') // case for when the string is empty
        for (index = 0; index < offer_list->dynamicArray.length; index++) {
            strcpy(valid_offers[counter].type, offer_list->dynamicArray.data[index].type);
            strcpy(valid_offers[counter].destination, offer_list->dynamicArray.data[index].destination);
            strcpy(valid_offers[counter].departure_date, offer_list->dynamicArray.data[index].departure_date);
            valid_offers[counter].price = offer_list->dynamicArray.data[index].price; // copy everything in the array[counter]
            counter++; // increase the number of elements from the array
        }
    else {
        for (index = 0; index < offer_list->dynamicArray.length; index++) {
            if (strstr(offer_list->dynamicArray.data[index].type, filter_string) != NULL && check_if_after_given_date(offer_list->dynamicArray.data[index].departure_date, given_date) == true) { // if the string can be found in the name, copy in array[counter]
                strcpy(valid_offers[counter].type, offer_list->dynamicArray.data[index].type);
                strcpy(valid_offers[counter].destination, offer_list->dynamicArray.data[index].destination);
                strcpy(valid_offers[counter].departure_date, offer_list->dynamicArray.data[index].departure_date);
                valid_offers[counter].price = offer_list->dynamicArray.data[index].price;
                counter++; // increase the number of elements from the array
            }
        }
    }
    return counter;
}

int filter_sort_offer(Repository* offer_list, Offer valid_offers[], char destination_input[]) {
    ///Filter and sort functionality
    ///Function to find the offers on a given destination that are sorted by price
    /// \param offer_list - the repository in which the elements are stored
    /// \param valid_offers - the array of valid offers
    /// \param destination_input - the destination of the offer to filter by
    /// \return - -1 if the offer is not empty or valid, the number of elements from the valid_offers array otherwise
    int counter = 0;
    int index;
    if (destination_input[0] == '\0') { // case if the string input is empty
        for (index = 0; index < offer_list->dynamicArray.length; index++) {
            strcpy(valid_offers[counter].type, offer_list->dynamicArray.data[index].type);
            strcpy(valid_offers[counter].destination, offer_list->dynamicArray.data[index].destination);
            strcpy(valid_offers[counter].departure_date, offer_list->dynamicArray.data[index].departure_date);
            valid_offers[counter].price = offer_list->dynamicArray.data[index].price;
            counter++;
        }
    }
    else {
        for (index = 0; index < offer_list->dynamicArray.length; index++)
            if (strstr(offer_list->dynamicArray.data[index].destination, destination_input) != NULL) { // if the continent is the same, copy the element and increase the counter
                strcpy(valid_offers[counter].type, offer_list->dynamicArray.data[index].type);
                strcpy(valid_offers[counter].destination, offer_list->dynamicArray.data[index].destination);
                strcpy(valid_offers[counter].departure_date, offer_list->dynamicArray.data[index].departure_date);
                valid_offers[counter].price = offer_list->dynamicArray.data[index].price;
                counter++;
            }
    }
    // Bubble sort to sort the elements of the array in ascending order by price
    Offer temp; // temporary variable for swapping the elements
    for (int i = 0; i < counter - 1; i++)
        // Last i elements are already in place
        for (int j = 0; j < counter - i - 1; j++)
            if (valid_offers[j].price > valid_offers[j + 1].price) { // if the elements correspond, do the swapping
                temp = valid_offers[j];
                valid_offers[j] = valid_offers[j + 1];
                valid_offers[j + 1] = temp;
            }
    return counter;
}

int ServiceUndo(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    ///UNDO service function
    ///Function to undo the last operation done
    /// \param offer_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository
    /// \return - 1 if there are no more operations to be undone, 0 otherwise
    if (undo_redo_repo->length_undo == 0)
        return 1;
    addRedoElement(undo_redo_repo, offer_list); // add the current repo for the redo operation
    popLastUndo(undo_redo_repo, offer_list);
    return 0;
}

int ServiceRedo(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    ///REDO service function
    ///Function to redo the last operation done
    /// \param offer_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository
    /// \return - 1 if there are no more operations to be redone, 0 otherwise
    if (undo_redo_repo->length_redo == 0)
        return 1;
    addUndoElement(undo_redo_repo, offer_list); // add the current repo for the undo operation
    popLastRedo(undo_redo_repo, offer_list);
    return 0;
}