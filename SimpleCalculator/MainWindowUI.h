#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "ArithmeticPanel.h"
#include "Enums.h"
#include "KeyboardButton.h"
#include "ResultPanel.h"
#include <unordered_map>

class MainWindowUI
{
public:
	QWidget *CentralWidget;

	// Layouts
	QVBoxLayout *LayoutY;
	QGridLayout *LayoutButtons;

	// Arithmetic Panel
	ArithmeticPanel *FrameArithmetic;
	ResultPanel *FrameResult;

	// Compute Keyboard Buttons
	KeyboardButton *Buttons[_Length];
	std::unordered_map<int, KeyboardButton *> KeyboardReflections;

	// MenuBar
	QMenuBar *MenuBar;
	QAction *ActionAbout;
	QAction *ActionSwitchAutoCompute;
	QAction *ActionSwitchRememberWindowSize;

	MainWindowUI();
	void setupUi(QMainWindow *);
	KeyboardButton * getButton(KbButtonName);

	~MainWindowUI();

private:
	void addButton(const char *, KbButtonName, KbButtonType, Qt::Key keyCode = Qt::Key::Key_unknown);
};

