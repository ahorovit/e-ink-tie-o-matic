#ifndef MENU_H
#define MENU_H

#include <QApplication> 
#include <QCoreApplication>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QSignalMapper>
#include <stdio.h>
#include <stdlib.h>

// Button Class
class Button : public QPushButton
{
	Q_OBJECT
public:
	Button(int id, QWidget *parent);
	int id;

//	virtual ~Button(){};
};




// Menu Class
class Menu : public QWidget
{
	Q_OBJECT
public:
	Menu(int numButtons);
//	virtual ~Menu(){};

private slots:
	void handleButton(const int id);

//signals:
//	void clicked(int id);

private:
	std::vector<Button *> buttons;
	std::vector<QPixmap *> images;
};

#endif
