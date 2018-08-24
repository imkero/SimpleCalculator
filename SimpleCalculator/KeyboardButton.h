#pragma once
#include <QtWidgets/QPushButton>
#include <QFont>
#include "Enums.h"
class KeyboardButton : public QPushButton
{
	Q_OBJECT
protected:
	static QFont NormalFont;
	static QFont DigitFont;
	static QColor ShiftDot;

	KbButtonName BtnName;
	int ChildButtonCount = 0;
	KeyboardButton **ChildrenButtons = nullptr;

	void paintEvent(QPaintEvent *);

protected slots:
	void eventOnClick();

signals:
	void signalOnClick(KbButtonName);
	
public:
	KeyboardButton(const char *text, QWidget *parent, KbButtonName btnName, KbButtonType btnType);
	~KeyboardButton();

	void enableChildButton(int count);
	void registerChildButton(int index, KeyboardButton*);
};

