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
	if (ChildButtonMenu != nullptr)
	{
		QPainter painter(this);
		QRect r;
		QRect buttonRect = rect();

		r.setSize(QSize(8, 8));
		r.moveTopRight(QPoint(buttonRect.width() - 4, 4));

		painter.fillRect(r, ShiftDot);
	}
}

void KeyboardButton::contextMenuEvent(QContextMenuEvent * e)
{
	if (ChildButtonMenu != nullptr)
	{
		ChildButtonMenu->exec(e->globalPos());
		update();
	}
	e->accept();
}

void KeyboardButton::eventChildButtonClick(QAction *action)
{
	KbButtonName btnName = static_cast<KbButtonName>(action->data().toInt());
	emit signalOnClick(btnName);
}

KeyboardButton *KeyboardButton::enableChildButton()
{
	ChildButtonMenu = new QMenu(this);
	ChildButtonMenu->setStyleSheet(
	"QMenu {"
		"background-color: rgb(250, 250, 250); "
		"border: 1px solid white; "
		"font-family: 'Microsoft YaHei UI'; "
		"font-size: 20px; "
	"}"
	"QMenu::item {"
		"background-color: transparent;"
		"padding: 8px 24px;"
		"border-bottom:1px solid #DBDBDB;"
	"}"
	"QMenu::item:selected {"
		"background-color: rgb(209, 209, 209);"
	"}");
	connect(ChildButtonMenu, SIGNAL(triggered(QAction *)), this, SLOT(eventChildButtonClick(QAction *)));
	return this;
}

KeyboardButton *KeyboardButton::registerChildButton(const QString &text, KbButtonName btnName)
{
	QAction *action = ChildButtonMenu->addAction(text);
	action->setData(btnName);
	return this;
}


KeyboardButton::~KeyboardButton()
{
}

void KeyboardButton::eventOnClick()
{
	emit signalOnClick(BtnName);
}
