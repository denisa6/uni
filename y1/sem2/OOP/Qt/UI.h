#pragma once
#include "Controller.h"

class UI
{
private:
	Controller ctrl;

public:
	UI(const Controller& c) : ctrl(c) {}

	void run();

private:
	static void printMenu();
	static void printRepositoryMenu();
	static void printPlayListMenu();

	void addTutorialToRepo();
	void displayAllTutorialsRepo();
	void removeTutorialFromRepo();
	void updateTutorialFromRepo();

	void addTutorialToWatchList();
	void displayPresenterMenu();
	void displayTutorialsBasedOnPresenter(const std::string& presenter);
	void finishedTutorial(const Tutorial& t);
	void displayWatchList();
	void removeTutorialFromWatchList(int pos);
	void goThroughWatchList();
	void CSVfile();
	void display_csv_watchilist();
	//void addAllSongsByArtistToPlaylist();
};

