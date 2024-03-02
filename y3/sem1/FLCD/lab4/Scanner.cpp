#include "Scanner.h"
#include "FiniteAutomaton.h"

Scanner::Scanner(const std::string& filePath) : filePath(filePath), symbolTable(100)
{
    operators = { "+", "-", "*", "/", "%", "<=", ">=", "==", "!=", "<", ">", "=", "&&", "||", "++", "+="};
    separators = { "{", "}", "(", ")", "[", "]", "<", ">", ":", ";", ".", " ", ",", "\t", "\n", "'", "\""};
    reservedWords = { "DEF", "INT", "STR", "CHAR", "IF", "ELSE", "READ", "PRINT", "DO", "WHILE", "FOR", "ARR", "CONST", "LEN", "RET", "ELIF", "GET_ELEM"};
}

std::string Scanner::readFile()
{
    std::string fileContent;
    std::ifstream file(this->filePath);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            fileContent += line + "\n";
        }
        file.close();
    }
    // Remove tab characters
    fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), '\t'), fileContent.end());
    return fileContent;
}

std::vector<Pair<std::string, Pair<int,int>>> Scanner::createListOfProgramElems()
{
    try {
        std::string content = this->readFile();
        std::string separatorsString = "";
        for (const auto& separator : separators) {
            separatorsString += separator;
        }
        std::vector<std::string> tokens;
        size_t current = 0, previous = 0;
        //get token substring
        while ((current = content.find_first_of(separatorsString, previous)) != std::string::npos) {
            if (current != previous) {
                tokens.push_back(content.substr(previous, current - previous));
            }
            std::string separator = content.substr(current, 1);
            tokens.push_back(separator);  // Add the separator itself as a token
            previous = current + 1;
        }
        if (previous < content.length()) {
            tokens.push_back(content.substr(previous, current - previous));
        }

        return tokenize(tokens);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<Pair<std::string, Pair<int,int>>> Scanner::tokenize(const std::vector<std::string>& tokensToBe)
{
    std::vector<Pair<std::string, Pair<int,int>>> resultedTokens;
    bool isStringConstant = false;
    bool isCharConstant = false;
    std::string createdString;
    int numberLine = 1;
    int numberColumn = 1;

    for (const std::string& t : tokensToBe) {
        switch (t[0]) {
        case '"':
            if (isStringConstant) {
                createdString += t;
                resultedTokens.emplace_back(Pair<std::string, Pair<int,int>>(createdString, Pair<int,int>(numberLine, numberColumn)));
                createdString.clear();
            }
            else {
                createdString += t;
            }
            isStringConstant = !isStringConstant;
            break;
        case '\'':
            if (isCharConstant) {
                createdString += t;
                resultedTokens.emplace_back(Pair<std::string, Pair<int,int>>(createdString, Pair<int,int>(numberLine, numberColumn)));
                createdString.clear();
            }
            else {
                createdString += t;
            }
            isCharConstant = !isCharConstant;
            std::cout << createdString << std::endl;
            break;
        case '\n':
            numberLine++;
            numberColumn = 1;
            break;
        default:
            if (isStringConstant) {
                createdString += t;
            }
            else if (isCharConstant) {
                createdString += t;
            }
            else if (t != " ") {
                resultedTokens.emplace_back(Pair<std::string, Pair<int,int>>(t, Pair<int,int>(numberLine, numberColumn)));
                numberColumn++;
            }
        }
    }
    return resultedTokens;
}

/*
0 - constants
1 - identifiers
2 - reserved words
3 - operators
4 - separators
*/
void Scanner::scan()
{
    std::vector<Pair<std::string, Pair<int,int>>> tokens = createListOfProgramElems();
    std::atomic<bool> lexicalErrorExists(false);
    if (tokens.empty()) {
        return;
    }
    for (const auto& t : tokens) {
        std::string token = t.getFirst();
        if (std::find(reservedWords.begin(), reservedWords.end(), token) != reservedWords.end()) {
            pif.add(Pair<std::string, Pair<int,int>>(token, Pair<int,int>(-1, -1)), 2);
        }
        else if (std::find(operators.begin(), operators.end(), token) != operators.end()) {
            pif.add(Pair<std::string, Pair<int, int>>(token, Pair<int,int>(-1, -1)), 3);
        }
        else if (std::find(separators.begin(), separators.end(), token) != separators.end()) {
            pif.add(Pair<std::string, Pair<int, int>>(token, Pair<int,int>(-1, -1)), 4);
        }
        //else if (std::regex_match(token, std::regex("^0|[-+]?[1-9][0-9]*|'[1-9]'|'[a-zA-Z]'|\"[0-9]*[a-zA-Z ]*\"$"))) {
        else if (FiniteAutomaton("Input_Output/FAconstants.txt").acceptsSequence(token) || std::regex_match(token, std::regex("^'[1-9]'|'[a-zA-Z]'|\"[0-9]*[a-zA-Z ]*\"$"))) {
            symbolTable.add(token);
            pif.add(Pair<std::string, Pair<int, int>>(token, symbolTable.findPosOfTerm(token)), 0);
        }
        //else if (std::regex_match(token, std::regex("^([a-zA-Z]|_)[a-zA-Z_0-9]*$"))) {
        else if (FiniteAutomaton("Input_Output/FAidentifiers.txt").acceptsSequence(token)) {
            symbolTable.add(token);
            pif.add(Pair<std::string, Pair<int, int>>(token, symbolTable.findPosOfTerm(token)), 1);
        }
        else {
            Pair<int,int> pairLineColumn = t.getSecond();
            std::cerr << "Error at line: " << pairLineColumn.getFirst() << " and column: " << pairLineColumn.getSecond() << ", invalid token: " << t.getFirst() << std::endl;
            lexicalErrorExists = true;
        }
    }
    if (!lexicalErrorExists) {
        std::cout << "Program is lexically correct!" << std::endl;
    }
}

ProgramInternalForm Scanner::getPif()
{
    return this->pif;
}

SymbolTable Scanner::getSymbolTable()
{
    return this->symbolTable;
}
