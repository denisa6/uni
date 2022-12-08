#include "CSV.h"
#include <fstream>
#include <Windows.h>

CSV::CSV(const std::string& text_file)
{

	this->file = text_file;
	this->save_file();



}

CSV::~CSV()
{
}

CSV::CSV()
{
}

CSV::CSV(CSV& txt)
{
	this->file = txt.file;
}

std::string CSV::getFileName()
{
	return this->file;
}

void CSV::addTutorialToPlaylist(const Tutorial& tutorial)
{
	WatchList::addTutorialToPlaylist(tutorial);
	this->save_file();

}

void CSV::deleteTutorialFromWatchList(int pos)
{
	WatchList::deleteTutorialFromWatchList(pos);
	this->save_file();
}

void CSV::addLike(int pos)
{
	WatchList::addLike(pos);
	this->save_file();
}

void CSV::save_file()
{
	std::ofstream file;

	file.open(this->file);

	for (auto& tutorial : this->tutorials_watchList)
		file << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getLikes() << "," << tutorial.getDuration().getMinutes() << "," << tutorial.getDuration().getSeconds() << "," << tutorial.getSource() << std::endl;
	file.close();

}

void CSV::displayPlaylist()
{
	std::string aux = "\"" + this->file + "\""; // if the path contains spaces, we must put it inside quotations
	//ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}
