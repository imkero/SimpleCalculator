#include <QtWidgets/QApplication>
#include <QTranslator>
#include "MainWindow.h"
#include "GlobalMgr.h"
#include "DefaultTranslator.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GlobalMgr::init();

	DefaultTranslator *translator = new DefaultTranslator();
	app.installTranslator(translator);

	MainWindow mainWnd;
	mainWnd.show();

	return app.exec();
}
