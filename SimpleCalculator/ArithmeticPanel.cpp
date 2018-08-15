#include "ArithmeticPanel.h"
#include "GlobalMgr.h"
#include "Util.h"
#include <QtWidgets/QFrame>
#include <QPainter>
#include <QDebug>
#include <iostream>
#include "CursorMgr.h"

void ArithmeticPanel::swapCursorBlinkStatus()
{
	CursorShowing = !CursorShowing;
	update();
}

void ArithmeticPanel::mouseMoveEvent(QMouseEvent * event)
{
	if (MouseEventTracking)
	{
		const QPointF & curMousePos = event->screenPos();
		
		QPoint exprPosOld = g_Data->Visual.ExprPosiiton;

		g_Data->Visual.moveExpr(curMousePos.x() - MouseEventPoint.x(), curMousePos.y() - MouseEventPoint.y());		
		g_Data->Visual.exprPosLimit();

		if (exprPosOld != g_Data->Visual.ExprPosiiton)
		{
			g_Data->repaintExpr();
		}
		
		MouseEventPoint = curMousePos;
		event->accept();
	}
}

void ArithmeticPanel::mousePressEvent(QMouseEvent * event)
{
	if ((event->button() & Qt::MouseButton::RightButton) != 0)
	{
		MouseEventPoint = event->screenPos();
		MouseEventTracking = true;
		event->accept();
	}
}

void ArithmeticPanel::mouseReleaseEvent(QMouseEvent * event)
{
	if ((event->button() & Qt::MouseButton::RightButton) != 0)
	{
		MouseEventTracking = false;
		event->accept();
	}
}

ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent), Singleton<ArithmeticPanel>()
{
	CursorBlinkTimer = new QTimer(this);
	CursorBlinkTimer->setInterval(600);
	connect(CursorBlinkTimer, SIGNAL(timeout()), this, SLOT(swapCursorBlinkStatus()));

	CursorBlinkTimer->start();
}

void ArithmeticPanel::paintEvent(QPaintEvent *)
{
	if (g_Data->isExprDirty())
	{
		g_Data->RootExpr->computeSize();
		g_Data->RootExpr->computePosition(AnchoredPoint());
		g_Data->clearExprDirtyFlag();
	}

	if (g_Data->isRequireCompute())
	{
		g_Data->updateResult();
		g_Data->clearRequireComputeFlag();
	}

	QPainter painter(this);
	painter.save();
	
	// Saved space for expr xy move
	painter.translate(QPoint(10, 10));

	// ExprPosition
	g_Data->Visual.updateVisibleRectPos();
	g_Data->Visual.updateVisibleRectSize(painter.viewport().size());

	if (g_Data->isEnsureCursorInScreen())
	{
		g_Data->Visual.ensureCursorInScreen();
		g_Data->clearEnsureCursorInScreenFlag();
	}
	g_Data->Visual.exprPosLimit();

	painter.translate(g_Data->Visual.ExprPosiiton);

	// Draw Focus Background
	const Cursor & c = g_Data->Cursor.get();
	if (c.available() && c.FocusdExpr->getParent() != nullptr && c.FocusdExpr->Rect.visible())
	{
		QRect exprRect = c.FocusdExpr->Rect.getRect();
		painter.fillRect(exprRect, g_Data->Visual.PanelFocusBgColor);

		painter.setPen(g_Data->Visual.PenFocusUnderline);
		painter.drawLine(QLine(exprRect.bottomLeft() + QPoint(1, 0), exprRect.bottomRight() + QPoint(1, 0)));
	}

	// Draw Expr
	
	g_Data->RootExpr->draw(&painter);

	// Draw Cursor
	if (CursorShowing)
		painter.fillRect(g_Data->Cursor.getRect(), g_Data->Visual.PanelCursorColor);

	painter.restore();
}

void ArithmeticPanel::brightenCursor()
{
	CursorBlinkTimer->stop();
	CursorShowing = true;
	CursorBlinkTimer->start();
}

ArithmeticPanel::~ArithmeticPanel()
{
}
