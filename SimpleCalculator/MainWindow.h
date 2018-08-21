#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QKeyEvent>
#include <QAction>
#include "MainWindowUI.h"
#include "Singleton.h"

class MainWindow : public QMainWindow, public Singleton<MainWindow>
{
	Q_OBJECT
private:
	MainWindowUI Ui;
	void connectSlot();

protected slots:
	void eventKbButtonClick(KbButtonName);
	void eventShowAbout();
	void eventOpenComputeHistoryFileDialog();
	void eventSaveComputeHistoryFileDialog();
	void eventSwitchAutoCompute(bool);
	void eventSwitchRememberWindowSize(bool);

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);
	void changeEvent(QEvent *event);
};