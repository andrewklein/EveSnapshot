#include <QApplication>
#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include "MainWindow.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
using namespace EveSnapshot;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow * window = new MainWindow();





	window->show();


	return app.exec();
}