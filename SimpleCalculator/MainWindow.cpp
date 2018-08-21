#include "MainWindow.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <QDebug>
#include "GlobalMgr.h"
#include "Util.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), Singleton<MainWindow>()
{
	Ui.setupUi(this);
	if (g_Data->Config.RememberWindowSize)
	{
		if (g_Data->Config.WindowMaximized)
		{
			this->setWindowState(this->windowState() | Qt::WindowMaximized);
		}
		else if (g_Data->Config.WindowWidth > 0 && g_Data->Config.WindowHeight > 0)
		{
			this->resize(g_Data->Config.WindowWidth, g_Data->Config.WindowHeight);
		}
	}
	Ui.ActionSwitchAutoCompute->setChecked(g_Data->Config.AutoCompute);
	Ui.ActionSwitchRememberWindowSize->setChecked(g_Data->Config.RememberWindowSize);
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
			
			g_Data->markEnsureCursorInScreen();
			g_Data->repaintExpr(); 
			event->accept();
			break;
		case Qt::Key::Key_Right:
			g_Data->Cursor.moveRight();
			
			g_Data->markEnsureCursorInScreen();
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

void MainWindow::closeEvent(QCloseEvent * event)
{
	g_Data->Config.WindowWidth = this->width();
	g_Data->Config.WindowHeight = this->height();
	g_Data->Config.WindowMaximized = this->isMaximized();
	g_Data->Config.saveToFile();
	QMainWindow::closeEvent(event);
}

void MainWindow::changeEvent(QEvent * event)
{
	if (event->type() == QEvent::Type::WindowStateChange)
	{
		QWindowStateChangeEvent *windowStateEvent = static_cast<QWindowStateChangeEvent *>(event);
		bool minimizedBefore = windowStateEvent->oldState().testFlag(Qt::WindowState::WindowMinimized);
		bool minimizedAfter = windowState().testFlag(Qt::WindowState::WindowMinimized);
		if (minimizedBefore != minimizedAfter)
		{
			if (minimizedAfter)
			{
				Ui.FrameArithmetic->stopBlinking();
			}
			else
			{
				Ui.FrameArithmetic->startBlinking();
			}
		}
	}
	QMainWindow::changeEvent(event);
}


void MainWindow::eventShowAbout()
{
	QMessageBox::information(this, "¹ØÓÚ", "Simple Calculator\nVer 1.0.0\n\nA simple scientific calculator.");
}

void MainWindow::eventOpenComputeHistoryFileDialog()
{
}

void MainWindow::eventSaveComputeHistoryFileDialog()
{
}

void MainWindow::eventSwitchAutoCompute(bool checked)
{
	g_Data->Config.AutoCompute = checked;
}

void MainWindow::eventSwitchRememberWindowSize(bool checked)
{
	g_Data->Config.RememberWindowSize = checked;
}

void MainWindow::connectSlot()
{
	for (int i = 0; i < sizeof(Ui.Buttons) / sizeof(*Ui.Buttons); i++)
	{
		connect(Ui.Buttons[i], &KeyboardButton::signalOnClick, this, &MainWindow::eventKbButtonClick);
	}
	connect(Ui.ActionAbout, &QAction::triggered, this, &MainWindow::eventShowAbout);
	connect(Ui.ActionSwitchAutoCompute, &QAction::triggered, this, &MainWindow::eventSwitchAutoCompute);
	connect(Ui.ActionSwitchRememberWindowSize, &QAction::triggered, this, &MainWindow::eventSwitchRememberWindowSize);
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
			g_Data->markExprDirty();
			g_Data->markEnsureCursorInScreen();
			g_Data->repaintExpr();
			if (g_Data->Config.AutoCompute)
				g_Data->markRequireCompute();
			else
				g_Data->clearResult();
		}
		else
		{
			g_Data->Cursor.brighten();
			playWarnSound();
		}
	}
	
}