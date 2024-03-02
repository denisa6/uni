#pragma once
#include <qwidget.h>
#include "Controller.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpainter.h>


class GUI : public QWidget {
private:
	Controller& c;
	void initGUI();
	QLabel* titleWidget;
	QPushButton* adminButton;
	QPushButton* userButton;
	void showAdmin();
	void showUser();
	void connectSignalsAndSlots();
public:
	explicit GUI(Controller& c);
};

class AdminGUI :public QWidget
{
private:
	Controller& c;
	QListWidget* tutorialsWidget;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* filterButton;
	QLineEdit* presenterWidget;
	QLineEdit* titleWidget;
	QLineEdit* durationWidget;
	QLineEdit* linkWidget;
	QLineEdit* updateWidget;
	void bindAdminGUI();
	void populate();
	void initFields();
	int getSelectedIndex();
	void connectSignalsWIthSlots();
	void deleteTutorial();
	void addTutorial();
	void updateTutorial();
	void filterTutorials();
	void painter();
public:
	AdminGUI(QWidget* parent, Controller& c);

};

class UserGUI :public QWidget
{
private:
	std::vector<Tutorial> filteredTutorials;
	Controller& c;
	QListWidget* watchListWidget, *tutorialsWidget;
	QLineEdit* presenterWidget;
	QLineEdit* titleWidget;
	QLineEdit* durationWidget;
	QLineEdit* linkWidget;
	QPushButton* addButton;
	QPushButton* playButton;
	QPushButton* nextButton;
	QPushButton* filterButton;
	void bindUserGUI();
	void populateWL();
	void populateTL();
	void initFieldsWL();
	void initFieldsTL();
	int getSelectedIndexWL();
	int getSelectedIndexTL();
	void connectSignalsWithSlots();
	void addTutorialToWatchList();
	void playTutorial();
	void nextTutorial();
	void filterTutorials();
public:
	UserGUI(QWidget* parent, Controller& c);
};
