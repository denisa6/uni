#include "ProgramInternalForm.h"

ProgramInternalForm::ProgramInternalForm()
{
}

void ProgramInternalForm::add(Pair<std::string, Pair<int,int>> pair, int type)
{
	this->tokenPositionPair.push_back(pair);
	this->types.push_back(type);
}

std::string ProgramInternalForm::toString()
{
	std::string result;
	for (int i = 0; i < tokenPositionPair.size(); i++) {
		result += tokenPositionPair[i].getFirst() + " - " + tokenPositionPair[i].getSecond().toString() + " -> " + std::to_string(types[i]) + "\n";
	}
	return result;
}
