#include "GUI.h"
#include <qvboxlayout>
#include <qhboxlayout>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <vector>
#include <qlist.h>
#include <QMessageBox>
#include <iostream>



// ------------------------------------------------------ Admin GUI --------------------------------------------------------------------------

void AdminGUI::bindAdminGUI()
{
	tutorialsWidget = new QListWidget();
	addButton = new QPushButton("Add");
	deleteButton = new QPushButton("Delete");
	updateButton = new QPushButton("Update");
	filterButton = new QPushButton("Filter");
	presenterWidget = new QLineEdit();
	titleWidget = new QLineEdit();
	durationWidget = new QLineEdit();
	linkWidget = new QLineEdit();
	updateWidget = new QLineEdit();


	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(tutorialsWidget);
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Presenter", presenterWidget);
	formLayout->addRow("Title", titleWidget);
	formLayout->addRow("Duration", durationWidget);
	formLayout->addRow("Link", linkWidget);
	formLayout->addRow("New title", updateWidget);
	mainLayout->addLayout(formLayout);
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(deleteButton,0,1);
	gridLayout->addWidget(updateButton,0,2);
	gridLayout->addWidget(filterButton,1,1);
	mainLayout->addLayout(gridLayout);
}

void AdminGUI::populate()
{
	tutorialsWidget->clear();
	std::vector<Tutorial> tutorials = c.getRepo()->getTutorials();
	for (Tutorial& t : tutorials)
	{
		tutorialsWidget->addItem(QString::fromStdString(t.getPresenter()) + ", " + QString::fromStdString(t.getTitle()));
	}
}

void AdminGUI::initFields()
{
	int index = getSelectedIndex();
	Tutorial t = c.getRepo()->getTutorials()[index];
	Duration d = t.getDuration();
	std::string min = std::to_string(int(d.getMinutes()));
	std::string sec = std::to_string(int(d.getSeconds()));
	std::string time = min + ":" + sec;

	presenterWidget->setText(QString::fromStdString(t.getPresenter()));
	titleWidget->setText(QString::fromStdString(t.getTitle()));
	durationWidget->setText(QString::fromStdString(time));
	linkWidget->setText(QString::fromStdString(t.getSource()));
}

int AdminGUI::getSelectedIndex()
{
	QModelIndexList indexes = tutorialsWidget->selectionModel()->selectedIndexes();
	if (indexes.size() == 0)
		return -1;
	return indexes[0].row();
}

void AdminGUI::connectSignalsWIthSlots()
{
	QObject::connect(tutorialsWidget, &QListWidget::clicked, this, &AdminGUI::initFields);
	QObject::connect(deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteTutorial);
	QObject::connect(addButton, &QPushButton::clicked, this, &AdminGUI::addTutorial);
	QObject::connect(updateButton, &QPushButton::clicked, this, &AdminGUI::updateTutorial);
	QObject::connect(filterButton, &QPushButton::clicked, this, &AdminGUI::filterTutorials);
}

void AdminGUI::deleteTutorial()
{
	int index = getSelectedIndex();
	if (index == -1)
	{
		QMessageBox::critical(this, QString::fromStdString("error"), QString::fromStdString("Nothing is selected"));
	}
	c.getRepo()->deleteTutorial(c.getRepo()->getTutorials()[index].getPresenter(), c.getRepo()->getTutorials()[index].getTitle());
	populate();
}

void AdminGUI::addTutorial()
{
	std::string presenter = presenterWidget->text().toStdString();
	std::string title = titleWidget->text().toStdString();
	std::string duration = durationWidget->text().toStdString();
	std::string link = linkWidget->text().toStdString();

	std::string time = duration.substr(0, duration.find(":"));
	std::string time2 = duration.substr(duration.find(":")+1, duration.length());
	double min = std::stod(time);
	double sec = std::stod(time2);
	this->c.addTutorialToRepository(presenter, title, min, sec, link);

	this->populate();
}

void AdminGUI::updateTutorial()
{
	std::string presenter = presenterWidget->text().toStdString();
	std::string title = titleWidget->text().toStdString();
	std::string newTitle = updateWidget->text().toStdString();
	this->c.updateTutorial(presenter, title, newTitle);
	this->populate();
}

void AdminGUI::filterTutorials()
{
	std::string presenter = presenterWidget->text().toStdString();
	std::vector<Tutorial> tutorials = c.getRepo()->getTutorials();
	std::vector<Tutorial> newTutorials;
	for (Tutorial& t : tutorials)
	{
		std::size_t found = t.getPresenter().find(presenter);
		if (found != std::string::npos)
			newTutorials.push_back(t);
	}
	tutorialsWidget->clear();
	for (Tutorial& t : newTutorials)
	{
		tutorialsWidget->addItem(QString::fromStdString(t.getPresenter()) + ", " + QString::fromStdString(t.getTitle()));
	}

}

