#pragma once
#include <iostream>

class Duration
{
private:
	double minutes;
	double seconds;
public:
	Duration() : minutes(0), seconds(0) {}
	Duration(double min, double sec) : minutes(min), seconds(sec) {}

	double getMinutes() const { return minutes; }
	double getSeconds() const { return seconds; }
};

class Tutorial
{
private:
	std::string title;
	std::string presenter;
	Duration duration;
	int likes;
	std::string source;		// youtube Link

public:
	// default constructor for a song
	Tutorial();

	// constructor with parameters
	Tutorial(const std::string& artist, const std::string& title, const Duration& duration, const std::string& source);

	std::string getTitle() const { return title; }
	std::string getPresenter() const { return presenter; }
	int getLikes() const { return likes; }
	std::string getSource() const { return source; }
	Duration getDuration() const { return duration; }
	void setTitle(const std::string& new_title);
	void increaseLikes();

	// Plays the current song: the page corresponding to the source link is opened in a browser.
	void play();


};

void test_Tutorial();




