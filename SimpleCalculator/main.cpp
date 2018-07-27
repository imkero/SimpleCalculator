#include <QtWidgets/QApplication>
#include "MainWindow.h"
using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow mainWnd;
	mainWnd.show();
	return app.exec();
}
