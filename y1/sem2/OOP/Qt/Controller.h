#pragma once
#include "Repository.h"
#include"WatchList.h"
#include <vector>


class Controller
{
protected:
	Repository* repo;
	WatchList* watch_list;

public:
	Controller(Repository* r, WatchList* w) : repo(r), watch_list(w) {}

	~Controller();

	Repository* getRepo() const { return repo; }

	WatchList* getWatchList() const { return watch_list; }

	/// <summary>
	/// verifies whether a tutorial already exists in the database
	/// </summary>
	/// <param name="presenter"></param> the presenter of the tutorial that needs to be checked
	/// <param name="title"></param> the title of the tutorial that needs to be checked
	/// <returns></returns> 1 if the tutorial is valid, 0 otherwise
	int verifyTutorialValidity(const std::string& presenter, const std::string& title);

	/// <summary>
	/// Adds a tutorial to the tutorial list in repo
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="title"></param> the title of the tutorial
	/// <param name="minutes"></param> the number of minutes of the tutorial
	/// <param name="seconds"></param> the number of seconds of the tutorial
	/// <param name="source"></param> the link of the tutorial
	void addTutorialToRepository(const std::string& presenter, const std::string& title, double minutes, double seconds, const std::string& source);

	/// <summary>
	/// Deletes a tutorial from the tutorial list in repo
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="title"></param> the title of the tutorial
	int deleteTutorialFromRepo(const std::string& presenter, const std::string& title);

	/// <summary>
	/// Updates the title of the tutorial
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="old_title"></param> the title of the tutorial that we want to change
	/// <param name="new_title"></param> the new title of the tutorial
	void updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title);

	/*
		Adds a given tutorial to the current watch list.
		Input: tutorial - Tutorial, the tutorial must belong to the repository.
		Output: the tutorial is added to the playlist.
	*/
	void addTutorialToPlaylistC(const Tutorial& tutorial);

	/// <summary>
	/// Deletes a tutorial from the watch list
	/// </summary>
	/// <param name="pos"></param> the position of the tutorial in the watch list
	void deleteTutorialFromWatchListC(int pos);

	/// <summary>
	/// Increases the number of likes of a tutorial by one
	/// </summary>
	/// <param name="pos"></param> the position of the tutorial in the watch list
	void addLikeC(int pos);

};

//void test_ctrl();





