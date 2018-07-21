#pragma once

#include <QtWidgets/QMainWindow>
#include "MainWindowUI.h"
#include "MainWindowData.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	MainWindowUI Ui;
	MainWindowData Data;

	void connectSlot();

public slots:
	void eventKbButtonClick(KbButtonName);

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
};