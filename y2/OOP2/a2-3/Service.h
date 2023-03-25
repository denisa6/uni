#pragma once
#include <stdbool.h>
#include "Repo.h"
#include "UndoRedoRepo.h"

bool check_if_valid_type(char type[]);
int add_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char type[], char destination[], char departure_date[], int price);
bool delete_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char destination[], char departure_date[]);
int update_offer(Repository* offer_list, UndoRedoRepository* undo_redo_repo, char new_destination[], char type[], char old_destination[], char departure_date[], int price);
int filter_offer(Repository* offer_list, const char filter_string[], const char given_date[], Offer valid_offers[]);
int filter_sort_offer(Repository* offer_list, Offer valid_offers[], char destination_input[]);
int ServiceUndo(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
int ServiceRedo(Repository* offer_list, UndoRedoRepository* undo_redo_repo);

