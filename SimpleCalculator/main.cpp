#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "MainWindow.h"
#include "NotImplementedException.h"
#include <iostream>
int main(int argc, char *argv[])
{
	try {
		QApplication app(argc, argv);
		MainWindow mainWnd;
		mainWnd.show();
		return app.exec();
	}
	catch (NotImplementedException e1)
	{
		std::cout << "Exception:" << std::endl;
		std::cout << "  Called a not implemented function: " << e1.what() << std::endl;
	}
	return -1;
}
