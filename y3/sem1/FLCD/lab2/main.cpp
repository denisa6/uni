#include <iostream>
#include "SymbolTable.h"

int main() {
    SymbolTable symbolTable(5);
    std::cout << std::boolalpha;

    symbolTable.add("12");
    std::cout << symbolTable.containsTerm("12") << std::endl;
    Pair position = symbolTable.findPosOfTerm("12");
    std::cout << position.toString() << std::endl;

    symbolTable.add("1");
    std::cout << symbolTable.containsTerm("1") << std::endl;
    position = symbolTable.findPosOfTerm("1");
    std::cout << position.toString() << std::endl;

    symbolTable.add("a");
    std::cout << symbolTable.containsTerm("a") << std::endl;
    position = symbolTable.findPosOfTerm("a");
    std::cout << position.toString() << std::endl;

    std::cout << symbolTable.getHashTable().toString() << std::endl;

    return 0;
}