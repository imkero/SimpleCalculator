#include "MainWindow.h"
#include <QMessageBox>
#include <iostream>
#include <QDebug>
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

void MainWindow::keyPressEvent(QKeyEvent * event)
{
	auto refl = Ui.KeyboardReflections.find(event->key());
	if (refl != Ui.KeyboardReflections.end())
	{
		(*refl).second->click();
		(*refl).second->setDown(true);
		event->accept();
	}
	else
	{
		switch (event->key())
		{
		case Qt::Key::Key_Left:
			g_Data->Cursor.moveLeft();
			g_Data->markEnsureCursorShowing();
			g_Data->repaintExpr(); 
			event->accept();
			break;
		case Qt::Key::Key_Right:
			g_Data->Cursor.moveRight();
			g_Data->markEnsureCursorShowing();
			g_Data->repaintExpr();
			event->accept();
			break;
		}
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
	auto refl = Ui.KeyboardReflections.find(event->key());
	if (refl != Ui.KeyboardReflections.end())
	{
		(*refl).second->setDown(false);
		event->accept();
	}
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
		g_Data->markRequireCompute();
		g_Data->repaintExpr();
		break;
	default:
		Cursor cursor = g_Data->Cursor.get();
		if (cursor.FocusdExpr->input(btnName, cursor.Pos))
		{
			g_Data->markRequireCompute();
			g_Data->markEnsureCursorShowing();
			g_Data->repaintExpr();
		}
		else
		{
			playWarnSound();
		}
	}
	
}