#pragma once
#include <QtWidgets/QPushButton>
#include <QFont>
#include "Enums.h"
class KeyboardButton : public QPushButton
{
	Q_OBJECT
private:
	static QFont NormalFont;
	static QFont DigitFont;
	KbButtonName BtnName;
	
private slots:
	void eventOnClick();

signals:
	void signalOnClick(KbButtonName);
	
public:
	KeyboardButton(const char *text, QWidget *parent, KbButtonName btnName, KbButtonType btnType);
	~KeyboardButton();
};

