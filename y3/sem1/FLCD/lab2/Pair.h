#pragma once
#include <string>

class Pair
{
private:
	int first;
	int second;

public:
	Pair(int first, int second);
	int getFirst();
	int getSecond();
	std::string toString();
};

