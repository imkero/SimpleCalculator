#include "MainWindow.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMessageBox>
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
	historyUpdate();
}

void MainWindow::afterInput(bool modified)
{
	if (modified)
	{
		g_Data->markExprDirty();
		g_Data->markEnsureCursorInScreen();
		if (g_Data->Config.AutoCompute)
			g_Data->doCompute();
		else
			g_Data->clearResult();
		g_Data->repaintExpr();
	}
	else
	{
		g_Data->Cursor.brighten();
		playWarnSound();
	}
}

void MainWindow::historyUpdate()
{
	Ui.updateHistoryEntry(g_Data->History.getIndex(g_Data->getRootExpr()), g_Data->History.getLength());
}

void MainWindow::showHistoryItem(const ComputeHistoryItem &item)
{
	g_Data->setRootExpr(item.Expr);
	historyUpdate();
	g_Data->ReadOnlyShowing = true;
	g_Data->Cursor.set(g_Data->getRootExpr(), 0);
	Ui.FrameArithmetic->stopBlinking();
	g_Data->markEnsureCursorInScreen();
	g_Data->markExprDirty();
	g_Data->repaintExpr();
	g_Data->setResult(item.Result);
}

void MainWindow::exitReadOnlyMode()
{
	historyUpdate();
	g_Data->clearResult();
	g_Data->markEnsureCursorInScreen();
	g_Data->markExprDirty();
	Ui.FrameArithmetic->startBlinking();
	g_Data->repaintExpr();
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key::Key_PageUp:
		eventHistoryUp();
		return;
	case Qt::Key::Key_PageDown:
		eventHistoryDown();
		return;
	}
	
	auto refl = Ui.KeyboardReflections.find(event->key());
	if (refl != Ui.KeyboardReflections.end())
	{
		(*refl).second->click();
		if (event->key() != Qt::Key::Key_V)
		{
			(*refl).second->setDown(true);
		}
		event->accept();
	}
	else
	{
		if (g_Data->ReadOnlyShowing)
		{
			g_Data->setRootExpr(new HorizontalExpression(nullptr));
			g_Data->Cursor.set(g_Data->getRootExpr(), 0);
			g_Data->ReadOnlyShowing = false;
			exitReadOnlyMode();
		}
		switch (event->key())
		{
		case Qt::Key::Key_Enter:
		case Qt::Key::Key_Return:
			Ui.Buttons[ButtonEqual]->click();
			event->accept();
			break;
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
		case Qt::Key::Key_Delete:
			Cursor cursor = g_Data->Cursor.get();
			afterInput(cursor.FocusdExpr->input(ButtonDelete, cursor.Pos));
			event->accept();
			break;
		case Qt::Key::Key_Home:
			g_Data->Cursor.moveToFront();
			g_Data->markEnsureCursorInScreen();
			g_Data->repaintExpr();
			event->accept();
			break;
		case Qt::Key::Key_End:
			g_Data->Cursor.moveToBack();
			g_Data->markEnsureCursorInScreen();
			g_Data->repaintExpr();
			event->accept();
			break;
		case Qt::Key::Key_Up:
			g_Data->Cursor.moveUp();
			g_Data->markEnsureCursorInScreen();
			g_Data->repaintExpr();
			event->accept();
			break;
		case Qt::Key::Key_Down:
			g_Data->Cursor.moveDown();
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
		if (!g_Data->ReadOnlyShowing)
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

void MainWindow::eventHistoryUp()
{
	int index = g_Data->History.getIndex(g_Data->getRootExpr());
	if (index > 0)
	{
		showHistoryItem(g_Data->History.get(index - 1));
	}
	else if (index == -1)
	{
		int length = g_Data->History.getLength();
		if (length > 0)
			showHistoryItem(g_Data->History.get(length - 1));
	}
}

void MainWindow::eventHistoryDown()
{
	int index = g_Data->History.getIndex(g_Data->getRootExpr());
	int length = g_Data->History.getLength();
	if (index == -1)
	{
		if (length > 0)
			showHistoryItem(g_Data->History.get(0));
	}
	else if (index < length - 1)
	{
		showHistoryItem(g_Data->History.get(index + 1));
	}
}

void MainWindow::connectSlot()
{
	for (int i = 0; i < sizeof(Ui.Buttons) / sizeof(*Ui.Buttons); i++)
	{
		connect(Ui.Buttons[i], &KeyboardButton::signalOnClick, this, &MainWindow::eventKbButtonClick);
	}
	connect(Ui.ActionAbout, &QAction::triggered, this, &MainWindow::eventShowAbout);
	connect(Ui.ActionHistoryUp, &QAction::triggered, this, &MainWindow::eventHistoryUp);
	connect(Ui.ActionHistoryDown, &QAction::triggered, this, &MainWindow::eventHistoryDown);
	connect(Ui.ActionSwitchAutoCompute, &QAction::triggered, this, &MainWindow::eventSwitchAutoCompute);
	connect(Ui.ActionSwitchRememberWindowSize, &QAction::triggered, this, &MainWindow::eventSwitchRememberWindowSize);
}

void MainWindow::eventKbButtonClick(KbButtonName btnName)
{
	if (g_Data->ReadOnlyShowing)
	{
		g_Data->setRootExpr(btnName == ButtonEqual ? g_Data->getRootExpr()->clone()->as<HorizontalExpression>() : new HorizontalExpression(nullptr));
		g_Data->Cursor.set(g_Data->getRootExpr(), 0);
		g_Data->ReadOnlyShowing = false;
		exitReadOnlyMode();
	}
	switch (btnName)
	{
	case ButtonEqual:
		g_Data->doCompute();
		g_Data->repaintExpr();
		if (g_Data->ExprResult.good())
		{
			g_Data->History.append(g_Data->getRootExpr(), g_Data->ExprResult);
			historyUpdate();
			g_Data->ReadOnlyShowing = true;
			Ui.FrameArithmetic->stopBlinking();
		}
		break;
	case ButtonVariable:
		Ui.VarWindow->exec();
		break;
	case ButtonDeleteAll:
	{
		if (g_Data->getRootExpr()->getLength() > 0)
		{
			g_Data->setRootExpr(new HorizontalExpression(nullptr));
			g_Data->markExprDirty();
			g_Data->markEnsureCursorInScreen();
			g_Data->clearResult();
			g_Data->Cursor.set(g_Data->getRootExpr(), 0);
		}
	}
	break;
	default:
		Cursor cursor = g_Data->Cursor.get();
		afterInput(cursor.FocusdExpr->input(btnName, cursor.Pos));
	}
	
}