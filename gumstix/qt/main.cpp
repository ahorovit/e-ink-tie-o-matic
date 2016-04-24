
#include "menu.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	// Create background for App
	Menu * w = new Menu(3);
	w->showFullScreen();
	w->show();

	QPalette p = w->palette();
	w->setAutoFillBackground(true);



    return app.exec();
}

