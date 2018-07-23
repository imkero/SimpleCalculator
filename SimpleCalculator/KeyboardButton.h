#pragma once
#include <QtWidgets/QPushButton>
#include "Enums.h"
class KeyboardButton : public QPushButton
{
public:
	KeyboardButton(const char *text, QWidget *parent, KbButtonName btnName, KbButtonType btnType);
	~KeyboardButton();
};

