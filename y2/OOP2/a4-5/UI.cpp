#include "UI.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>


void UI::printMenu()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - Enter administrator mode\n";
	std::cout << "2 - Enter user mode\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

void UI::printUserMenu()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - See movies with given genre\n";
	std::cout << "2 - See watch list\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

void UI::printAdministratorMenu()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - Add a movie\n";
	std::cout << "2 - Remove a movie\n";
	std::cout << "3 - Update a movie\n";
	std::cout << "4 - See all the movies from the date base\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

void UI::printUpdateMenu()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - Update title\n";
	std::cout << "2 - Update genre\n";
	std::cout << "3 - Update trailer\n";
	std::cout << "4 - Update year\n";
	std::cout << "5 - Update number of likes\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

void UI::printViewingOptions()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - Next\n";
	std::cout << "2 - Add to movie list\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

int UI::readNumber()
{
	char string[50];
	int number = 0;

	std::cin >> string;
	for (int i = 0; i < strlen(string); i++)
		if (isdigit(string[i]) == 0)
			return -1;
		else
			number = number * 10 + string[i] - '0';

	return number;
}

void UI::printMovieListOptions()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "1 - Next\n";
	std::cout << "2 - Delete from movie list\n";
	std::cout << "0 - Exit\n";
	std::cout << "--------------------------------------------\n";
}

void UI::writeFile(std::string file, DynamicVector<Movie> movies, int size)
{
	std::ofstream g(file);
	for (int i = 0; i < size; i++)
	{
		g << movies[i].getTitle() << "\n";
		g << movies[i].getGenre() << "\n";
		g << movies[i].getTrailer() << "\n";
		g << movies[i].getYear() << "\n";
		g << movies[i].getNumberLikes() << "\n";
	}
	g.close();
}

void UI::readFile(std::string file)
{
	std::ifstream f(file);
	std::string title;
	std::string genre;
	std::string trailer;
	int year, numberOfLikes;

	while (getline(f, title))
	{
		getline(f, genre);
		getline(f, trailer);
		f >> year;
		f >> numberOfLikes;
		this->serv.add(title, genre, trailer, year, numberOfLikes);
		getline(f, genre);
	}
	f.close();
}

void UI::start()
{
	readFile("Movies.txt");
	while (1)
	{
		printMenu();
		std::cout << "Option: ";
		int option = readNumber();
		switch (option)
		{
		case 1:
			this->startAdministrator();
			break;
		case 2:
			this->startUser();
			break;
		case 0:
			//writeFile("Movies.txt", this->serv.getList(), this->serv.getSize());
			return;
		default:
			std::cout << "Option does not exist!\n";
		}
	}
}

int UI::startAdministrator()
{
	while (1)
	{
		printAdministratorMenu();
		std::cout << "Option: ";
		int option = readNumber();
		switch (option)
		{
		case 1:
			this->addMovieToDataBase();
			break;
		case 2:
			this->removeMovieFromDataBase();
			break;
		case 3:
			this->updateMovieFromDataBase();
			break;
		case 4:
			this->printMovieList(this->serv.getList(), this->serv.getSize());
			break;
		case 0:
			return 1;
		default:
			std::cout << "Option does not exist!\n";
		}
	}
	return 0;
}

int UI::startUser()
{
	while (1)
	{
		printUserMenu();
		std::cout << "Option: ";
		int option = readNumber();
		switch (option)
		{
		case 1:
			this->filterAfterGenre();
			break;
		case 2:
			this->iterateMovieList();
			break;
		case 0:
			return 1;
		default:
			std::cout << "Option does not exist!\n";
		}

	}
	return 0;
}

void UI::addMovieToDataBase()
{
	std::string title, genre, trailer, space;

	std::cout << "Movie title: ";
	std::getline(std::cin, space);
	std::getline(std::cin, title);
	std::cout << "Movie genre: ";
	std::getline(std::cin, genre);
	std::cout << "Movie trailer: ";
	std::getline(std::cin, trailer);
	std::cout << "Movie year: ";
	int year = readNumber();
	while (year <= 1800 or year >= 2024)
	{
		std::cout << "Year must be a number between 1800 and 2024!\n";
		std::cout << "Movie year: ";
		year = readNumber();
	}
	std::cout << "Movie number of likes: ";
	int numberOfLikes = readNumber();
	while (numberOfLikes < 0)
	{
		std::cout << "Movie number of likes: ";
		int numberOfLikes = readNumber();
		std::cout << "Number of likes must be a number higher or equal to 0!\n";
	}
	if (this->serv.add(title, genre, trailer, year, numberOfLikes) == 1)
		std::cout << "Movie was added successful!\n";
	else
		std::cout << "Movie could not be added!\n";
}

