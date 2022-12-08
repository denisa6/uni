#pragma once

#include <vector>
#include "Tutorial.h"


#include<iostream>
#include<iterator> 
#include<vector> 

class WatchList

{
protected:
	std::vector<Tutorial> tutorials_watchList;

public:
	WatchList();
	~WatchList();
	virtual void addTutorialToPlaylist(const Tutorial& tutorial);

	virtual void deleteTutorialFromWatchList(int pos);

	virtual void addLike(int pos);

	std::vector<Tutorial> getWatchList() const { return tutorials_watchList; }

	virtual void save_file();

	int findTutorialPosWatchList(const std::string& presenter, const std::string& title);

	void updateLikesWatchList(int pos);

	virtual void displayPlaylist() = 0;






};


