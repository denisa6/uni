#include "Pair.h"

Pair::Pair(int first, int second)
{
	this->first = first;
	this->second = second;
}

int Pair::getFirst()
{
	return this->first;
}

int Pair::getSecond()
{
	return this->second;
}

std::string Pair::toString()
{
	return "Pair{first=" + std::to_string(this->first) + ", second=" + std::to_string(this->second) + "}";
}
