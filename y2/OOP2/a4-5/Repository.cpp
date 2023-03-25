#include "Repository.h"

using namespace std;

void Repository::addMovie(const Movie& movie)
{
	this->movies.add(movie);
}

Movie Repository::findByTitleAndYear(const std::string title, const int year)
{
	for (int i = 0; i < this->movies.getSize(); i++)
	{
		Movie movie = movies[i];
		if (movie.getTitle() == title && movie.getYear() == year)
			return movie;
	}

	return Movie{};
}

void Repository::updateMovieString(Movie& movie, void (Movie::* function)(std::string), std::string value)
{
	for (int i = 0; i < this->movies.getSize(); i++)
		if (movies[i] == movie)
			(movies[i].*function)(value);
}

void Repository::updateMovieInteger(Movie& movie, void(Movie::* function)(int), int value)
{
	for (int i = 0; i < this->movies.getSize(); i++)
		if (movies[i] == movie)
			(movies[i].*function)(value);
}

void Repository::removeMovie(const Movie& movie)
{
	int i = 0;
	bool found = false;
	while (i < this->movies.getSize() and found == false)
	{
		if (movies[i] == movie)
		{
			found = true;
			movies[i] = movies[this->movies.getSize() - 1];
			movie.~Movie();
			this->movies.setSize(this->movies.getSize() - 1);
		}
		i++;
	}

}