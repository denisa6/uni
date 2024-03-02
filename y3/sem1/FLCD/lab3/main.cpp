#include "Scanner.h"

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

int main() {
	run("Input_Output/p1.txt");
	run("Input_Output/p2.txt");
	run("Input_Output/p3.txt");
	run("Input_Output/p1err.txt");

	return 0;
}