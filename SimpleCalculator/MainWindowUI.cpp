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
	LayoutButtons = new QGridLayout();

	FrameArithmetic = new ArithmeticPanel(CentralWidget);
	
	addButton("0", Button0, Digit);
	addButton("1", Button1, Digit);
	addButton("2", Button2, Digit);
	addButton("3", Button3, Digit);
	addButton("4", Button4, Digit);
	addButton("5", Button5, Digit);
	addButton("6", Button6, Digit);
	addButton("7", Button7, Digit);
	addButton("8", Button8, Digit);
	addButton("9", Button9, Digit);

	addButton("+", ButtonAdd, Op);
	addButton("-", ButtonSub, Op);
	addButton("×", ButtonMul, Op);
	addButton("÷", ButtonDiv, Op);
	addButton("=", ButtonEqual, Op);

	addButton("Ans", ButtonAnswer, Normal);
	addButton(".", ButtonDot, Normal);
	addButton("shift", ButtonShift, Normal);
	addButton("const", ButtonConstant, Normal);
	addButton("ln", ButtonLn, Normal);
	addButton("log", ButtonLog, Normal);
	addButton("√", ButtonSqrt, Normal);
	addButton("a/b", ButtonFrac, Normal);
	addButton("x^y", ButtonPow, Normal);
	addButton("sin", ButtonSin, Normal);
	addButton("cos", ButtonCos, Normal);
	addButton("tan", ButtonTan, Normal);
	addButton("×10^n", ButtonSci, Normal);
	addButton("(", ButtonBracketLeft, Normal);
	addButton(")", ButtonBracketRight, Normal);

	QPalette pal(CentralWidget->palette());
	pal.setColor(QPalette::Background, QColor(230, 230, 230));
	CentralWidget->setAutoFillBackground(true);
	CentralWidget->setPalette(pal);

	LayoutY->addWidget(FrameArithmetic);
	LayoutY->insertSpacing(1, 10);
	LayoutY->addLayout(LayoutButtons);
	
	LayoutButtons->addWidget(getButton(ButtonSqrt), 0, 0);
	LayoutButtons->addWidget(getButton(ButtonLog), 1, 0);
	LayoutButtons->addWidget(getButton(ButtonLn), 2, 0);
	LayoutButtons->addWidget(getButton(ButtonConstant), 3, 0);
	LayoutButtons->addWidget(getButton(ButtonShift), 4, 0);
	LayoutButtons->addWidget(getButton(ButtonFrac), 0, 1);
	LayoutButtons->addWidget(getButton(ButtonPow), 0, 2);
	LayoutButtons->addWidget(getButton(ButtonSin), 0, 3);
	LayoutButtons->addWidget(getButton(ButtonCos), 0, 4);
	LayoutButtons->addWidget(getButton(ButtonTan), 0, 5);

	LayoutButtons->addWidget(getButton(Button0), 4, 1);
	LayoutButtons->addWidget(getButton(Button1), 3, 1);
	LayoutButtons->addWidget(getButton(Button2), 3, 2);
	LayoutButtons->addWidget(getButton(Button3), 3, 3);
	LayoutButtons->addWidget(getButton(Button4), 2, 1);
	LayoutButtons->addWidget(getButton(Button5), 2, 2);
	LayoutButtons->addWidget(getButton(Button6), 2, 3);
	LayoutButtons->addWidget(getButton(Button7), 1, 1);
	LayoutButtons->addWidget(getButton(Button8), 1, 2);
	LayoutButtons->addWidget(getButton(Button9), 1, 3);

	LayoutButtons->addWidget(getButton(ButtonAdd), 3, 4);
	LayoutButtons->addWidget(getButton(ButtonSub), 3, 5);
	LayoutButtons->addWidget(getButton(ButtonMul), 2, 4);
	LayoutButtons->addWidget(getButton(ButtonDiv), 2, 5);

	LayoutButtons->addWidget(getButton(ButtonAnswer), 4, 4);
	LayoutButtons->addWidget(getButton(ButtonEqual), 4, 5);
	LayoutButtons->addWidget(getButton(ButtonDot), 4, 2);
	LayoutButtons->addWidget(getButton(ButtonSci), 4, 3);
	LayoutButtons->addWidget(getButton(ButtonBracketLeft), 1, 4);
	LayoutButtons->addWidget(getButton(ButtonBracketRight), 1, 5);

	LayoutButtons->setSpacing(3);

	LayoutY->setStretchFactor(FrameArithmetic, 6);
	LayoutY->setStretchFactor(LayoutButtons, 8);
	LayoutY->setMargin(3);

	CentralWidget->setLayout(LayoutY);
}

MainWindowUI::~MainWindowUI()
{
	delete MenuBar;
	delete CentralWidget;
}

KeyboardButton * MainWindowUI::getButton(KbButtonName btnName)
{
	return Buttons[btnName];
}

void MainWindowUI::addButton(const char *text, KbButtonName btnName, KbButtonType btnType)
{
	Buttons[btnName] = new KeyboardButton(text, CentralWidget, btnName, btnType);
}
