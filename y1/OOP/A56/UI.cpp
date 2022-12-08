#include "UI.h"
#include <string>

using namespace std;

void UI::printMenu()
{
	cout << endl;
	cout << "1 - Admin mode." << endl;
	cout << "2 - User mode." << endl;
	cout << "0 - Exit." << endl;
}

void UI::printRepositoryMenu()
{
	cout << "Possible commands: " << endl;
	cout << "\t 1 - Add tutorial." << endl;
	cout << "\t 2 - Display all." << endl;
	cout << "\t 3 - Remove tutorial." << endl;
	cout << "\t 4 - Update tutorial." << endl;
	cout << "\t 0 - Back." << endl;
}

void UI::printPlayListMenu()
{
	cout << "Possible commands: " << endl;
	cout << "\t 1 - Display based on presenter." << endl;
	cout << "\t 2 - Display watch list." << endl;
	cout << "\t 3 - Go through watch list." << endl;
	cout << "\t 0 - Back." << endl;
}

void UI::addTutorialToRepo()
{
	cout << "Enter the presenter: ";
	std::string presenter;
	getline(cin, presenter);
	cout << "Enter the title: ";
	std::string title;
	getline(cin, title);
	double minutes = 0, seconds = 0;
	cout << "Enter the duration: " << endl;
	cout << "\tMinutes: ";
	cin >> minutes;
	cin.ignore();
	cout << "\tSeconds: ";
	cin >> seconds;
	cin.ignore();
	cout << "Youtube link: ";
	std::string link;
	getline(cin, link);

	this->ctrl.addTutorialToRepository(presenter, title, minutes, seconds, link);
}

void UI::displayAllTutorialsRepo()
{
	DynamicVector<Tutorial> tutorials = this->ctrl.getRepo().getTutorials();
	if (tutorials.getSize() == 0)
	{
		cout << "There are no tutorials in the repository." << endl;
		return;
	}
	for (int i = 0; i < tutorials.getSize(); i++)
	{
		Tutorial t = tutorials[i];
		Duration d = t.getDuration();
		cout << t.getPresenter() << " - " << t.getTitle() << "; " << d.getMinutes() << ":" << d.getSeconds() << "; likes: " << t.getLikes() << endl;
	}
}

void UI::removeTutorialFromRepo()
{
	cout << "Enter the presenter: ";
	std::string presenter;
	getline(cin, presenter);
	cout << "Enter the title: ";
	std::string title;
	getline(cin, title);
	if (this->ctrl.deleteTutorialFromRepo(presenter, title) == -1)
		cout << "This tutorial does't exist" << endl;
	else
		this->ctrl.deleteTutorialFromRepo(presenter, title);
}

void UI::updateTutorialFromRepo()
{
	cout << "Enter the presenter: ";
	std::string presenter;
	getline(cin, presenter);
	cout << "Enter the title: ";
	std::string title;
	getline(cin, title);
	cout << "Enter the new title: ";
	std::string new_title;
	getline(cin, new_title);
	this->ctrl.updateTutorial(presenter, title, new_title);
}

void UI::addTutorialToWatchList()
{
	cout << "Enter the presenter: ";
	std::string presenter;
	getline(cin, presenter);
	cout << "Enter the title: ";
	std::string title;
	getline(cin, title);

	// search for the tutorial in the repository
	Tutorial t = this->ctrl.getRepo().findByPresenter(presenter);
	if (t.getPresenter() == "")
	{
		cout << "There are no songs with the given data in the repository. Nothing will be added to the playlist." << endl;
		return;
	}

	this->ctrl.addTutorialToPlaylist(t);
}

void UI::displayPresenterMenu()
{
	cout << "Enter the presenter: ";
	std::string presenter;
	getline(cin, presenter);
	this->displayTutorialsBasedOnPresenter(presenter);
}

