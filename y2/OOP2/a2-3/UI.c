#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"


void option_2(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    char type[50];
    char destination[50];
    char departure_date[50];
    char price_string[50];
    int price;
    printf("Enter the type, destination, departure date (formated like day/month/year) and price of the offer: \n");
    scanf_s("%s", &type, sizeof(type));
    scanf_s("%s", &destination, sizeof(destination));
    scanf_s("%s", &departure_date, sizeof(departure_date));
    scanf_s("%s", &price_string, sizeof(price_string));
    price = atoi(price_string);
    int added = add_offer(offer_list, undo_redo_repo, type, destination, departure_date, price);
    if (added == 1)
        printf("Offer already exists in the list.\n");
    else if (added == 2)
        printf("The type %s is not a valid one.\n", type);
    else
        printf("Offer successfully added.\n");
}

void option_3(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    char destination_delete[50], departure_date_deleted[50];
    printf("Enter the destination and the departure date of the offer you want to delete: \n");
    scanf_s(" %[^\n]", &destination_delete, sizeof(destination_delete));
    scanf_s("%s", &departure_date_deleted, sizeof(departure_date_deleted));
    bool deleted = delete_offer(offer_list, undo_redo_repo, destination_delete, departure_date_deleted);
    if (deleted == false)
        printf("The offer you wanted to delete is not in the list.\n");
    else
        printf("Offer successfully deleted.\n");
}

void option_4(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    char new_destination[50], type[50], old_destination[50], departure_date[50], price_string[50];
    int price;
    printf("Enter the new destinaton of the offer as well as the initial type, destination, departure date and price: \n");
    scanf_s(" %[^\n]", &new_destination, sizeof(new_destination));
    scanf_s(" %[^\n]", &type, sizeof(type));
    scanf_s("%s", &old_destination, sizeof(old_destination));
    scanf_s("%s", &departure_date, sizeof(departure_date));
    scanf_s("%s", &price_string, sizeof(price_string));
    price = atoi(price_string);
    int updated = update_offer(offer_list, undo_redo_repo, new_destination, type, old_destination, departure_date, price);
    if (updated == 1)
        printf("Offer with destination %s and departure date %s does not exist.\n", old_destination, departure_date);
    else if (updated == 2)
        printf("Invalid input for the type.\n");
    else
        printf("Offer successfully updated.\n");
}

void option_5(Repository* offer_list) {
    char filter_string[50];
    Offer* valid_offers;

    valid_offers = (Offer*)malloc(offer_list->dynamicArray.length * sizeof(Offer));
    printf("Enter the destination by which you want to filter: \n");
    getchar();
    fgets(filter_string, sizeof(filter_string), stdin);
    filter_string[strlen(filter_string) - 1] = '\0';
    int counter = filter_sort_offer(offer_list, valid_offers, filter_string);
    if (counter == 0)
        printf("There are no offers that have the given string in their names.\n");
    else {
        for (int index = 0; index < counter; index++)
            printf("type: %s, destination: %s, departure date: %s, price: %d \n", valid_offers[index].type, valid_offers[index].destination, valid_offers[index].departure_date, valid_offers[index].price);
    }
    free(valid_offers);
}

void option_6(Repository* offer_list) {
    char type_input[50];
    char departure_date_input[50];
    Offer* valid_offers;
    valid_offers = (Offer*)malloc(offer_list->dynamicArray.length * sizeof(Offer));
    printf("Enter the type by which you want to filter: \n");
    getchar();
    fgets(type_input, sizeof(type_input), stdin);
    type_input[strlen(type_input) - 1] = '\0';
    printf("Enter the departure date: \n");
    scanf_s("%s", &departure_date_input, sizeof(departure_date_input));
    int counter = filter_offer(offer_list, type_input, departure_date_input, valid_offers);
    if (counter == -1)
        printf("The type you gave is not a valid one. \n");
    else
        for (int index = 0; index < counter; index++)
            printf("%d. type: %s, destination: %s, departure date: %s, price: %d \n", index + 1, valid_offers[index].type, valid_offers[index].destination, valid_offers[index].departure_date, valid_offers[index].price);
    free(valid_offers);
}

void list_all_offers(Repository* offer_list) {
    int index;
    for (index = 0; index < arrayLength(&offer_list->dynamicArray); index++) {
        printf("%d. type: %s, destination: %s, departure date: %s, price: %d \n", index + 1, offer_list->dynamicArray.data[index].type, offer_list->dynamicArray.data[index].destination, offer_list->dynamicArray.data[index].departure_date, offer_list->dynamicArray.data[index].price);
    }
}

void undo(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    int valid = ServiceUndo(offer_list, undo_redo_repo);
    if (valid == 1)
        printf("There are no more operations that can be undone!\n");
    else
        printf("Successful undo!\n");
}

void redo(Repository* offer_list, UndoRedoRepository* undo_redo_repo) {
    int valid = ServiceRedo(offer_list, undo_redo_repo);
    if (valid == 1)
        printf("There are no more operations that can be redone!\n");
    else
        printf("Successful redo!\n");
}

void print_menu() {
    printf("MENU: \n"
        "0. EXIT. \n"
        "1. List all offers. \n"
        "2. Add an offer. \n"
        "3. Delete an offer. \n"
        "4. Update an offer. \n"
        "5. Display all offer whose destination contains a given string (sorted by price). \n"
        "6. Display all countries of a given type, having their departure after a given date. \n"
        "7. UNDO.\n"
        "8. REDO.\n");
}

void start() {
    printf("Welcome to the Tourism Agency App!\n");
    bool done = false;
    Repository offer_list = createRepository();
    UndoRedoRepository undo_redo_repo = createUndoRedoRepo(10);
    while (!done) {
        print_menu();
        printf("Choose an option from the menu: ");
        char option_string[5];
        char option0[] = "0";
        char option1[] = "1";
        char option2[] = "2";
        char option3[] = "3";
        char option4[] = "4";
        char option5[] = "5";
        char option6[] = "6";
        char option7[] = "7";
        char option8[] = "8";
        scanf_s("%s", &option_string, sizeof(option_string));
        if (strcmp(option_string, option0) == 0) {
            destroyDynamicArray(&offer_list.dynamicArray);
            destroyUndoRedoRepository(&undo_redo_repo);
            printf("Goodbye!");
            done = true;
        }
        else if (strcmp(option_string, option1) == 0) {
            list_all_offers(&offer_list);
        }
        else if (strcmp(option_string, option2) == 0) {
            option_2(&offer_list, &undo_redo_repo);
        }
        else if (strcmp(option_string, option3) == 0) {
            option_3(&offer_list, &undo_redo_repo);
        }
        else if (strcmp(option_string, option4) == 0) {
            option_4(&offer_list, &undo_redo_repo);
        }
        else if (strcmp(option_string, option5) == 0) {
            option_5(&offer_list);
        }
        else if (strcmp(option_string, option6) == 0) {
            option_6(&offer_list);
        }
        else if (strcmp(option_string, option7) == 0) {
            undo(&offer_list, &undo_redo_repo);
        }
        else if (strcmp(option_string, option8) == 0) {
            redo(&offer_list, &undo_redo_repo);
        }
        else
            printf("Bad input!\n");
    }
}