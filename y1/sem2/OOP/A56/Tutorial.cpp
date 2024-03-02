#include "Tutorial.h"
#include <Windows.h>
#include <shellapi.h>

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