void AdminGUI::painter()
{
	QPainter painter(addButton);
	QLinearGradient linearGradient(QPointF(100, 100), QPointF(200, 200));
	linearGradient.setColorAt(1, Qt::red);
	QRect linearRect(50, 50, 200, 200);
	painter.fillRect(linearRect, linearGradient);
}

AdminGUI::AdminGUI(QWidget* parent, Controller& c):c{c}
{
	bindAdminGUI();
	//inter();
	populate();
	connectSignalsWIthSlots();
}




// --------------------------------------------- USER GUI ------------------------------------------------------------------------------------

void UserGUI::bindUserGUI()
{
	tutorialsWidget = new QListWidget();
	watchListWidget = new QListWidget();
	addButton = new QPushButton("Add");
	playButton = new QPushButton("Play");
	nextButton = new QPushButton("Next");
	filterButton = new QPushButton("Filter");
	presenterWidget = new QLineEdit();
	titleWidget = new QLineEdit();
	durationWidget = new QLineEdit();
	linkWidget = new QLineEdit();

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(tutorialsWidget);
	mainLayout->addWidget(watchListWidget);
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow("Presenter", presenterWidget);
	formLayout->addRow("Title", titleWidget);
	formLayout->addRow("Duration", durationWidget);
	formLayout->addRow("Link", linkWidget);
	mainLayout->addLayout(formLayout);
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(playButton, 0, 1);
	gridLayout->addWidget(nextButton, 0, 2);
	gridLayout->addWidget(filterButton, 1, 1);
	mainLayout->addLayout(gridLayout);
}

void UserGUI::populateWL()
{
	watchListWidget->clear();
	std::vector<Tutorial> watchList = c.getWatchList()->getWatchList();
	for (Tutorial& t : watchList)
	{
		watchListWidget->addItem(QString::fromStdString(t.getPresenter()) + ", " + QString::fromStdString(t.getTitle()));
	}
}

void UserGUI::populateTL()
{
	tutorialsWidget->clear();
	std::vector<Tutorial> tutorials = filteredTutorials;
	for (Tutorial& t : tutorials)
	{
		tutorialsWidget->addItem(QString::fromStdString(t.getPresenter()) + ", " + QString::fromStdString(t.getTitle()));
	}
}

void UserGUI::initFieldsWL()
{
	int index = getSelectedIndexWL();
	Tutorial t = c.getWatchList()->getWatchList()[index];
	Duration d = t.getDuration();
	std::string min = std::to_string(int(d.getMinutes()));
	std::string sec = std::to_string(int(d.getSeconds()));
	std::string time = min + ":" + sec;

	presenterWidget->setText(QString::fromStdString(t.getPresenter()));
	titleWidget->setText(QString::fromStdString(t.getTitle()));
	durationWidget->setText(QString::fromStdString(time));
	linkWidget->setText(QString::fromStdString(t.getSource()));
}

void UserGUI::initFieldsTL()
{
	int index = getSelectedIndexTL();
	Tutorial t = filteredTutorials[index];
	Duration d = t.getDuration();
	std::string min = std::to_string(int(d.getMinutes()));
	std::string sec = std::to_string(int(d.getSeconds()));
	std::string time = min + ":" + sec;

	presenterWidget->setText(QString::fromStdString(t.getPresenter()));
	titleWidget->setText(QString::fromStdString(t.getTitle()));
	durationWidget->setText(QString::fromStdString(time));
	linkWidget->setText(QString::fromStdString(t.getSource()));
}

int UserGUI::getSelectedIndexWL()
{
	QModelIndexList indexes = watchListWidget->selectionModel()->selectedIndexes();
	if (indexes.size() == 0)
		return -1;
	return indexes[0].row();
}

int UserGUI::getSelectedIndexTL()
{
	QModelIndexList indexes = tutorialsWidget->selectionModel()->selectedIndexes();
	if (indexes.size() == 0)
		return -1;
	return indexes[0].row();
}

void UserGUI::connectSignalsWithSlots()
{
	QObject::connect(watchListWidget, &QListWidget::clicked, this, &UserGUI::initFieldsWL);
	QObject::connect(tutorialsWidget, &QListWidget::clicked, this, &UserGUI::initFieldsTL);
	QObject::connect(addButton, &QPushButton::clicked, this, &UserGUI::addTutorialToWatchList);
	QObject::connect(playButton, &QPushButton::clicked, this, &UserGUI::playTutorial);
	QObject::connect(nextButton, &QPushButton::clicked, this, &UserGUI::nextTutorial);
	QObject::connect(filterButton, &QPushButton::clicked, this, &UserGUI::filterTutorials);
}

