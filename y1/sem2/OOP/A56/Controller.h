#pragma once
#include "Repository.h"
#include "PlayList.h"

class Controller
{
private:
	Repository repo;
	// add playlist: std::vector
	DynamicVector<Tutorial> watch_list;

public:
	Controller(const Repository& r) : repo(r) {}

	Repository getRepo() const { return repo; }
	DynamicVector<Tutorial> getWatchList() const { return watch_list; }

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
	void addTutorialToPlaylist(const Tutorial& tutorial);
	
	/// <summary>
	/// Deletes a tutorial from the watch list
	/// </summary>
	/// <param name="pos"></param> the position of the tutorial in the watch list
	void deleteTutorialFromWatchList(int pos);
	
	/// <summary>
	/// Increases the number of likes of a tutorial by one
	/// </summary>
	/// <param name="pos"></param> the position of the tutorial in the watch list
	void addLike(int pos);

};


