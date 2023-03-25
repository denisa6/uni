#include "Tests.h"
#include <assert.h>
#include "Movie.h"
#include "DynamicVector.h"
#include "Repository.h"
#include "Service.h"

void Tests::testMovie()
{
	Movie m{};
	m.setTitle("Cars");
	m.setGenre("Animation");
	m.setTrailer("https://www.youtube.com/watch?v=SbXIj2T-_uk");
	m.setYear(2006);
	m.setNumberLikes(0);
	assert(m.getGenre() == "Animation");
	assert(m.getTitle() == "Cars");
	assert(m.getTrailer() == "https://www.youtube.com/watch?v=SbXIj2T-_uk");
	assert(m.getNumberLikes() == 0);
	assert(m.getYear() == 2006);
}

void Tests::testDynamicVector()
{
	DynamicVector<int> v1{ 2 };
	v1.add(10);
	v1.add(20);
	assert(v1.getSize() == 2);
	assert(v1[1] == 20);
	v1[1] = 25;
	assert(v1[1] == 25);
	v1.add(30);
	assert(v1.getSize() == 3);

	DynamicVector<int> v2{ v1 };
	assert(v2.getSize() == 3);

	DynamicVector<int> v3;
	v3 = v1;
	assert(v3[0] == 10);

	DynamicVector<int> v4;
	v4 = v4 + 5;
	assert(v4[0] == 5);
	v4 = 1 + v4;
	assert(v4[1] == 1);


	// test iterator
	DynamicVector<int>::iterator it = v1.begin();
	assert(*it == 10);
	assert(it != v1.end());
	it++;
	assert(*it == 25);
}

void Tests::testRepository()
{
	Repository repo{};
	Movie m{ "Cars", "Animation", "https://www.youtube.com/watch?v=SbXIj2T-_uk", 2006, 0 };
	repo.addMovie(m);
	Movie res = repo.findByTitleAndYear("Cars", 2006);
	assert(res.getTitle() == m.getTitle() && res.getGenre() == m.getGenre());
	res = repo.findByTitleAndYear("Cars", 0);
	assert(res.getGenre() == "");
	repo.updateMovieString(m, &Movie::setGenre, "Horror");
	m = repo.findByTitleAndYear("Cars", 2006);
	assert(m.getGenre() == "Horror");
	repo.updateMovieInteger(m, &Movie::setYear, 2008);
	m = repo.findByTitleAndYear("Cars", 2008);
	assert(m.getYear() == 2008);

	DynamicVector<Movie> movies = repo.getMovies();
	assert(movies.getSize() == 1);
	repo.removeMovie(m);
	movies = repo.getMovies();
	assert(movies.getSize() == 0);
}

void Tests::testService()
{
	Repository repo = Repository();
	Service serv = Service(repo);
	assert(serv.getSize() == 0);

	std::string title = "Cars";
	std::string genre = "Animation";
	std::string trailer = "https://www.youtube.com/watch?v=SbXIj2T-_uk";
	serv.add(title, genre, trailer, 2006, 0);

	assert(serv.add(title, genre, trailer, 2006, 0) == 0);

	assert(serv.getSize() == 1);

	serv.updateMovieInteger(title, 2006, 2008, 1);
	DynamicVector<Movie> movies = serv.getList();

	assert(movies[0].getYear() == 2008);

	std::string newTitle = "Masini";
	serv.updateMovieString(title, 2008, newTitle, 1);
	movies = serv.getList();
	assert(movies[0].getTitle() == "Masini");

	DynamicVector<Movie> filtered = serv.filter(genre);
	assert(filtered.getSize() == 1);

	genre = "Horror";
	filtered = serv.filter(genre);
	assert(filtered.getSize() == 1);

	serv.remove(newTitle, 2008);
	assert(serv.getSize() == 0);

	Movie nmovie{ "A" , "BB", "CC", 1985, 2 };
	serv.addMovie(nmovie);
	serv.addMovie(nmovie);
	std::string newGenre = "M";
	title = "A";
	serv.updateMovieString(title, 1985, newGenre, 2);
	movies = serv.getList();
	assert(movies[0].getGenre() == "M");

	std::string newTrailer = "Ma";
	serv.updateMovieString(title, 1985, newTrailer, 3);
	movies = serv.getList();
	assert(movies[0].getTrailer() == "Ma");

	serv.updateMovieInteger(title, 1985, 5, 2);
	movies = serv.getList();
	assert(movies[0].getNumberLikes() == 5);

	title = "";
	assert(serv.updateMovieInteger(title, 1895, 5, 1) == 0);
	assert(serv.updateMovieString(title, 1895, title, 1) == 0);
	assert(serv.remove(title, 1895) == 0);
}

void Tests::testAll()
{
	testMovie();
	testDynamicVector();
	testRepository();
	testService();
}