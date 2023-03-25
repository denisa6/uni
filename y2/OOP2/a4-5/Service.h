#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;
public:
	/// <summary>
	/// Constructor for service
	/// </summary>
	/// <param name="repo"></param>
	Service(const Repository& repo) : repo(repo) {}
	/// <summary>
	/// Add a movie in the repo, if it does not already exist
	/// </summary>
	/// <param name="title"></param>
	/// <param name="genre"></param>
	/// <param name="trailer"></param>
	/// <param name="year"></param>
	/// <param name="numberLikes"></param>
	/// <returns>1 if the operation was succesful, 0 otherwise </returns>
	int add(std::string& title, std::string& genre, std::string& trailer, int year, int numberLikes);
	/// <summary>
	/// Removes a movie from the reppository
	/// </summary>
	/// <param name="title">Identifier for the movie to be removed</param>
	/// <param name="year">Identifier for the movie to be removed</param>
	/// <returns>1 if the operation was succesful, 0 otherwise </returns>
	int remove(std::string& title, int year);
	/// <summary>
	/// Function updates a movie
	/// </summary>
	/// <param name="title"></param>
	/// <param name="year"></param>
	/// <param name="updatedValue"></param>
	/// <param name="updater"></param>
	/// <returns>1 if the operation was succesful, 0 otherwise</returns>
	int updateMovieString(std::string& title, int year, std::string& updatedValue, int updater);
	/// <summary>
	/// Function updates a movie
	/// </summary>
	/// <param name="title"></param>
	/// <param name="year"></param>
	/// <param name="updatedValue"></param>
	/// <param name="updater"></param>
	/// <returns>1 if the operation was succesful, 0 otherwise</returns>
	int updateMovieInteger(std::string& title, int year, int updatedValue, int updater);
	/// <summary>
	/// Gets the movies from the repo
	/// </summary>
	/// <returns>A dynamic vector containing all the movies from the repo</returns>
	DynamicVector<Movie> getList() { return this->repo.getMovies(); }
	/// <summary>
	/// Gets the size of the list with movies
	/// </summary>
	/// <returns>The number of movies stored in the repo</returns>
	int getSize() { return this->repo.getSize(); }
	/// <summary>
	/// Filter after the genre of the movies
	/// </summary>
	/// <param name="genre"></param>
	/// <returns>A dynamic vector containing the movies with specified genre</returns>
	DynamicVector<Movie> filter(std::string& genre);
	/// Add a movie in the repo, if it does not already exist
	void addMovie(Movie movie);
};

