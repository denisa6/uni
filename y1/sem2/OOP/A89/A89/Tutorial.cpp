#include "Tutorial.h"
#include "Tutorial.h"
#include <Windows.h>
#include <shellapi.h>
#include <assert.h>

Tutorial::Tutorial() : title(""), presenter(""), duration(Duration()), likes(), source("") {}

Tutorial::Tutorial(const std::string& presenter, const std::string& title, const Duration& duration, const std::string& source)
{
	this->presenter = presenter;
	this->title = title;
	this->duration = duration;
	this->source = source;
	this->likes = 0;
}

void Tutorial::setTitle(const std::string& new_title)
{
	this->title = new_title;
}

void Tutorial::increaseLikes()
{
	this->likes = this->likes++;
}

void Tutorial::play()
{
	ShellExecuteA(NULL, NULL, "opera.exe", this->getSource().c_str(), NULL, SW_SHOWMAXIMIZED);
}


// --------------------------------------------------- tests --------------------------------------------------------------------------------

void test_getMinutes()
{
	Duration d1{ 1, 0 };
	assert(d1.getMinutes() == 1);

	Duration d2{ 0, 1 };
	assert(d2.getMinutes() == 0);

	Duration d3{ 5, 55 };
	assert(d3.getMinutes() == 5);
}

void test_getSeconds()
{
	Duration d1{ 1, 0 };
	assert(d1.getSeconds() == 0);

	Duration d2{ 0, 1 };
	assert(d2.getSeconds() == 1);

	Duration d3{ 5, 55 };
	assert(d3.getSeconds() == 55);
}

void test_getTitle()
{
	Tutorial t1{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t1.getTitle() == "tutorial");

	Tutorial t2{ "mara", "title", Duration{4, 59}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	assert(t2.getTitle() == "title");

	Tutorial t3{ "cana", "tutorial3", Duration{7, 77}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	assert(t3.getTitle() == "tutorial3");
}

void test_getPresenter()
{
	Tutorial t1{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t1.getPresenter() == "ana");

	Tutorial t2{ "mara", "title", Duration{4, 59}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	assert(t2.getPresenter() == "mara");

	Tutorial t3{ "cana", "tutorial3", Duration{7, 77}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	assert(t3.getPresenter() == "cana");
}

void test_getLikes()
{
	Tutorial t1{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t1.getLikes() == 0);

	Tutorial t2{ "mara", "title", Duration{4, 59}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	t2.increaseLikes();
	assert(t2.getLikes() == 1);

	Tutorial t3{ "cana", "tutorial3", Duration{7, 77}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	t3.increaseLikes();
	t3.increaseLikes();
	assert(t3.getLikes() == 2);
}

void test_getSource()
{
	Tutorial t1{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t1.getSource() == "https://www.youtube.com/watch?v=2fngvQS_PmQ");

	Tutorial t2{ "mara", "title", Duration{4, 59}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	assert(t2.getSource() == "https://www.youtube.com/watch?v=XYKUeZQbMF0");

	Tutorial t3{ "cana", "tutorial3", Duration{7, 77}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	assert(t3.getSource() == "https://www.youtube.com/watch?v=6L-_DiZlrUI");
}


void test_getDuration()
{
	Tutorial t1{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t1.getDuration().getMinutes() == 5);
	assert(t1.getDuration().getSeconds() == 48);

	Tutorial t2{ "mara", "title", Duration{4, 59}, "https://www.youtube.com/watch?v=XYKUeZQbMF0" };
	assert(t2.getDuration().getMinutes() == 4);
	assert(t2.getDuration().getSeconds() == 59);

	Tutorial t3{ "cana", "tutorial3", Duration{7, 77}, "https://www.youtube.com/watch?v=6L-_DiZlrUI" };
	assert(t3.getDuration().getMinutes() == 7);
	assert(t3.getDuration().getSeconds() == 77);
}

void test_setTitle()
{
	Tutorial t{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t.getTitle() == "tutorial");
	t.setTitle("new_title");
	assert(t.getTitle() == "new_title");
}

void test_increaseLikes()
{
	Tutorial t{ "ana", "tutorial", Duration{5, 48}, "https://www.youtube.com/watch?v=2fngvQS_PmQ" };
	assert(t.getLikes() == 0);
	t.increaseLikes();
	assert(t.getLikes() == 1);
}

void test_Tutorial()
{
	test_getMinutes();
	test_getSeconds();
	test_getTitle();
	test_getPresenter();
	test_getLikes();
	test_getSource();
	test_getDuration();
	test_setTitle();
	test_increaseLikes();
}

