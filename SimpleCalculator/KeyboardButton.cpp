#include "KeyboardButton.h"
#include <QtWidgets/QPushButton>
KeyboardButton::KeyboardButton(const char *text, QWidget * parent, KbButtonName btnName, KbButtonType btnType)
	: QPushButton(text, parent)
{
	
	switch (btnType)
	{
	case Normal:
		this->setFont(QFont("Cambria", 15));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Digit:
		this->setFont(QFont("Microsoft YaHei UI", 16, QFont::DemiBold));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(250, 250, 250);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Op:
		this->setFont(QFont("Cambria", 15));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{color:white;background-color:rgb(0, 120, 215);}"
			"QPushButton:pressed{background-color:rgb(166, 216, 255);}"
		);
		break;
	}
	
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

KeyboardButton::~KeyboardButton()
{
}
