#include "Movie.h"
#include <Windows.h>
#include <shellapi.h>

Movie::Movie() : title(""), genre(""), trailer(""), year(int()), numberLikes(int()) {}

Movie::Movie(const std::string& title, const std::string& genre, const std::string& trailer, const int year, const int numberLikes)
{
	this->title = title;
	this->genre = genre;
	this->trailer = trailer;
	this->numberLikes = numberLikes;
	this->year = year;
}

void Movie::setTitle(std::string title)
{
	this->title = title;
}
void Movie::setTrailer(std::string trailer)
{
	this->trailer = trailer;
}
void Movie::setGenre(std::string genre)
{
	this->genre = genre;
}
void Movie::setYear(int year)
{
	this->year = year;
}
void Movie::setNumberLikes(int numberLikes)
{
	this->numberLikes = numberLikes;
}


void Movie::play()
{
	ShellExecuteA(nullptr, nullptr, "opera.exe", this->getTrailer().c_str(), nullptr, SW_SHOWMAXIMIZED);
}

bool Movie::operator==(const Movie& movie)
{
	if (this->genre == movie.getGenre() && this->numberLikes == movie.getNumberLikes()
		&& this->trailer == movie.getTrailer() && this->title == movie.getTitle() && this->year == movie.getYear())
		return true;
	return false;
}