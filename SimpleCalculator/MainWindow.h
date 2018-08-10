#pragma once
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include "MainWindowUI.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	MainWindowUI Ui;
	void connectSlot();

public slots:
	void eventKbButtonClick(KbButtonName);

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
};