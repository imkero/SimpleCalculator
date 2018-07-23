#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "ArithmeticPanel.h"
#include "Enums.h"
#include "KeyboardButton.h"

class MainWindowUI
{
public:
	QMenuBar *MenuBar;
	QWidget *CentralWidget;

	// Layouts
	QVBoxLayout *LayoutY;
	QGridLayout *LayoutButtons;

	// Arithmetic Panel
	ArithmeticPanel *FrameArithmetic;

	// Calc Keyboard Buttons
<<<<<<< HEAD
	KeyboardButton *Buttons[KbButtonName::_Last];

	MainWindowUI();
	void setupUi(QMainWindow *);
	KeyboardButton *getButton(KbButtonName);
=======
	KeyboardButton *Button0;
	KeyboardButton *Button1;
	KeyboardButton *Button2;
	KeyboardButton *Button3;
	KeyboardButton *Button4;
	KeyboardButton *Button5;
	KeyboardButton *Button6;
	KeyboardButton *Button7;
	KeyboardButton *Button8;
	KeyboardButton *Button9;
	KeyboardButton *ButtonAdd;
	KeyboardButton *ButtonSub;
	KeyboardButton *ButtonMul;
	KeyboardButton *ButtonDiv;
	KeyboardButton *ButtonEqual;
	KeyboardButton *ButtonAnswer;
	KeyboardButton *ButtonDot;
	KeyboardButton *ButtonShift;
	KeyboardButton *ButtonConstant;
	KeyboardButton *ButtonLn;
	KeyboardButton *ButtonLog;
	KeyboardButton *ButtonSqrt;
	KeyboardButton *ButtonFrac; // Fraction
	KeyboardButton *ButtonPow;
	KeyboardButton *ButtonSin;
	KeyboardButton *ButtonCos;
	KeyboardButton *ButtonTan;
	KeyboardButton *ButtonBracketLeft;
	KeyboardButton *ButtonBracketRight;
	KeyboardButton *ButtonSci; // Scientific notation

	MainWindowUI();
	void setupUi(QMainWindow *);
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
	~MainWindowUI();
};

