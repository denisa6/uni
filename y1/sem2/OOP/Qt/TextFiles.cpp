#include "TextFiles.h"

#include <iostream>

TextFiles::TextFiles(const std::string& file_name)
{
    this->file_name = file_name;
    std::ifstream file;
    if (file)
        this->load_file();
    else this->save_file();

}

TextFiles::TextFiles()
{
}

TextFiles::TextFiles(const TextFiles& txt)
{
    this->file_name = txt.file_name;


}

void TextFiles::addTutorial(const Tutorial& m)
{
    Repository::addTutorial(m);
    std::cout << "lkjhgf";
    this->save_file();
}

int TextFiles::deleteTutorial(const std::string& presenter, const std::string& title)
{
    Repository::deleteTutorial(presenter, title);
    this->save_file();
    return 0;
}

void TextFiles::updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title)
{
    Repository::updateTutorial(presenter, old_title, new_title);
    this->save_file();
}
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void TextFiles::save_file()
{
    std::ofstream file;
    file.open(this->file_name);
    std::vector<Tutorial> tutorials = this->getTutorials();
    for (auto& tutorial : tutorials)
        file << tutorial.getTitle() << "," << tutorial.getPresenter() << "," << tutorial.getLikes() << "," << tutorial.getDuration().getMinutes() << "," << tutorial.getDuration().getSeconds() << "," << tutorial.getSource() << std::endl;
    file.close();

}

void TextFiles::load_file()
{
    std::string line;
    std::ifstream file(this->file_name);
    std::string title, presenter, source, likes, minutes, seconds;
    title = "";
    presenter = "";
    source = "";
    likes = "";
    minutes = "";
    seconds = "";

    if (file.is_open()) {

        while (std::getline(file, line)) {
            int count = 0;
            int pos = 0;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    if (count == 0)
                        for (int j = pos; j < i; j++)
                            title += line[j];
                    else if (count == 1)
                        for (int j = pos; j < i; j++)
                            presenter += line[j];
                    else if (count == 2)
                        for (int j = pos; j < i; j++)
                            likes += line[j];
                    else if (count == 3)
                        for (int j = pos; j < i; j++)
                            minutes += line[j];
                    else if (count == 4)
                        for (int j = pos; j < i; j++)
                            seconds += line[j];
                    count++;
                    pos = i + 1;
                }
            }
            for (int j = pos; j < line.length(); j++)
                source += line[j];

            Repository::addTutorial(Tutorial(presenter, title, Duration(stod(minutes), stod(seconds)), source));
            title = "";
            presenter = "";
            source = "";
            likes = "";
            minutes = "";
            seconds = "";

        }

    }
    file.close();

}

