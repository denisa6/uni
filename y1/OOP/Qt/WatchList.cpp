#include "WatchList.h"


WatchList::WatchList()
{
	this->tutorials_watchList = std::vector<Tutorial>();
}

WatchList::~WatchList()
{
}

void WatchList::addTutorialToPlaylist(const Tutorial& tutorial)
{
	this->tutorials_watchList.push_back(tutorial);
}

void WatchList::deleteTutorialFromWatchList(int pos)
{
	std::vector<Tutorial>::iterator it;
	it = this->tutorials_watchList.begin() + pos;
	this->tutorials_watchList.erase(it);
}

void WatchList::addLike(int pos)
{
	std::vector<Tutorial> watch_list = this->getWatchList();
	Tutorial t = watch_list[pos];
	int i = this->findTutorialPosWatchList(t.getPresenter(), t.getTitle());
	this->updateLikesWatchList(i);
}

void WatchList::save_file()
{
}

int WatchList::findTutorialPosWatchList(const std::string& presenter, const std::string& title)
{
	int searched_index = -1;
	std::vector<Tutorial>::iterator it;
	it = find_if(this->tutorials_watchList.begin(), this->tutorials_watchList.end(), [&presenter, &title](Tutorial& t) {return t.getPresenter() == presenter && t.getTitle() == title; });
	if (it != this->tutorials_watchList.end())
	{
		searched_index = it - this->tutorials_watchList.begin();
	}
	return searched_index;
}

void WatchList::updateLikesWatchList(int pos)
{
	this->tutorials_watchList[pos].increaseLikes();
}



