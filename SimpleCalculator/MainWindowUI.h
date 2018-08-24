#pragma once
#include <unordered_map>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "Enums.h"
#include "ArithmeticPanel.h"
#include "KeyboardButton.h"
#include "ResultPanel.h"
#include "VariableWindow.h"

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
	KeyboardButton *Buttons[_VisibleButtonLength];
	std::unordered_map<int, KeyboardButton *> KeyboardReflections;

	// MenuBar
	QMenuBar *MenuBar;
	QAction *ActionAbout;
	QAction *ActionSwitchAutoCompute;
	QAction *ActionSwitchRememberWindowSize;

	// Variable & Constant Window
	VariableWindow *VarWindow;

	MainWindowUI();
	void setupUi(QMainWindow *);
	KeyboardButton * getButton(KbButtonName);

	~MainWindowUI();

private:
	void addButton(const char *, KbButtonName, KbButtonType, Qt::Key keyCode = Qt::Key::Key_unknown);
};

