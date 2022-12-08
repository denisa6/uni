#pragma once
#include <string>

using namespace std;

template<typename T>
class Comparator {
public:
	virtual bool compare(const T& elem1, const T& elem2) = 0;
};

template<typename T>
class ComparatorAscendingByTitle : public Comparator<string> {
public:
	bool compare(const std::string& s1, const std::string& s2) override {
		if (s1.compare(s2) < 0) {
			return true;
		}
		return false;
	};
};

template<typename T>
class ComparatorDescendingByMinutes : public Comparator<int> {
public:
	bool compare(const int& y1, const int& y2) override {
		if (y1 > y2) {
			return true;
		}
		return false;
	};
};

