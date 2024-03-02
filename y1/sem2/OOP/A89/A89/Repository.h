#pragma once
#include "Tutorial.h"
#include <vector>

class Repository
{
protected:
	std::vector<Tutorial> tutorials;
	//std::vector<Tutorial> watch_list;

public:
	/*
		Default constructor.
	*/
	Repository() {}

	/*
		Adds a song to the repository.
		Input: s - Song.
		Output: the song is added to the repository.
	*/
	virtual void addTutorial(const Tutorial& t);

	/// <summary>
	/// deletes a tutorial from the repo
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="title"></param> the title of the tutorial
	virtual int deleteTutorial(const std::string& presenter, const std::string& title);

	/// <summary>
	/// updates the name of a tutoria;
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="old_title"></param> the title of the tutorial that we want to chamge
	/// <param name="new_title"></param> the new title of the tutorial
	virtual void updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title);

	/// <summary>
	/// updates the number of likes of a given tutorial, it increases it by one
	/// </summary>
	/// <param name="pos"></param> the position of the tutorial in the repo
	void updateLikes(int pos);

	/// <summary>
	/// finds the positon of a tutorial in repo
	/// </summary>
	/// <param name="presenter"></param> the name of the presenter of the tutorial
	/// <param name="title"></param> the title of the tutorial
	/// <returns></returns> the position of the tutorial in the repo
	int findTutorialPos(const std::string& presenter, const std::string& title);

	/*
		Finds a song, by artist and title.
		Input: artist, title - string
		Output: the song that was found, or an "empty" song (all fields empty and duration 0), if nothing was found.
	*/
	Tutorial findByPresenter(const std::string& presenter);

	std::vector<Tutorial> getTutorials() { return tutorials; }

	//virtual void addTutorialToPlaylist(const Tutorial& tutorial);

	///// <summary>
	///// Deletes a tutorial from the watch list
	///// </summary>
	///// <param name="pos"></param> the position of the tutorial in the watch list
	//virtual void deleteTutorialFromWatchList(int pos);

	///// <summary>
	///// Increases the number of likes of a tutorial by one
	///// </summary>
	///// <param name="pos"></param> the position of the tutorial in the watch list
	//virtual void addLike(int pos);

	//std::vector<Tutorial> getWatchList() const { return watch_list; }
};

//void test_repo();