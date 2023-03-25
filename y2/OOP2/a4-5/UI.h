#pragma once
#include "Service.h".
//User mode : can create a watch list
//allow the user to :
//See the movies with given genre(genre empty, see all the movies), one by one.
//user chooses this option => the data of the first movie
// (title\genre\year of release\number of likes) displayed and trailer is played in the browser.
//user likes the trailer, she can add the movie to her watch list.
//trailer is not satisfactory, the user can choose not to add the movie to the watch list and to
//continue to the next.In this case, the information corresponding to the next movie is shown and the user
//is again offered the possibility to add it to the watch list.This can continue as long as the user wants, 
//as when arriving to the end of the list of movies with the given genre, if the user chooses next, the
//application will again show the first movie.
//Delete a movie from the watch list, after the user watched the movie.When deleting a movie from the watch 
//list, the user can also rate the movie(with a like), and in this case, the number of likes the movie has 
//in the repository will be increased.
//See the watch list.
class UI {
private:
	Service serv;
	Service moviePlaylist;

public:
	UI(const Service& serv, const Service& moviePlaylist) : serv(serv), moviePlaylist(moviePlaylist) {}

private:
	static void printMenu();
	static void printUserMenu();
	static void printAdministratorMenu();
	static void printUpdateMenu();
	static void printViewingOptions();
	static void printMovieListOptions();
	static int readNumber();
	static void writeFile(std::string file, DynamicVector<Movie> movies, int size);

public:
	void start();
	int startAdministrator();
	int startUser();
	void addMovieToDataBase();
	void removeMovieFromDataBase();
	void printMovieList(DynamicVector<Movie> movies, int size);
	void readFile(std::string file);
	void updateMovieFromDataBase();
	void printMovie(Movie movie);
	void filterAfterGenre();
	void iterateMovieList();
};