#pragma once
#include "HashTable.h"

class SymbolTable
{
private:
	int size;
	HashTable hashTable;

public:
	SymbolTable(int size);
	std::string findByPos(Pair<int,int> pos);
	HashTable getHashTable();
	int getSize();
	Pair<int,int> findPosOfTerm(std::string term);
	bool containsTerm(std::string term);
	bool add(std::string term);
	std::string toString();
};

