#pragma once
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>
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
	QMenu *ChildButtonMenu = nullptr;

	void paintEvent(QPaintEvent *);
	void contextMenuEvent(QContextMenuEvent * e);

protected slots:
	void eventChildButtonClick(QAction *);
	void eventOnClick();

signals:
	void signalOnClick(KbButtonName);
	
public:
	KeyboardButton(const char *text, QWidget *parent, KbButtonName btnName, KbButtonType btnType);
	~KeyboardButton();

	KeyboardButton *enableChildButton();
	KeyboardButton *registerChildButton(const QString &text, KbButtonName btnName);

};

