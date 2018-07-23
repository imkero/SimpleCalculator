#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
<<<<<<< HEAD
	Ui.setupUi(this);
	connectSlot();
	
=======
	ui.setupUi(this);
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
}

MainWindow::~MainWindow()
{
}
<<<<<<< HEAD

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
=======
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
