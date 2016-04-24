#include "menu.h"
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Button Constructor
Button::Button(int id, QWidget *parent) : QPushButton("", parent)
{
	this->id = id;
}

// Menu Constructor
Menu::Menu(int numButtons)
{
	// Images to load
	std::string dir = "./images/";
 	std::string ext = "_2_7.xbm";
	std::string file[] = {"aphrodite", "cat", "saturn", "venus", "text_image", "ea"};
	std::string imgFile;

	// Button size
	QSize butSize = QSize(90, 70);

	// Button placement
	int x=0, y=0, leftMargin = 50, topMargin = 50, xSpacing = 150, ySpacing = 100;

	QSignalMapper *signal = new QSignalMapper(this);

	// Generate buttons
	for (int i = 0; i < numButtons; i++)
	{
		// Assemble file name
		imgFile = dir + file[i] + ext;

		// Load images from file and generate button
		QPixmap * img = new QPixmap(imgFile.c_str());
		Button * but = new Button(i, this);

		// Map Image to button
		but->setIcon(*img);
		but->setIconSize(butSize);

		// Change button size and position
		x = leftMargin + (i % 2) * xSpacing;
		y = topMargin + (i/2) * ySpacing;

		but->setGeometry(QRect(QPoint(x,y), butSize));
		but->show();

		// Couple button with button handler
		signal->setMapping(but, but->id);
		connect(but, SIGNAL(released()), signal, SLOT(map()) );


		images.push_back(img);
		buttons.push_back(but);
	}

	connect(signal, SIGNAL(mapped(const int)),this, SLOT(handleButton(const int)));
}

// Button Handler --> write button ID to kernel Module
void Menu::handleButton(int id)
{
	printf("Button %d pressed\n", id);

	char output[10];
	sprintf(output, "%d", id);

	int pFile = open("/dev/dom_tie", O_RDWR);
	if (pFile < 0){
		printf("dom_tie module not loaded\n");
		return;
	}
		
	write(pFile, output, strlen(output));


}



