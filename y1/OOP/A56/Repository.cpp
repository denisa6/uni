#include "Repository.h"
#include <string>

using namespace std;

void Repository::addTutorial(const Tutorial& t)
{
	this->tutorials.add(t);
}

int Repository::deleteTutorial(const std::string& presenter, const std::string& title)
{
	int pos = this->findTutorialPos(presenter, title);
	if (pos != -1)
		this->tutorials.remove(pos);
	else
		return -1;
}

void Repository::updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title)
{
	int pos = this->findTutorialPos(presenter, old_title);
	if (pos != -1)
		this->tutorials[pos].setTitle(new_title);
}

void Repository::updateLikes(int pos)
{
	this->tutorials[pos].increaseLikes();
}

int Repository::findTutorialPos(const std::string& presenter, const std::string& title)
{
	for (int i = 0; i < this->tutorials.getSize(); i++)
	{
		Tutorial t = tutorials[i];
		if (t.getPresenter() == presenter && t.getTitle() == title)
			return i;
	}
	return -1;
}

Tutorial Repository::findByPresenter(const std::string& presenter)
{
	for (int i = 0; i < this->tutorials.getSize(); i++)
	{
		Tutorial t = tutorials[i];
		if (t.getPresenter() == presenter)
			return t;
	}

	return Tutorial{};
}