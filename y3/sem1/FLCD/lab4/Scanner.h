#pragma once
#include <fstream>
#include <regex>
#include <atomic>
#include "SymbolTable.h"
#include "ProgramInternalForm.h"

class Scanner
{
private:
	std::vector<std::string> operators;
	std::vector<std::string> separators;
	std::vector<std::string> reservedWords;
	std::string filePath;
	SymbolTable symbolTable;
	ProgramInternalForm pif;

	std::string readFile();
	std::vector<Pair<std::string, Pair<int,int>>> createListOfProgramElems();
	std::vector<Pair<std::string, Pair<int,int>>> tokenize(const std::vector<std::string>& tokensToBe);

public:
	Scanner(const std::string& filePath);
	void scan();
	ProgramInternalForm getPif();
	SymbolTable getSymbolTable();
};

