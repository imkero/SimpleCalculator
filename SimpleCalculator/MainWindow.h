#pragma once
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QAction>
#include "MainWindowUI.h"
#include "Singleton.h"
#include "HistoryMgr.h"

class MainWindow : public QMainWindow, public Singleton<MainWindow>
{
	Q_OBJECT
private:
	MainWindowUI Ui;
	void connectSlot();

protected slots:
	void eventKbButtonClick(KbButtonName);
	void eventShowAbout();
	void eventShowHelp();
	void eventOpenComputeHistoryFileDialog();
	void eventSaveComputeHistoryFileDialog();
	void eventSwitchAutoCompute(bool);
	void eventSwitchRememberWindowSize(bool);
	void eventSwitchThousandComma(bool);
	void eventHistoryUp();
	void eventHistoryDown();

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	void afterInput(bool);
	void historyUpdate();
	void showHistoryItem(const ComputeHistoryItem &);
	void exitReadOnlyMode();
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);
	void changeEvent(QEvent *event);
};