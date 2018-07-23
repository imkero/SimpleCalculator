#include "KeyboardButton.h"
#include <QtWidgets/QPushButton>
<<<<<<< HEAD
#include "Const.h"

=======
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
KeyboardButton::KeyboardButton(const char *text, QWidget * parent, KbButtonName btnName, KbButtonType btnType)
	: QPushButton(text, parent)
{
	switch (btnType)
	{
	case Normal:
		this->setFont(QFont(Const::FONT_ALPHA, 15));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Digit:
		this->setFont(QFont(Const::FONT_DIGHT, 16, QFont::DemiBold));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(250, 250, 250);border:none;}"
			"QPushButton:hover{background-color:rgb(209, 209, 209);}"
			"QPushButton:pressed{background-color:rgb(187, 187, 187);}"
		);
		break;
	case Op:
		this->setFont(QFont(Const::FONT_ALPHA, 15));
		this->setStyleSheet(
			"QPushButton{color:black;background-color:rgb(240, 240, 240);border:none;}"
			"QPushButton:hover{color:white;background-color:rgb(0, 120, 215);}"
			"QPushButton:pressed{background-color:rgb(166, 216, 255);}"
		);
		break;
	}
	
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
<<<<<<< HEAD
	connect(this, SIGNAL(clicked()), this, SLOT(eventOnClick()));
=======
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
}

KeyboardButton::~KeyboardButton()
{
}
