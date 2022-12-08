#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "Controller.h"
#include "HTML.h"
#include "TextFiles.h"
#include "GUI.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QtWidgetsApplication1 w;
    //w.show();

	Repository* repo;
	HTML repo2{ "html.html" };
	TextFiles repo1{ "Data.txt" };
	WatchList* watch_list{ };
	watch_list = &repo2;
	repo = &repo1;
	Controller ctrl{ repo, watch_list };
	//AdminGUI gui(ctrl);
	//UserGUI gui(ctrl);
	//gui.show();
	GUI gui{ctrl};
	gui.show();

    return a.exec();
}
