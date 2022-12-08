#pragma once
#include "Repository.h"
#include <iostream>
#include <fstream>t
#include <string>

class TextFiles : public Repository {
private:
    std::string file_name;
public:

    TextFiles(const std::string& file_name);
    ~TextFiles() {};
    TextFiles();
    TextFiles(const TextFiles& txt);
    void addTutorial(const Tutorial& m) override;
    int deleteTutorial(const std::string& presenter, const std::string& title) override;
    void updateTutorial(const std::string& presenter, const std::string& old_title, const std::string& new_title) override;
    void save_file();
    void load_file();
};

