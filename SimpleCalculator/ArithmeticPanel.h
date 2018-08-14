#pragma once
#include <QtWidgets/QFrame>
#include <QTimer>
#include <QPointF>
#include <QMouseEvent>
#include "Singleton.h"

class ArithmeticPanel : public QFrame, public Singleton<ArithmeticPanel>
{
	Q_OBJECT
private:
	QTimer * CursorBlinkTimer = nullptr;
	bool CursorShowing = true;
	QPointF MouseEventPoint;
	bool MouseEventTracking = false;

private slots:
	void swapCursorBlinkStatus();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

public:
	ArithmeticPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void brightenCursor();
	~ArithmeticPanel();
};

