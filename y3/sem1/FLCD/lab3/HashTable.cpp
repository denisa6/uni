#include "HashTable.h"
#include <sstream>


int HashTable::hash(std::string key)
{
	int sum_chars = 0;
	for (char c : key) {
		sum_chars += int(c);
	}
	return sum_chars % size;
}

HashTable::HashTable(int size) : size(size), table(size)
{
	for (int i = 0; i < size; i++) {
		table[i] = std::vector<std::string>();
	}
}

std::string HashTable::findByPos(Pair<int,int> pos)
{
	if (this->table.size() <= pos.getFirst() || pos.getSecond() >= table[pos.getFirst()].size()) {
		throw std::exception("invalid position");
	}
	return table[pos.getFirst()][pos.getSecond()];
}

int HashTable::getSize()
{
	return size;
}

Pair<int,int> HashTable::findPosOfTerm(std::string term)
{
	int pos = hash(term);
	if (!table[pos].empty()) {
		std::vector<std::string>& elems = table[pos];
		for (int i = 0; i < elems.size(); i++) {
			if (elems[i] == term) {
				return Pair<int,int>(pos, i);
			}
		}
	}
	return Pair<int,int>(-1, -1);
}

bool HashTable::containsTerm(std::string term)
{
	return findPosOfTerm(term).getFirst() != -1;
}

bool HashTable::add(std::string term)
{
	if (containsTerm(term)) {
		return false;
	}
	int pos = hash(term);
	std::vector<std::string>& elems = table[pos];
	elems.push_back(term);
	return true;
}

std::string HashTable::toString()
{
	std::stringstream computedString;
	for (int i = 0; i < table.size(); i++) {
		if (!table[i].empty()) {
			computedString << i << " - ";
			for (const std::string& item : table[i]) {
				computedString << "[" << item << "]";
			}
			computedString << "\n";
		}
	}
	return computedString.str();
}