void UI::removeMovieFromDataBase()
{
	std::cout << "Movie title: ";
	std::string title;
	std::getline(std::cin, title);
	std::getline(std::cin, title);
	std::cout << "Movie year: ";
	int year = readNumber();
	while (year <= 1800 or year >= 2024)
	{
		std::cout << "Year must be a number between 1800 and 2024!\n";
		std::cout << "Movie year: ";
		year = readNumber();
	}
	if (this->serv.remove(title, year))
		std::cout << "Movie removed succesfully!\n";
	else
		std::cout << "Movie could not be removed!\n";
}

void UI::printMovieList(DynamicVector<Movie> movies, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Movie " << i + 1 << "\n";
		printMovie(movies[i]);
	}
}

void UI::updateMovieFromDataBase()
{
	std::string newS;
	int result;
	while (1)
	{
		printUpdateMenu();
		std::cout << "Option: ";
		int option = readNumber();
		if (option == 0)
			return;
		std::cout << "Movie title you want to update: ";
		std::string title;
		std::getline(std::cin, title);
		std::getline(std::cin, title);
		std::cout << "Movie year you want to update: ";
		int year = readNumber();
		while (year <= 1800 or year >= 2024)
		{
			std::cout << "Year must be a number between 1800 and 2024!\n";
			std::cout << "Movie year: ";
			year = readNumber();
		}
		switch (option)
		{
		case 1:
		{
			std::cout << "New title: ";
			std::getline(std::cin, newS);
			std::getline(std::cin, newS);
			result = this->serv.updateMovieString(title, year, newS, 1);
			break;
		}
		case 2:
		{
			std::cout << "New genre: ";
			std::getline(std::cin, newS);
			std::getline(std::cin, newS);
			result = this->serv.updateMovieString(title, year, newS, 2);
			break;
		}
		case 3:
		{
			std::cout << "New trailer: ";
			std::getline(std::cin, newS);
			std::getline(std::cin, newS);
			result = this->serv.updateMovieString(title, year, newS, 3);
			break;
		}
		case 4:
		{
			std::cout << "Movie year: ";
			int newYear = readNumber();
			while (newYear <= 1800 or newYear >= 2024)
			{
				std::cout << "Year must be a number between 1800 and 2024!\n";
				std::cout << "Movie new year: ";
				year = readNumber();
			}
			result = this->serv.updateMovieInteger(title, year, newYear, 1);
			break;
		}
		case 5:
		{
			std::cout << "Movie number of likes: ";
			int numberOfLikes = readNumber();
			while (numberOfLikes < 0)
			{
				std::cout << "Movie number of likes: ";
				numberOfLikes = readNumber();
				std::cout << "Number of likes must be a number higher or equal to 0!\n";
			}
			result = this->serv.updateMovieInteger(title, year, numberOfLikes, 2);
			break;
		}
		default:
			std::cout << "Option does not exist!\n";
		}
	}
	if (result)
		std::cout << "Update was succesfull!\n";
	else
		std::cout << "Update was not succesfull!\n";
}

void UI::printMovie(Movie movie)
{
	std::cout << "	Title: " << movie.getTitle() << "\n";
	std::cout << "	Genre: " << movie.getGenre() << "\n";
	std::cout << "	Trailer: " << movie.getTrailer() << "\n";
	std::cout << "	Year: " << movie.getYear() << "\n";
	std::cout << "	Number of likes: " << movie.getNumberLikes() << "\n";
}

void UI::filterAfterGenre()
{
	std::cout << "Genre: ";
	std::string genre;
	std::getline(std::cin, genre);
	std::getline(std::cin, genre);
	DynamicVector<Movie> filteredList = this->serv.filter(genre);
	int option = 1;
	int i = 0;
	while (filteredList.getSize() != 0)
	{
		printViewingOptions();
		printMovie(filteredList[i]);
		filteredList[i].play();
		option = readNumber();
		switch (option)
		{
		case 1:
			if (i == filteredList.getSize() - 1)
				i = 0;
			else
				i++;
			break;
		case 2:
			this->moviePlaylist.addMovie(filteredList[i]);
			i++;
			break;
		case 0:
			return;
		default:
			std::cout << "Option does not exist!\n";
		}
	}
}

void UI::iterateMovieList()
{
	int i = 0;
	int option = 1;
	char answer;
	while (this->moviePlaylist.getSize() != 0)
	{
		printMovieListOptions();
		DynamicVector<Movie> movies = this->moviePlaylist.getList();
		printMovie(movies[i]);
		option = readNumber();
		switch (option)
		{
		case 1:
			if (i == this->moviePlaylist.getSize() - 1)
				i = 0;
			else
				i++;
			break;
		case 2:
		{
			std::cout << "Did you like the movie? <y/n>\n";
			std::cin >> answer;
			std::string title = movies[i].getTitle();
			if (answer == 'y')
				this->serv.updateMovieInteger(title, movies[i].getYear(), movies[i].getNumberLikes() + 1, 2);
			this->moviePlaylist.remove(title, movies[i].getYear());
		}
		break;
		case 0:
			return;
		default:
			std::cout << "Option does not exist!\n";
		}
	}
}