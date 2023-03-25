#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "Tests.h"

//DOMAIN TESTS
void testDomain() {
    //Create an offer
    Offer o1 = createOffer("seaside", "Gold Coast", "15/06/2025", 100);
    assert(strcmp(o1.type, "seaside") == 0);
    assert(strcmp(o1.destination, "Gold Coast") == 0);
    assert(strcmp(o1.departure_date, "15/06/2025") == 0);
    assert(o1.price == 100);
    //Create another offer
    Offer o2 = createOffer("city break", "Kosovo", "26/09/2023", 100);
    assert(strcmp(o1.type, o2.type) != 0);
    assert(strcmp(o2.destination, "Africa") != 0);
    assert(o2.price != 200);
    //Test the getters
    assert(strcmp(getType(&o1), "seaside") == 0);
    assert(strcmp(getDestination(&o2), "Kosovo") == 0);
    assert(strcmp(getDepartureDate(&o2), "26/09/2023") == 0);
    assert(getPrice(&o1) == 100);
}

//DYNAMIC ARRAY TESTS
void testDynamicArray() {
    //Test create array
    DynamicArray da = createDynamicArray(2);
    assert(da.length == 0);
    assert(da.capacity == 2);
    Offer o1 = createOffer("seaside", "Gold Coast", "15/06/2025", 100);
    //Add an element
    addElement(&da, o1);
    assert(da.length == 1);
    Offer o2 = createOffer("city break", "Amsterdam", "19/02/2026", 100);
    //Add another element
    addElement(&da, o2);
    assert(da.length == 2);
    Offer o3 = createOffer("mountain", "Oslo", "30/03/2023", 100);
    //Add element to test the resize
    addElement(&da, o3);
    assert(da.length == 3);
    assert(da.capacity == 4);
    //Delete an element
    deleteElement(&da, 2);
    assert(da.length == 2);
    assert(da.capacity == 4);
    Offer update = createOffer("city break", "Brazil", "19/02/2026", 100);
    //Update an element
    updateElement(&da, 1, update);
    assert(strcmp(da.data[1].destination, "Brazil") == 0);
    assert(da.data[1].price == 100);
    assert(arrayCapacity(&da) == 4);
    assert(arrayLength(&da) == 2);
    //Destroy the array
    destroyDynamicArray(&da);
}

//REPOSITORY TESTS
void testRepository() {
    //Create repository
    Repository repo = createRepository();
    assert(repo.dynamicArray.length == 10);
    assert(repo.dynamicArray.capacity == 10);
    Offer o1 = createOffer("seaside", "Gold Coast", "15/06/2025", 100);
    //Add a country
    addOffer(&repo, o1);
    assert(repo.dynamicArray.length == 11);
    assert(repo.dynamicArray.capacity == 20);
    Offer update = createOffer("seaside", "Canada", "15/06/2025", 100);
    //Update a country
    updateOffer(&repo, 10, update);
    assert(strcmp(repo.dynamicArray.data[10].destination, "Canada") == 0);
    assert(strcmp(repo.dynamicArray.data[10].type, "seaside") == 0);
    assert(repo.dynamicArray.data[10].price == 100);
    Offer o2 = createOffer("mountain", "Apache", "26/01/2027", 100);
    //Add another country
    addOffer(&repo, o2);
    assert(repo.dynamicArray.length == 12);
    //Delete a country
    deleteOffer(&repo, findByDestinationAndDepartureDate(&repo, "Apache", "26/01/2027"));
    assert(repo.dynamicArray.length == 11);
    //Destroy the repository
    destroyDynamicArray(&repo.dynamicArray);
}

