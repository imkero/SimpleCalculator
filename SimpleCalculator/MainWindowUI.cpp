#include "MainWindowUI.h"

#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "ArithmeticPanel.h"

#pragma execution_character_set("utf-8")

MainWindowUI::MainWindowUI()
{
}

void MainWindowUI::setupUi(QMainWindow *wnd)
{
	wnd->resize(620, 590);

	MenuBar = new QMenuBar(wnd);
	wnd->setMenuBar(MenuBar);
	
	CentralWidget = new QWidget(wnd);
	wnd->setCentralWidget(CentralWidget);

	LayoutY = new QVBoxLayout(CentralWidget);
	LayoutButtons = new QGridLayout(CentralWidget);

	FrameArithmetic = new ArithmeticPanel(CentralWidget);
	
	Button0 = new KeyboardButton("0", CentralWidget, KbButtonName::Button0, KbButtonType::Digit);
	Button1 = new KeyboardButton("1", CentralWidget, KbButtonName::Button1, KbButtonType::Digit);
	Button2 = new KeyboardButton("2", CentralWidget, KbButtonName::Button2, KbButtonType::Digit);
	Button3 = new KeyboardButton("3", CentralWidget, KbButtonName::Button3, KbButtonType::Digit);
	Button4 = new KeyboardButton("4", CentralWidget, KbButtonName::Button4, KbButtonType::Digit);
	Button5 = new KeyboardButton("5", CentralWidget, KbButtonName::Button5, KbButtonType::Digit);
	Button6 = new KeyboardButton("6", CentralWidget, KbButtonName::Button6, KbButtonType::Digit);
	Button7 = new KeyboardButton("7", CentralWidget, KbButtonName::Button7, KbButtonType::Digit);
	Button8 = new KeyboardButton("8", CentralWidget, KbButtonName::Button8, KbButtonType::Digit);
	Button9 = new KeyboardButton("9", CentralWidget, KbButtonName::Button9, KbButtonType::Digit);
	
	ButtonAdd = new KeyboardButton("+", CentralWidget, KbButtonName::ButtonAdd, KbButtonType::Op);
	ButtonSub = new KeyboardButton("-", CentralWidget, KbButtonName::ButtonSub, KbButtonType::Op);
	ButtonMul = new KeyboardButton("×", CentralWidget, KbButtonName::ButtonMul, KbButtonType::Op);
	ButtonDiv = new KeyboardButton("÷", CentralWidget, KbButtonName::ButtonDiv, KbButtonType::Op);
	ButtonEqual = new KeyboardButton("=", CentralWidget, KbButtonName::ButtonEqual, KbButtonType::Op);
	
	ButtonAnswer = new KeyboardButton("Ans", CentralWidget, KbButtonName::ButtonAnswer, KbButtonType::Normal);
	ButtonDot = new KeyboardButton(".", CentralWidget, KbButtonName::ButtonDot, KbButtonType::Normal);
	ButtonShift = new KeyboardButton("Shift", CentralWidget, KbButtonName::ButtonShift, KbButtonType::Normal);
	ButtonConstant = new KeyboardButton("const", CentralWidget, KbButtonName::ButtonConstant, KbButtonType::Normal);
	ButtonLn = new KeyboardButton("ln", CentralWidget, KbButtonName::ButtonLn, KbButtonType::Normal);
	ButtonLog = new KeyboardButton("log", CentralWidget, KbButtonName::ButtonLog, KbButtonType::Normal);
	ButtonSqrt = new KeyboardButton("√", CentralWidget, KbButtonName::ButtonSqrt, KbButtonType::Normal);
	ButtonFrac = new KeyboardButton("a/b", CentralWidget, KbButtonName::ButtonFrac, KbButtonType::Normal);
	ButtonPow = new KeyboardButton("x^y", CentralWidget, KbButtonName::ButtonPow, KbButtonType::Normal);
	ButtonSin = new KeyboardButton("sin", CentralWidget, KbButtonName::ButtonSin, KbButtonType::Normal);
	ButtonCos = new KeyboardButton("cos", CentralWidget, KbButtonName::ButtonCos, KbButtonType::Normal);
	ButtonTan = new KeyboardButton("tan", CentralWidget, KbButtonName::ButtonTan, KbButtonType::Normal);
	ButtonSci = new KeyboardButton("×10^n", CentralWidget, KbButtonName::ButtonSci, KbButtonType::Normal);
	ButtonBracketLeft = new KeyboardButton("(", CentralWidget, KbButtonName::ButtonBracketLeft, KbButtonType::Normal);
	ButtonBracketRight = new KeyboardButton(")", CentralWidget, KbButtonName::ButtonBracketRight, KbButtonType::Normal);

	QPalette pal(CentralWidget->palette());
	pal.setColor(QPalette::Background, QColor(230, 230, 230));
	CentralWidget->setAutoFillBackground(true);
	CentralWidget->setPalette(pal);

	LayoutY->addWidget(FrameArithmetic);
	LayoutY->insertSpacing(1, 10);
	LayoutY->addLayout(LayoutButtons);
	
	LayoutButtons->addWidget(ButtonSqrt, 0, 0);
	LayoutButtons->addWidget(ButtonLog, 1, 0);
	LayoutButtons->addWidget(ButtonLn, 2, 0);
	LayoutButtons->addWidget(ButtonConstant, 3, 0);
	LayoutButtons->addWidget(ButtonShift, 4, 0);
	LayoutButtons->addWidget(ButtonFrac, 0, 1);
	LayoutButtons->addWidget(ButtonPow, 0, 2);
	LayoutButtons->addWidget(ButtonSin, 0, 3);
	LayoutButtons->addWidget(ButtonCos, 0, 4);
	LayoutButtons->addWidget(ButtonTan, 0, 5);

	LayoutButtons->addWidget(Button0, 4, 1);
	LayoutButtons->addWidget(Button1, 3, 1);
	LayoutButtons->addWidget(Button2, 3, 2);
	LayoutButtons->addWidget(Button3, 3, 3);
	LayoutButtons->addWidget(Button4, 2, 1);
	LayoutButtons->addWidget(Button5, 2, 2);
	LayoutButtons->addWidget(Button6, 2, 3);
	LayoutButtons->addWidget(Button7, 1, 1);
	LayoutButtons->addWidget(Button8, 1, 2);
	LayoutButtons->addWidget(Button9, 1, 3);

	LayoutButtons->addWidget(ButtonAdd, 3, 4);
	LayoutButtons->addWidget(ButtonSub, 3, 5);
	LayoutButtons->addWidget(ButtonMul, 2, 4);
	LayoutButtons->addWidget(ButtonDiv, 2, 5);

	LayoutButtons->addWidget(ButtonAnswer, 4, 4);
	LayoutButtons->addWidget(ButtonEqual, 4, 5);
	LayoutButtons->addWidget(ButtonDot, 4, 2);
	LayoutButtons->addWidget(ButtonSci, 4, 3);
	LayoutButtons->addWidget(ButtonBracketLeft, 1, 4);
	LayoutButtons->addWidget(ButtonBracketRight, 1, 5);

	LayoutButtons->setSpacing(5);

	LayoutY->setStretchFactor(FrameArithmetic, 6);
	LayoutY->setStretchFactor(LayoutButtons, 8);
	LayoutY->setMargin(5);

	CentralWidget->setLayout(LayoutY);
}


MainWindowUI::~MainWindowUI()
{
}
