#pragma once
#include "Controller.h"
#include <string>
#include <fstream>
using namespace std;


class HTML :public WatchList
{
private:

	string file;
public:
	HTML();
	HTML(const string& text_file);

	~HTML();

	string getFileName();

	void addTutorialToPlaylist(const Tutorial& tutorial) override;


	void deleteTutorialFromWatchList(int pos) override;


	void addLike(int pos) override;

	void save_file();

	void displayPlaylist() override;


};


