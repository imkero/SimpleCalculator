#include "MainWindow.h"
#include <QMessageBox>
#include <QDebug>

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
	qDebug() << "KbButtonClick Idx = " << btnName;
}