#pragma once

#include <QtWidgets/QMainWindow>
#include "MainWindowUI.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private:
	MainWindowUI ui;
};