//Undo Redo Repository tests
void testUndoRedoRepository() {
    //Create the undo redo repository
    UndoRedoRepository undo_redo = createUndoRedoRepo(1);
    assert(undo_redo.length_undo == 0);
    assert(undo_redo.length_redo == 0);
    assert(undo_redo.capacity_undo == 1);
    assert(undo_redo.capacity_redo == 1);
    Repository repo = createRepository();
    //Add an element to the undo array
    addUndoElement(&undo_redo, &repo);
    assert(undo_redo.length_undo == 1);
    Offer o1 = createOffer("mountain", "Apache", "26/01/2027", 100);
    addOffer(&repo, o1);
    //Add an element to the redo array
    addRedoElement(&undo_redo, &repo);
    assert(undo_redo.length_redo == 1);
    //test the resize of undo
    addUndoElement(&undo_redo, &repo);
    assert(undo_redo.length_undo == 2);
    assert(undo_redo.capacity_undo == 2);
    //test the resize of redo
    addRedoElement(&undo_redo, &repo);
    assert(undo_redo.length_redo == 2);
    assert(undo_redo.capacity_redo == 2);
    //Pop the last element of the undo array
    popLastUndo(&undo_redo, &repo);
    assert(undo_redo.length_undo == 1);
    //Pop the last element of the redo array
    popLastRedo(&undo_redo, &repo);
    assert(undo_redo.length_redo == 1);
    //Destroy the arrays
    destroyDynamicArray(&repo.dynamicArray);
    free(undo_redo.undo);
    free(undo_redo.redo);
}

void testService() {
    UndoRedoRepository undo_redo = createUndoRedoRepo(10);
    Repository repo = createRepository();
    //check if a continent is valid
    bool valid = check_if_valid_type("seaside");
    assert(valid == true);
    valid = check_if_valid_type("sea");
    assert(valid == false);
    //test the undo redo functions
    int undone = ServiceUndo(&repo, &undo_redo);
    int redone = ServiceRedo(&repo, &undo_redo);
    assert(undone == 1);
    assert(redone == 1);
    // add an already existing offer
    int added = add_offer(&repo, &undo_redo, "seaside", "Constanta", "12/05/2023", 250);
    assert(added == 1);
    // add an offer with an invalid type
    added = add_offer(&repo, &undo_redo, "seas", "Croatia", "13/05/2023", 250);
    assert(added == 2);
    // add a valid offer
    added = add_offer(&repo, &undo_redo, "city break", "Antalia", "04/09/2029", 100);
    assert(added == 0);
    //delete a non-existing offer
    bool deleted = delete_offer(&repo, &undo_redo, "America", "01/01/2021");
    assert(deleted == false);
    //delete an offer
    deleted = delete_offer(&repo, &undo_redo, "Antalia", "04/09/2029");
    assert(deleted == true);
    //undo
    undone = ServiceUndo(&repo, &undo_redo);
    assert(undone == 0);
    //redo
    redone = ServiceRedo(&repo, &undo_redo);
    assert(redone == 0);
    //undo
    ServiceUndo(&repo, &undo_redo);
    //update a non existing offer
    int updated = update_offer(&repo, &undo_redo, "USA", "city break", "Montana", "06/06/2026", 100);
    assert(updated == 1);
    //update an offer
    updated = update_offer(&repo, &undo_redo, "UK", "seaside", "Constanta", "12/05/2023", 250);
    assert(updated == 0);
    updated = update_offer(&repo, &undo_redo, "Ireland", "seaside", "UK", "12/05/2023", 250);
    assert(updated == 0);
    added = add_offer(&repo, &undo_redo, "mountain", "Scotland", "12/06/2023", 1000);
    assert(added == 0);
    //filter by empty string the names
    char filter_string1[] = "\0";
    Offer* valid_offers = (Offer*)malloc(repo.dynamicArray.capacity * sizeof(Offer));
    int filter = filter_offer(&repo, filter_string1, "00/00/0000", valid_offers);
    assert(filter == repo.dynamicArray.length);
    free(valid_offers);
    //filter so that nothing corresponds
    valid_offers = (Offer*)malloc(repo.dynamicArray.capacity * sizeof(Offer));
    filter = filter_offer(&repo, "z", "00/00/0000", valid_offers);
    assert(filter == 0);
    free(valid_offers);
    //filter and sort by empty string
    valid_offers = (Offer*)malloc(repo.dynamicArray.capacity * sizeof(Offer));
    int filter_sort = filter_sort_offer(&repo, valid_offers, filter_string1);
    assert(filter_sort == repo.dynamicArray.length);
    assert(valid_offers[0].price <= valid_offers[1].price);
    free(valid_offers);
}


void testAll() {
    testDomain();
    testDynamicArray();
    testRepository();
    testUndoRedoRepository();
    testService();
}