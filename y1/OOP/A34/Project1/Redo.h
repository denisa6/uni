#pragma once
typedef struct
{
	char* operation;
	char* type;
	char* destination;
	char* departure_date;
	char* changed_destination;
	int price;
} Redo;

/// <summary>
/// Creates an elem of type Redo
/// </summary>
/// <param name="operation"></param> the type of the operation that needs to be redone
/// <param name="type"></param> the type of the offer
/// <param name="destination"></param> the destination of the offer
/// <param name="departure_date"></param> the departure date of the offer
/// <param name="changed_destination"></param> the changed destination of the offer
/// <param name="price"></param> the price of the offer
/// <returns></returns> the redo elem created
Redo* createRedoElem(char* operation, char* type, char* destination, char* departure_date, char* changed_destination, int price);

/// <summary>
/// frees the memory from the redo elem
/// </summary>
/// <param name="e"></param> the elem that needs to be freed
void deleteRedoElem(Redo* e);