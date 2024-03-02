#include "FiniteAutomaton.h"
#include <fstream>
#include <iostream>

std::vector<std::string> splitString(const std::string& input, const std::string& delimiter) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;

	while ((end = input.find(delimiter, start)) != std::string::npos) {
		tokens.push_back(input.substr(start, end - start));
		start = end + delimiter.length();
	}
	tokens.push_back(input.substr(start));
	return tokens;
}

void FiniteAutomaton::readFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::string line;
	if (file.is_open()) {
		getline(file, line);
		this->states = splitString(line, this->separator);
		getline(file, this->initialState);
		getline(file, line);
		this->alphabet = splitString(line, this->separator);
		getline(file, line);
		this->finalStates = splitString(line, this->separator);
		while (getline(file, line)) {
			std::vector<std::string> transitionComponents = splitString(line, " ");
			if (std::find(this->states.begin(), this->states.end(), transitionComponents[0]) != this->states.end()
				&& std::find(this->states.begin(), this->states.end(), transitionComponents[2]) != this->states.end()
				&& std::find(this->alphabet.begin(), this->alphabet.end(), transitionComponents[1]) != this->alphabet.end()) {
				std::pair<std::string, std::string> transitionStates = std::pair<std::string, std::string>(transitionComponents[0], transitionComponents[1]);
				if (this->transitions.find(transitionStates) == this->transitions.end()) {
					std::set<std::string> transitionStatesSet;
					transitionStatesSet.insert(transitionComponents[2]);
					this->transitions[transitionStates] = transitionStatesSet;
				}
				else {
					this->transitions[transitionStates].insert(transitionComponents[2]);
				}
			}
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file";
	}
	this->isDeterministic = checkIfDeterministic();
}

bool FiniteAutomaton::checkIfDeterministic()
{
	for (const auto& it : this->transitions) {
		if (it.second.size() > 1) {
			return false;
		}
	}
	return true;
}

FiniteAutomaton::FiniteAutomaton(const std::string& filePath)
{
	this->readFromFile(filePath);
}

std::vector<std::string> FiniteAutomaton::getStates()
{
	return this->states;
}

std::string FiniteAutomaton::getInitialState()
{
	return this->initialState;
}

std::vector<std::string> FiniteAutomaton::getAlphabet()
{
	return this->alphabet;
}

std::vector<std::string> FiniteAutomaton::getFinalStates()
{
	return this->finalStates;
}

std::map<std::pair<std::string, std::string>, std::set<std::string>> FiniteAutomaton::getTransitions()
{
	return this->transitions;
}

std::string FiniteAutomaton::writeTransitions()
{
	std::string result = "Transitions: \n";
	for (const auto& entry : this->transitions) {
		result += "<" + entry.first.first + "," + entry.first.second + "> -> ";
		for (const auto& state : entry.second) {
			result += state + " ";
		}
		result += "\n";
	}
	return result;
}

bool FiniteAutomaton::acceptsSequence(const std::string& sequence) {
	if (!this->isDeterministic) {
		return false;
	}

	if (sequence.empty()) {
		return std::find(this->finalStates.begin(), this->finalStates.end(), this->initialState) != this->finalStates.end();
	}

	std::string currentState = this->initialState;

	for (char symbol : sequence) {
		std::string currentSymbol(1, symbol);
		std::pair<std::string, std::string> transition = std::make_pair(currentState, currentSymbol);

		if (this->transitions.find(transition) == this->transitions.end()) {
			return false;
		}
		else {
			currentState = *this->transitions[transition].begin();
		}
	}

	return std::find(this->finalStates.begin(), this->finalStates.end(), currentState) != this->finalStates.end();
}
