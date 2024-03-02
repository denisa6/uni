#include "SymbolTable.h"

SymbolTable::SymbolTable(int size) : size(size), hashTable(size)
{
}

std::string SymbolTable::findByPos(Pair pos)
{
	return this->hashTable.findByPos(pos);
}

HashTable SymbolTable::getHashTable()
{
	return this->hashTable;
}

int SymbolTable::getSize()
{
	return this->hashTable.getSize();
}

Pair SymbolTable::findPosOfTerm(std::string term)
{
	return this->hashTable.findPosOfTerm(term);
}

bool SymbolTable::containsTerm(std::string term)
{
	return this->hashTable.containsTerm(term);
}

bool SymbolTable::add(std::string term)
{
	return this->hashTable.add(term);
}
