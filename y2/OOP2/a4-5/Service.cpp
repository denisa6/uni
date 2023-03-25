#include "Service.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>


int Service::add(std::string& title, std::string& genre, std::string& trailer, int year, int numberLikes)
{
	Movie movie{ title, genre, trailer, year, numberLikes };
	Movie m = this->repo.findByTitleAndYear(title, year);
	if (m == movie)
		return 0;
	this->repo.addMovie(movie);
	return 1;
}

int Service::remove(std::string& title, int year)
{
	Movie m = this->repo.findByTitleAndYear(title, year);
	if (m == Movie{})
		return 0;
	this->repo.removeMovie(m);
	return 1;
}

int Service::updateMovieString(std::string& title, int year, std::string& updatedValue, int updater)
{
	Movie m = this->repo.findByTitleAndYear(title, year);
	if (m == Movie{})
		return 0;
	switch (updater)
	{
	case 1:
	{
		this->repo.updateMovieString(m, &Movie::setTitle, updatedValue);
		return 1;
	}
	case 2:
	{
		this->repo.updateMovieString(m, &Movie::setGenre, updatedValue);
		return 1;
	}
	case 3:
	{
		this->repo.updateMovieString(m, &Movie::setTrailer, updatedValue);
		return 1;
	}
	}
}

int Service::updateMovieInteger(std::string& title, int year, int updatedValue, int updater)
{
	Movie m = this->repo.findByTitleAndYear(title, year);
	if (m == Movie{})
		return 0;
	switch (updater)
	{
	case 1:
	{
		this->repo.updateMovieInteger(m, &Movie::setYear, updatedValue);
		return 1;
	}
	case 2:
	{
		this->repo.updateMovieInteger(m, &Movie::setNumberLikes, updatedValue);
		return 1;
	}
	}
}

DynamicVector<Movie> Service::filter(std::string& genre)
{
	DynamicVector<Movie> movies, filteredList;

	movies = this->repo.getMovies();
	filteredList = DynamicVector<Movie>();
	for (int i = 0; i < this->repo.getSize(); i++)
	{
		if (movies[i].getGenre() == genre)
			filteredList.add(movies[i]);
	}
	if (filteredList.getSize() == 0)
		for (int i = 0; i < this->repo.getSize(); i++)
			filteredList.add(movies[i]);


	return filteredList;
}

void Service::addMovie(Movie movie)
{
	Movie m = this->repo.findByTitleAndYear(movie.getTitle(), movie.getYear());
	if (m == movie)
		return;
	this->repo.addMovie(movie);
}