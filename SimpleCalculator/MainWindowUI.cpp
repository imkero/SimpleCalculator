﻿#include "MainWindowUI.h"

#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include "ArithmeticPanel.h"
#include "GlobalMgr.h"
#include "Util.h"

MainWindowUI::MainWindowUI()
{
}

void MainWindowUI::setupUi(QMainWindow *wnd)
{
	wnd->resize(620, 660);
	wnd->setMinimumSize(520, 550);
	wnd->setWindowTitle("Simple Calculator");

	setQtWindowIcon(wnd->winId());

	MenuBar = new QMenuBar(wnd);
	wnd->setMenuBar(MenuBar);
	MenuBar->setFocusPolicy(Qt::FocusPolicy::NoFocus);

	CentralWidget = new QWidget(wnd);
	wnd->setCentralWidget(CentralWidget);

	LayoutY = new QVBoxLayout(CentralWidget);
	LayoutButtons = new QGridLayout();

	FrameArithmetic = new ArithmeticPanel(CentralWidget);
	FrameResult = new ResultPanel(CentralWidget);

	addButton("0", Button0, Digit, Qt::Key::Key_0);
	addButton("1", Button1, Digit, Qt::Key::Key_1);
	addButton("2", Button2, Digit, Qt::Key::Key_2);
	addButton("3", Button3, Digit, Qt::Key::Key_3);
	addButton("4", Button4, Digit, Qt::Key::Key_4);
	addButton("5", Button5, Digit, Qt::Key::Key_5);
	addButton("6", Button6, Digit, Qt::Key::Key_6);
	addButton("7", Button7, Digit, Qt::Key::Key_7);
	addButton("8", Button8, Digit, Qt::Key::Key_8);
	addButton("9", Button9, Digit, Qt::Key::Key_9);

	addButton("+", ButtonAdd, Op, Qt::Key::Key_Plus);
	addButton("-", ButtonSub, Op, Qt::Key::Key_Minus);
	addButton("×", ButtonMul, Op, Qt::Key::Key_Asterisk);
	addButton("÷", ButtonDiv, Op, Qt::Key::Key_Slash);
	addButton("=", ButtonEqual, Op, Qt::Key::Key_Equal);

	addButton("Var", ButtonVariable, Normal, Qt::Key::Key_V);
	addButton(".", ButtonDot, Normal, Qt::Key::Key_Period);
	addButton("abs", ButtonAbs, Normal);
	addButton("←", ButtonBackspace, Normal, Qt::Key::Key_Backspace);
	addButton("ln", ButtonLn, Normal);
	addButton("log", ButtonLog, Normal);
	addButton("√", ButtonSqrt, Normal);
	addButton("a/b", ButtonFrac, Normal, Qt::Key::Key_F);
	addButton("x^y", ButtonPow, Normal, Qt::Key::Key_AsciiCircum);
	addButton("sin", ButtonSin, Normal);
	addButton("cos", ButtonCos, Normal);
	addButton("tan", ButtonTan, Normal);
	addButton("×10^n", ButtonSci, Normal);
	addButton("(", ButtonBracketLeft, Normal, Qt::Key::Key_ParenLeft);
	addButton(")", ButtonBracketRight, Normal, Qt::Key::Key_ParenRight);

	QPalette pal(CentralWidget->palette());
	pal.setColor(QPalette::Background, QColor(230, 230, 230));
	CentralWidget->setAutoFillBackground(true);
	CentralWidget->setPalette(pal);

	LayoutY->addWidget(FrameArithmetic);
	LayoutY->addWidget(FrameResult);

	LayoutY->addLayout(LayoutButtons);

	LayoutButtons->addWidget(getButton(ButtonAbs), 1, 0);
	LayoutButtons->addWidget(getButton(ButtonSqrt), 2, 0);
	LayoutButtons->addWidget(getButton(ButtonLog), 3, 0);
	LayoutButtons->addWidget(getButton(ButtonLn), 4, 0);
	LayoutButtons->addWidget(getButton(ButtonFrac), 0, 0);
	LayoutButtons->addWidget(getButton(ButtonPow), 0, 1);
	LayoutButtons->addWidget(getButton(ButtonSin), 0, 2);
	LayoutButtons->addWidget(getButton(ButtonCos), 0, 3);
	LayoutButtons->addWidget(getButton(ButtonTan), 0, 4);
	LayoutButtons->addWidget(getButton(ButtonBackspace), 0, 5);

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

	LayoutButtons->addWidget(getButton(ButtonVariable), 4, 4);
	LayoutButtons->addWidget(getButton(ButtonEqual), 4, 5);
	LayoutButtons->addWidget(getButton(ButtonDot), 4, 2);
	LayoutButtons->addWidget(getButton(ButtonSci), 4, 3);
	LayoutButtons->addWidget(getButton(ButtonBracketLeft), 1, 4);
	LayoutButtons->addWidget(getButton(ButtonBracketRight), 1, 5);

	LayoutButtons->setSpacing(3);

	LayoutY->setStretchFactor(FrameArithmetic, 4);
	LayoutY->setStretchFactor(LayoutButtons, 8);

	LayoutY->setMargin(3);

	CentralWidget->setLayout(LayoutY);

	QMenu *menuSettings = new QMenu("设置(&S)");
	ActionSwitchAutoCompute = menuSettings->addAction("自动计算(&A)");
	ActionSwitchAutoCompute->setCheckable(true);

	ActionSwitchRememberWindowSize = menuSettings->addAction("窗口大小记忆(&M)");
	ActionSwitchRememberWindowSize->setCheckable(true);

	ActionSwitchThousandComma = menuSettings->addAction("千位分隔符(&D)");
	ActionSwitchThousandComma->setCheckable(true);
	
	QMenu *menuHistory = new QMenu("计算历史(&H)");
	ActionHistoryUp = menuHistory->addAction("上一条(&U)");
	ActionHistoryDown = menuHistory->addAction("下一条(&D)");

	QMenu *menuHelp = new QMenu("帮助(&A)");
	ActionHelp = menuHelp->addAction("使用说明(&H)");
	ActionAbout = menuHelp->addAction("关于 Simple Calculator(&A)");

	MenuBar->addMenu(menuSettings);
	MenuBar->addMenu(menuHelp);
	ActionHistoryEntry = MenuBar->addMenu(menuHistory);

	VarWindow = new VariableWindow(wnd);
	VarWindow->setModal(true);

	getButton(ButtonSin)
		->enableChildButton()
		->registerChildButton("sin °", ButtonSind)
		->registerChildButton("arcsin", ButtonArcsin);

	getButton(ButtonCos)
		->enableChildButton()
		->registerChildButton("cos °", ButtonCosd)
		->registerChildButton("arccos", ButtonArccos);

	getButton(ButtonTan)
		->enableChildButton()
		->registerChildButton("tan °", ButtonTand)
		->registerChildButton("arctan", ButtonArctan);

	getButton(ButtonBackspace)
		->enableChildButton()
		->registerChildButton("清空", ButtonDeleteAll);

	getButton(ButtonSqrt)
		->enableChildButton()
		->registerChildButton("x√y", ButtonSqrtXY);

	getButton(ButtonLog)
		->enableChildButton()
		->registerChildButton("log10", ButtonLog10);
}

MainWindowUI::~MainWindowUI()
{
}

KeyboardButton * MainWindowUI::getButton(KbButtonName btnName)
{
	return Buttons[btnName];
}

void MainWindowUI::updateHistoryEntry(int currentIdx, int totalCount)
{
	if (currentIdx == -1)
	{
		ActionHistoryEntry->setText(QString::asprintf("历史记录 (%d) (&H)", totalCount));
	}
	else
	{
		ActionHistoryEntry->setText(QString::asprintf("历史记录 (%d/%d) (&H)", currentIdx + 1, totalCount));
	}
}

void MainWindowUI::addButton(const char *text, KbButtonName btnName, KbButtonType btnType, Qt::Key keyCode)
{
	Buttons[btnName] = new KeyboardButton(text, CentralWidget, btnName, btnType);
	if (keyCode != Qt::Key::Key_unknown)
	{
		KeyboardReflections[keyCode] = Buttons[btnName];
	}
}
