#include "HTML.h"
#include <fstream>
#include <Windows.h>

HTML::HTML()
{
}

HTML::HTML(const string& text_file)
{
    this->file = text_file;
    this->save_file();
}

HTML::~HTML()
{
}

string HTML::getFileName()
{
    return this->file;
}

void HTML::addTutorialToPlaylist(const Tutorial& tutorial)
{
    WatchList::addTutorialToPlaylist(tutorial);
    this->save_file();
}

void HTML::deleteTutorialFromWatchList(int pos)
{
    WatchList::deleteTutorialFromWatchList(pos);
    this->save_file();
}

void HTML::addLike(int pos)
{
    WatchList::addLike(pos);
    this->save_file();
}

void HTML::save_file()
{
    std::ofstream file;
    file.open(this->file);
    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "\t<title>Watch list</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "\t<tr>\n";

    file << "\t\t<td>Title</td>\n";
    file << "\t\t<td>Presenter</td>\n";
    file << "\t\t<td>Likes</td>\n";
    file << "\t\t<td>Minutes</td>\n";
    file << "\t\t<td>Seconds</td>\n";
    file << "\t\t<td>Source</td>\n";

    file << "\t</tr>\n";
    for (auto& tutorial : tutorials_watchList) {
        file << "\t<tr>\n";
        file << "\t\t<td>" << tutorial.getTitle() << "</td>\n";
        file << "\t\t<td>" << tutorial.getPresenter() << "</td>\n";
        file << "\t\t<td>" << tutorial.getLikes() << "</td>\n";
        file << "\t\t<td>" << tutorial.getDuration().getMinutes() << "</td>\n";
        file << "\t\t<td>" << tutorial.getDuration().getSeconds() << "</td>\n";
        file << "\t\t<td><a href=\"" << tutorial.getSource() << "\">Link</a></td>\n";
        file << "\t</tr>\n";
    }
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>";
    file.close();
}

void HTML::displayPlaylist()
{
    string open = "open";

    // Initializing an object of wstring
    wstring temp = wstring(open.begin(), open.end());

    // Applying c_str() method on temp
    LPCWSTR wideString = temp.c_str();

    string str2 = this->getFileName();

    // Initializing an object of wstring
    wstring temp2 = wstring(str2.begin(), str2.end());

    // Applying c_str() method on temp
    LPCWSTR wideString2 = temp2.c_str();


    string aux = "\"" + this->file + "\""; // if the path contains spaces, we must put it inside quotations
    //ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
    ShellExecute(NULL, wideString, wideString2, NULL, NULL, SW_SHOWNORMAL);
}
