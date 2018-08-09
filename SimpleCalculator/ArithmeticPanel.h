#pragma once
#include <QtWidgets/QFrame>
#include "Singleton.h"
class ArithmeticPanel : public QFrame, public Singleton<ArithmeticPanel>
{
public:
	ArithmeticPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	~ArithmeticPanel();
};

