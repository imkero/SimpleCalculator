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
		connect(Ui.Buttons[i], SIGNAL(signalOnClick(KbButtonName)), this, SLOT(eventKbButtonClick(KbButtonName)));
	}
}

void MainWindow::eventKbButtonClick(KbButtonName btnName)
{
	Data.Input.handle(btnName);
}