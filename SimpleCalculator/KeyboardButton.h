#pragma once
#include <QtWidgets/QPushButton>
#include "Enums.h"
class KeyboardButton : public QPushButton
{
	Q_OBJECT
private:
	KbButtonName BtnName;
	
private slots:
	void eventOnClick();

signals:
	void signalOnClick(KbButtonName);
	
public:
	KeyboardButton(const char *text, QWidget *parent, KbButtonName btnName, KbButtonType btnType);
	~KeyboardButton();

};

