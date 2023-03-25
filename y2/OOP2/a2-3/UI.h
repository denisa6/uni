#pragma once
#include "Service.h"

void option_2(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
void option_3(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
void option_4(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
void option_5(Repository* offer_list);
void option_6(Repository* offer_list);
void list_all_offers(Repository* offer_list);
void undo(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
void redo(Repository* offer_list, UndoRedoRepository* undo_redo_repo);
void print_menu();
void start();
