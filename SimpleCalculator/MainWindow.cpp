#include "MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	Ui.setupUi(this);
	connectSlot();
}

MainWindow::~MainWindow()
{
}

void MainWindow::connectSlot()
{
	for (int i = 0; i < sizeof(Ui.Buttons) / sizeof(*Ui.Buttons); i++)
	{
		connect(Ui.Buttons[i], &KeyboardButton::signalOnClick, this, &MainWindow::eventKbButtonClick);
	}
}

void MainWindow::eventKbButtonClick(KbButtonName btnName)
{
	char a[10];
	itoa(btnName, a, 10);
	QMessageBox::about(this, "eventKbButtonClick", a);
}