#include "MainWindow.h"
#include <QMessageBox>
#include <iostream>
#include "GlobalMgr.h"
#include "Util.h"

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
	switch (btnName)
	{
	case ButtonEqual:
		g_Data->updateResult();
		g_Data->repaintExpr();
		break;
	default:
		Cursor cursor = g_Data->Cursor.get();
		if (cursor.FocusdExpr->input(btnName, cursor.Pos))
		{
			g_Data->updateResult();
			g_Data->repaintExpr();
		}
		else
		{
			playWarnSound();
		}
	}
	
}