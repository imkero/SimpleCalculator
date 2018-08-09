#include "KeyboardButton.h"
#include <QtWidgets/QPushButton>
#include "GlobalMgr.h"

QFont KeyboardButton::NormalFont("Microsoft YaHei UI", 15);
QFont KeyboardButton::DigitFont("Microsoft YaHei UI", 18, QFont::DemiBold);

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

	connect(this, SIGNAL(clicked()), this, SLOT(eventOnClick()));
}

KeyboardButton::~KeyboardButton()
{
}

void KeyboardButton::eventOnClick()
{
	emit signalOnClick(BtnName);
}
