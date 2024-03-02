#include "Controller.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

void Controller::addTutorialToRepository(const std::string& presenter, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Tutorial t{ presenter, title, Duration{minutes, seconds}, source };
	this->repo.addTutorial(t);
}

int Controller::deleteTutorialFromRepo(const std::string& presenter, const std::string& title)
{
	return this->repo.deleteTutorial(presenter, title);
}

void Controller::updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title)
{
	this->repo.updateTutorial(presenter, old_title, new_title);
}

// playlist = watchlist
void Controller::addTutorialToPlaylist(const Tutorial& tutorial)
{
	this->watch_list.add(tutorial);
}

void Controller::deleteTutorialFromWatchList(int pos)
{
	this->watch_list.remove(pos);
}

void Controller::addLike(int pos)
{
	DynamicVector<Tutorial> watch_list = this->getWatchList();
	Tutorial t = watch_list[pos];
	int i = this->repo.findTutorialPos(t.getPresenter(), t.getTitle());
	this->repo.updateLikes(i);
}
