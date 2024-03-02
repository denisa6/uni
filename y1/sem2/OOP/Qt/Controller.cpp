#include "Controller.h"
#include "Controller.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <assert.h>
using namespace std;



int Controller::verifyTutorialValidity(const std::string& presenter, const std::string& title)
{
	vector<Tutorial> tutorials = this->getRepo()->getTutorials();
	for (auto i : tutorials)
	{
		Tutorial t = i;
		if (t.getPresenter() == presenter && t.getTitle() == title)
			return 0;
	}
	return 1;
}

void Controller::addTutorialToRepository(const std::string& presenter, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Tutorial t{ presenter, title, Duration{minutes, seconds}, source };
	this->repo->addTutorial(t);
}

int Controller::deleteTutorialFromRepo(const std::string& presenter, const std::string& title)
{
	return this->repo->deleteTutorial(presenter, title);
}

void Controller::updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title)
{
	this->repo->updateTutorial(presenter, old_title, new_title);
}

// playlist = watchlist
void Controller::addTutorialToPlaylistC(const Tutorial& tutorial)
{
	this->watch_list->addTutorialToPlaylist(tutorial);
}

void Controller::deleteTutorialFromWatchListC(int pos)
{
	this->watch_list->deleteTutorialFromWatchList(pos);
}

void Controller::addLikeC(int pos)
{
	this->watch_list->addLike(pos);
}

Controller::~Controller()
{
}

