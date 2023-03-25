#pragma once
#include "Domain.h"

typedef struct {
    Offer* data;
    int capacity;
    int length;
}DynamicArray;

DynamicArray createDynamicArray(int capacity);
void destroyDynamicArray(DynamicArray* array);
void addElement(DynamicArray* array, Offer element);
void deleteElement(DynamicArray* array, int delete_index);
void updateElement(DynamicArray* array, int update_index, Offer update_element);
//void resizeDynamicArray(DynamicArray * array);
int arrayCapacity(DynamicArray* array);
int arrayLength(DynamicArray* array);