void UI::displayTutorialsBasedOnPresenter(const std::string& presenter)
{
	
	DynamicVector<Tutorial> tutorials = this->ctrl.getRepo().getTutorials();

	for (int i = 0; i < tutorials.getSize(); i++)
	{
		Tutorial t = tutorials[i];
		Duration d = t.getDuration();
		if (t.getPresenter() == presenter)
		{
			cout << t.getPresenter() << " - " << t.getTitle() << "; " << d.getMinutes() << ":" << d.getSeconds() << "; likes: " << t.getLikes() << endl;
			t.play();
			this->finishedTutorial(t);
		}
	}
	cout << "Do you want to replay all? yes or no" << endl;
	std::string response;
	getline(cin, response);
	if (response == "yes")
		this->displayTutorialsBasedOnPresenter(presenter);
}

void UI::finishedTutorial(const Tutorial& t)
{
	cout << "Did you like the tutorial? yes or no" << endl;
	std::string response;
	getline(cin, response);
	if (response == "yes")
	{
		cout << "Do you want to add it to your watch list? yes or no" << endl;
		std::string response2;
		getline(cin, response2);
		if (response2 == "yes")
			this->ctrl.addTutorialToPlaylist(t);
	}
}

void UI::displayWatchList()
{
	DynamicVector<Tutorial> watch_list = this->ctrl.getWatchList();

	for (int i = 0; i < watch_list.getSize(); i++)
	{
		Tutorial t = watch_list[i];
		Duration d = t.getDuration();
		cout << t.getPresenter() << " - " << t.getTitle() << "; " << d.getMinutes() << ":" << d.getSeconds() << "; likes: " << t.getLikes() << endl;
	}
}

void UI::removeTutorialFromWatchList(int pos)
{
	cout << "Did you like the tutorial? yes or no" << endl;
	std::string response;
	getline(cin, response);
	if (response == "yes")
		this->ctrl.addLike(pos);
	this->ctrl.deleteTutorialFromWatchList(pos);
}

void UI::goThroughWatchList()
{
	DynamicVector<Tutorial> watch_list = this->ctrl.getWatchList();

	for (int i = 0; i < watch_list.getSize(); i++)
	{
		Tutorial t = watch_list[i];
		Duration d = t.getDuration();
		cout << t.getPresenter() << " - " << t.getTitle() << "; " << d.getMinutes() << ":" << d.getSeconds() << "; likes: " << t.getLikes() << endl;
		cout << "Do you want to play the tutorial? yes or no" << endl;
		std::string response;
		getline(cin, response);
		if (response == "yes")
		{
			t.play();
			this->removeTutorialFromWatchList(i);
		}
	}
}


void UI::run()
{
	while (true)
	{
		UI::printMenu();
		int command{ 0 };
		cout << "Input the command: ";
		cin >> command;
		cin.ignore();
		if (command == 0)
			break;

		// repository management
		if (command == 1)
		{
			while (true)
			{
				UI::printRepositoryMenu();
				int commandRepo{ 0 };
				cout << "Input the command: ";
				cin >> commandRepo;
				cin.ignore();
				if (commandRepo == 0)
					break;
				switch (commandRepo)
				{
				case 1:
					this->addTutorialToRepo();
					break;
				case 2:
					this->displayAllTutorialsRepo();
					break;
				case 3:
					this->removeTutorialFromRepo();
					break;
				case 4:
					this->updateTutorialFromRepo();
				}
			}
		}

		// playlist management
		if (command == 2)
		{
			while (true)
			{
				UI::printPlayListMenu();
				int commandWatchList{ 0 };
				cout << "Input the command: ";
				cin >> commandWatchList;
				cin.ignore();
				if (commandWatchList == 0)
					break;
				switch (commandWatchList)
				{
				case 1:
					this->displayPresenterMenu();
					break;
				case 2:
					this->displayWatchList();
					break;
				case 3:
					this->goThroughWatchList();
				}
			}
		}
	}
}