#include "Scanner.h"
#include "FiniteAutomaton.h"

void printToFile(const std::string& filePath, const std::string& content) {
	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << content;
		outFile.close();
	}
	else {
		std::cerr << "Error: Cannot open file " << filePath << std::endl;
	}
}

void run(const std::string& filePath) {
	Scanner scanner(filePath);
	scanner.scan();
	printToFile(filePath.substr(0, filePath.length() - 4) + "ST.txt", scanner.getSymbolTable().toString());
	printToFile(filePath.substr(0, filePath.length() - 4) + "PIF.txt", scanner.getPif().toString());
}

void runScanner() {
	run("Input_Output/p1.txt");
	run("Input_Output/p2.txt");
	run("Input_Output/p3.txt");
	run("Input_Output/p1err.txt");
}

void printMenu() {
	std::cout << "0. exit" << std::endl;
	std::cout << "1. print states" << std::endl;
	std::cout << "2. print alphabet" << std::endl;
	std::cout << "3. print final states" << std::endl;
	std::cout << "4. print transitions" << std::endl;
	std::cout << "5. print initial state" << std::endl;
	std::cout << "6. print is deterministic" << std::endl;
	std::cout << "7. check if sequence is accepted by DFA" << std::endl;
}

void optionsForDFA() {
	FiniteAutomaton finiteAutomaton("Input_Output/FA.in");
	std::cout << "FA read from file." << std::endl;
	printMenu();
	std::cout << "Choose: ";
	int option;
	std::cin >> option;
	while (option) {
		switch (option) {
		case 0:
			break;
		case 1:
			std::cout << "Final states: " << std::endl;
			for (const auto& state : finiteAutomaton.getStates()) {
				std::cout << state << std::endl;
			}
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Alphabet: " << std::endl;
			for (const auto& symbol : finiteAutomaton.getAlphabet()) {
				std::cout << symbol << std::endl;
			}
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Final states: " << std::endl;
			for (const auto& finalState : finiteAutomaton.getFinalStates()) {
				std::cout << finalState << std::endl;
			}
			std::cout << std::endl;
			break;
		case 4:
			std::cout << finiteAutomaton.writeTransitions() << std::endl;
			break;
		case 5:
			std::cout << "Initial state: " << std::endl;
			std::cout << finiteAutomaton.getInitialState() << std::endl;
			std::cout << std::endl;
			break;
		case 6:
			std::cout << "Is deterministic? " << std::boolalpha << finiteAutomaton.checkIfDeterministic() << std::endl;
			break;
		case 7: {
			std::cout << "Your sequence: " << std::endl;
			std::string sequence;
			std::cin.ignore();  // Clearing buffer
			std::getline(std::cin, sequence);

 			if (finiteAutomaton.acceptsSequence(sequence))
				std::cout << "Sequence is valid" << std::endl;
			else
				std::cout << "Invalid sequence" << std::endl;
		}
			  break;
		default:
			std::cout << "Invalid command!" << std::endl;
			break;

		}
		std::cout << std::endl;
		printMenu();
		std::cout << "Your option: ";
		std::cin >> option;
	}
}

int main() {
	int option;
	std::cout << "0. Scanner\n1. FA\nYour option: ";
	std::cin >> option;
	if (option) {
		optionsForDFA();
	}
	else {
		runScanner();
	}
	return 0;
}
