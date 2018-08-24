#include "KeyboardButton.h"
#include <QtWidgets/QPushButton>
#include <QKeyEvent>
#include "GlobalMgr.h"

QFont KeyboardButton::NormalFont("Microsoft YaHei UI", 15);
QFont KeyboardButton::DigitFont("Microsoft YaHei UI", 18, QFont::DemiBold);
QColor KeyboardButton::ShiftDot(0, 120, 215);


KeyboardButton::KeyboardButton(const char *text, QWidget * parent, KbButtonName btnName, KbButtonType btnType)
	: QPushButton(text, parent), BtnName(btnName)
{
	switch (btnType)
	{
	case Normal:
		this->setFont(NormalFont);
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Digit:
		this->setFont(DigitFont);
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(250, 250, 250);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Op:
		this->setFont(NormalFont);
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{color:white;background-color:rgb(0, 120, 215);}"
			"QPushButton:pressed{background-color:rgb(166, 216, 255);}"
		);
		break;
	}
	
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	this->setMaximumHeight(70);
	connect(this, SIGNAL(clicked()), this, SLOT(eventOnClick()));
}

void KeyboardButton::paintEvent(QPaintEvent *event)
{
	QPushButton::paintEvent(event);
	if (ChildButtonCount > 0)
	{
		QPainter painter(this);
		QRect r;
		QRect buttonRect = rect();

		r.setSize(QSize(8, 8));
		r.moveTopRight(QPoint(buttonRect.width() - 4, 4));

		painter.fillRect(r, ShiftDot);
	}
}

void KeyboardButton::enableChildButton(int count)
{
	ChildButtonCount = count;
	ChildrenButtons = new KeyboardButton *[count];
}

void KeyboardButton::registerChildButton(int index, KeyboardButton *button)
{
	ChildrenButtons[index] = button;
}

KeyboardButton::~KeyboardButton()
{
	if (ChildrenButtons != nullptr)
	{
		delete[] ChildrenButtons;
	}
}

void KeyboardButton::eventOnClick()
{
	emit signalOnClick(BtnName);
}
