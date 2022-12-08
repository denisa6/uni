#pragma once
#include "Controller.h"
#include <string>
#include <fstream>
using namespace std;

class CSV :public WatchList

{
private:
	string file;
public:
	CSV(const string& text_file);
	~CSV();
	CSV();
	CSV(CSV& txt);
	string getFileName();


	void addTutorialToPlaylist(const Tutorial& tutorial) override;


	void deleteTutorialFromWatchList(int pos) override;


	void addLike(int pos) override;

	void save_file();

	void displayPlaylist() override;
};

