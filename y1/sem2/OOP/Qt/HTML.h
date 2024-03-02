#pragma once
#include "Controller.h"
#include <string>
#include <fstream>



class HTML :public WatchList
{
private:

	std::string file;
public:
	HTML();
	HTML(const std::string& text_file);

	~HTML();

	std::string getFileName();

	void addTutorialToPlaylist(const Tutorial& tutorial) override;


	void deleteTutorialFromWatchList(int pos) override;


	void addLike(int pos) override;

	void save_file();

	void displayPlaylist() override;


};



