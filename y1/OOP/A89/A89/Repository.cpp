#include "Repository.h"
#include <string>
#include <assert.h>
#include"Exceptions.h"
# include< iostream>
using namespace std;


using namespace std;

void Repository::addTutorial(const Tutorial& t)
{
	for (auto& tutorial : this->tutorials)
		if (tutorial.getTitle() == t.getTitle())
			throw RepositoryException();
	if (t.getDuration().getMinutes() == 0 && t.getDuration().getSeconds() == 0)
		throw LengthIsZero();
	this->tutorials.push_back(t);
}

int Repository::deleteTutorial(const std::string& presenter, const std::string& title)
{
	bool ok = false;
	int pos = this->findTutorialPos(presenter, title);
	if (pos != -1)
	{

		vector<Tutorial>::iterator it;
		it = this->tutorials.begin() + pos;
		this->tutorials.erase(it);
		ok = true;
	}
	else
		if (ok == false)
			throw RepositoryException();
	return 1;
}

void Repository::updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title)
{
	bool ok = false;
	int pos = this->findTutorialPos(presenter, old_title);
	if (pos != -1)
	{
		this->tutorials[pos].setTitle(new_title);
		ok = true;
	}

	if (!ok)
		throw RepositoryException();
}

void Repository::updateLikes(int pos)
{


	this->tutorials[pos].increaseLikes();
}

int Repository::findTutorialPos(const std::string& presenter, const std::string& title)
{
	int searched_index = -1;
	vector<Tutorial>::iterator it;
	it = find_if(this->tutorials.begin(), this->tutorials.end(), [&presenter, &title](Tutorial& t) {return t.getPresenter() == presenter && t.getTitle() == title; });
	if (it != this->tutorials.end())
	{
		searched_index = it - this->tutorials.begin();
	}
	return searched_index;
}

Tutorial Repository::findByPresenter(const std::string& presenter)
{
	for (auto i : this->tutorials)
	{
		Tutorial t = i;
		if (t.getPresenter() == presenter)
			return t;
	}

	return Tutorial{};
}