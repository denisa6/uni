#pragma once
#include "Controller.h"
#include <string>
#include <fstream>


class CSV :public WatchList

{
private:
	std::string file;
public:
	CSV(const std::string& text_file);
	~CSV();
	CSV();
	CSV(CSV& txt);
	std::string getFileName();


	void addTutorialToPlaylist(const Tutorial& tutorial) override;


	void deleteTutorialFromWatchList(int pos) override;


	void addLike(int pos) override;

	void save_file();

	void displayPlaylist() override;
};


