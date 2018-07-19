#pragma once
#include <QtWidgets/QFrame>

class ArithmeticPanel : public QFrame
{
public:
	ArithmeticPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	~ArithmeticPanel();
};

