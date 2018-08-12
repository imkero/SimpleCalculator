#pragma once
#include <QtWidgets/QFrame>
#include <QTimer>
#include "Singleton.h"
class ArithmeticPanel : public QFrame, public Singleton<ArithmeticPanel>
{
	Q_OBJECT
private:
	QTimer * CursorBlinkTimer = nullptr;
	bool CursorShowing = true;

private slots:
	void swapCursorBlinkStatus();

public:
	ArithmeticPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void brightenCursor();
	~ArithmeticPanel();
};