void UserGUI::addTutorialToWatchList()
{
	std::string presenter = presenterWidget->text().toStdString();
	std::string title = titleWidget->text().toStdString();
	std::string duration = durationWidget->text().toStdString();
	std::string link = linkWidget->text().toStdString();

	std::string time = duration.substr(0, duration.find(":"));
	std::string time2 = duration.substr(duration.find(":") + 1, duration.length());
	double min = std::stod(time);
	double sec = std::stod(time2);
	//this->c.addTutorialToRepository(presenter, title, min, sec, link);
	Tutorial t{ presenter, title, Duration{min, sec}, link };
	this->c.addTutorialToPlaylistC(t);
	this->populateWL();
}

void UserGUI::playTutorial()
{
	int index = getSelectedIndexWL();
	if (index == -1)
	{
		QMessageBox::critical(this, QString::fromStdString("error"), QString::fromStdString("Nothing is selected"));
	}
	//c.getRepo()->deleteTutorial(c.getRepo()->getTutorials()[index].getPresenter(), c.getRepo()->getTutorials()[index].getTitle());
	
	c.getWatchList()->getWatchList()[index].play();
	c.getWatchList()->deleteTutorialFromWatchList(index);

	populateWL();
}

void UserGUI::nextTutorial()
{
	int index = getSelectedIndexWL();
	index++;

	Tutorial t = c.getWatchList()->getWatchList()[index];
	Duration d = t.getDuration();
	std::string min = std::to_string(int(d.getMinutes()));
	std::string sec = std::to_string(int(d.getSeconds()));
	std::string time = min + ":" + sec;

	presenterWidget->setText(QString::fromStdString(t.getPresenter()));
	titleWidget->setText(QString::fromStdString(t.getTitle()));
	durationWidget->setText(QString::fromStdString(time));
	linkWidget->setText(QString::fromStdString(t.getSource()));
}

void UserGUI::filterTutorials()
{
	filteredTutorials.clear();
	std::string presenter = presenterWidget->text().toStdString();
	std::vector<Tutorial> tutorials = c.getRepo()->getTutorials();
	std::vector<Tutorial> newTutorials;
	for (Tutorial& t : tutorials)
	{
		std::size_t found = t.getPresenter().find(presenter);
		if (found != std::string::npos)
			newTutorials.push_back(t);
	}
	tutorialsWidget->clear();
	for (Tutorial& t : newTutorials)
	{
		tutorialsWidget->addItem(QString::fromStdString(t.getPresenter()) + ", " + QString::fromStdString(t.getTitle()));
		filteredTutorials.push_back(t);
	}
}

UserGUI::UserGUI(QWidget* parent, Controller& c) :c{ c }
{
	bindUserGUI();
	//populateTL();
	populateWL();
	connectSignalsWithSlots();
}




// ---------------------------------------------------------- GUI ----------------------------------------------------------------------------

void GUI::initGUI()
{
	auto* layout = new QVBoxLayout(this);
	QFont titleFont = this->titleWidget->font();
	this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>Welcome to the Master C++ App! <br> Select your mode!</font></p>");
	titleFont.setItalic(true);
	titleFont.setPointSize(10);
	titleFont.setStyleHint(QFont::System);
	titleFont.setWeight(QFont::Weight::Bold);
	this->titleWidget->setFont(titleFont);
	layout->addWidget(this->titleWidget);
	this->adminButton->setText("Admin mode");
	
	QString linearGradient = QString("qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));");
	adminButton->setStyleSheet(QString("background-color: %1").arg(linearGradient));

	layout->addWidget(this->adminButton);
	this->userButton->setText("User mode");
	layout->addWidget(this->userButton);
	this->setLayout(layout);
	this->setStyleSheet("background-color:#D9DBF1");
}

void GUI::showAdmin()
{
	auto* admin = new AdminGUI(this, this->c);
	admin->show();
}

void GUI::showUser()
{
	auto* user = new UserGUI(this, this->c);
	user->show();
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
}

GUI::GUI(Controller& c) :c{ c }
{
	this->titleWidget = new QLabel(this);
	this->adminButton = new QPushButton(this);
	this->userButton = new QPushButton(this);
	this->initGUI();
	this->connectSignalsAndSlots();
}
