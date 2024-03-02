#pragma once
#include "HashTable.h"

class SymbolTable
{
private:
	int size;
	HashTable hashTable;

public:
	SymbolTable(int size);
	std::string findByPos(Pair pos);
	HashTable getHashTable();
	int getSize();
	Pair findPosOfTerm(std::string term);
	bool containsTerm(std::string term);
	bool add(std::string term);
};

