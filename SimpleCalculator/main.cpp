#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "GlobalMgr.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GlobalMgr::init();

	MainWindow mainWnd;
	mainWnd.show();

	return app.exec();
}
