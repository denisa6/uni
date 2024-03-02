#pragma once
#include <vector>
#include "Pair.h"

class HashTable
{
private:
	int size;
	std::vector<std::vector<std::string>> table;
	int hash(std::string key);

public:
	HashTable(int size);
	std::string findByPos(Pair pos);
	int getSize();
	Pair findPosOfTerm(std::string term);
	bool containsTerm(std::string term);
	bool add(std::string term);
	std::string toString();
};

