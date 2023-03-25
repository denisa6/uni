#pragma once
#include <iostream>

class Movie
{
private:
	std::string title;
	std::string genre;
	std::string trailer;
	int year;
	int numberLikes;
public:
	Movie();

	Movie(const std::string& title, const std::string& genre, const std::string& trailer, const int year, const int numberLikes);

	//Getter for the movie title
	std::string getTitle() const { return this->title; }
	//Getter for the movie genre
	std::string getGenre() const { return this->genre; }
	//Getter for the movie link to the trailer
	std::string getTrailer() const { return this->trailer; }
	//Getter for the movie year of release
	int getYear() const { return this->year; };
	//Getter for the movie number of likes
	int getNumberLikes() const { return this->numberLikes; }

	//Setter for the movie title
	void setTitle(std::string title);
	//Setter for the movie genre
	void setGenre(std::string genre);
	//Setter for the movie link to the trailer
	void setTrailer(std::string trailer);
	//Setter for the movie year of release
	void setYear(int year);
	//Setter for the movie number of likes
	void setNumberLikes(int numberLikes);

	bool operator==(const Movie& movie);

	void play();
};
