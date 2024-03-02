#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Pair.h"

class FiniteAutomaton
{
private:
	const std::string separator = ";";
	bool isDeterministic;
	std::string initialState;
	std::vector<std::string> states;
	std::vector<std::string> alphabet;
	std::vector<std::string> finalStates;
	std::map<std::pair<std::string, std::string>, std::set<std::string>> transitions;

	void readFromFile(const std::string& filePath);

public:
	FiniteAutomaton(const std::string& filePath);
	std::vector<std::string> getStates();
	std::string getInitialState();
	std::vector<std::string> getAlphabet();
	std::vector<std::string> getFinalStates();
	std::map<std::pair<std::string, std::string>, std::set<std::string>> getTransitions();
	std::string writeTransitions();
	bool acceptsSequence(const std::string& sequence);
	bool checkIfDeterministic();
};

