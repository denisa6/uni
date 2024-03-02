#pragma once
#include <iostream>
#include <vector>
#include "Pair.h" 

class ProgramInternalForm
{
private:
	std::vector<Pair<std::string, Pair<int,int>>> tokenPositionPair;
	std::vector<int> types;

public:
	ProgramInternalForm();
	void add(Pair<std::string, Pair<int,int>> pair, int type);
	std::string toString();
};

