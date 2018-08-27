#include "ArithmeticPanel.h"
#include "GlobalMgr.h"
#include "Util.h"
#include <QtWidgets/QFrame>
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "CursorMgr.h"
#include "MainWindow.h"

void ArithmeticPanel::swapCursorBlinkStatus()
{
	CursorShowing = !CursorShowing;
	update();
}

void ArithmeticPanel::mouseMoveEvent(QMouseEvent *event)
{
	if (MouseEventTracking)
	{
		const QPointF & curMousePos = event->screenPos();
		g_Data->Visual.smartMoveExpr(curMousePos.x() - MouseEventPoint.x(), curMousePos.y() - MouseEventPoint.y());
		MouseEventPoint = curMousePos;
		event->accept();
	}
}

void ArithmeticPanel::mousePressEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::MouseButton::RightButton) != 0)
	{
		MouseEventPoint = event->screenPos();
		MouseEventTracking = true;
		event->accept();
	}
	else if ((event->button() & Qt::MouseButton::LeftButton) != 0)
	{
		if (g_Data->ReadOnlyShowing)
		{
			g_Data->setRootExpr(g_Data->getRootExpr()->clone()->as<HorizontalExpression>());
			g_Data->markExprDirty();
			g_Data->ReadOnlyShowing = false;
			startBlinking();
			repaint();
			MainWindow::getInstance()->historyUpdate();
		}
		QPoint pos(event->localPos().x() - 10, event->localPos().y() - 10);
		pos -= g_Data->Visual.ExprPosiiton;
		g_Data->markEnsureCursorInScreen();
		g_Data->getRootExpr()->mouseClick(pos);

	}
}

void ArithmeticPanel::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::MouseButton::RightButton) != 0)
	{
		MouseEventTracking = false;
		event->accept();
	}
}

void ArithmeticPanel::wheelEvent(QWheelEvent *event)
{
	if ((event->modifiers() & Qt::Modifier::CTRL) != 0)
		g_Data->Visual.smartMoveExpr(event->delta() < 0 ? -40 : 40, 0);
	else
		g_Data->Visual.smartMoveExpr(0, event->delta() < 0 ? -20 : 20);
}

ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent), Singleton<ArithmeticPanel>()
{
	CursorBlinkTimer = new QTimer(this);
	CursorBlinkTimer->setInterval(600);
	connect(CursorBlinkTimer, SIGNAL(timeout()), this, SLOT(swapCursorBlinkStatus()));

	CursorBlinkTimer->start();

	setCursor(Qt::IBeamCursor);
}

void ArithmeticPanel::paintEvent(QPaintEvent *)
{
	if (g_Data->isExprDirty())
	{
		g_Data->getRootExpr()->computeSize();
		g_Data->getRootExpr()->computePosition(AnchoredPoint());
		g_Data->clearExprDirtyFlag();
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

	// Draw Focus Highlight
	const Cursor & c = g_Data->Cursor.get();
	bool focusHighlightFlag = !g_Data->ReadOnlyShowing && c.available() && c.FocusdExpr->getParent() != nullptr && c.FocusdExpr->Rect.visible();
	if (focusHighlightFlag)
	{
		QRect exprRect = c.FocusdExpr->Rect.getRect();
		painter.fillRect(exprRect, g_Data->Visual.PanelFocusBgColor);
	}

	// Draw Error Highlight
	if (!g_Data->ExprResult.good() && g_Data->ExprResult.Expr != nullptr && g_Data->getRootExpr()->getLength() > 0)
	{
		int fromIdx = g_Data->ExprResult.IndexFrom;
		int toIdx = g_Data->ExprResult.IndexTo;
		if (fromIdx >= 0)
		{
			if (toIdx < fromIdx)
				toIdx = fromIdx;
			QRect rect = g_Data->ExprResult.Expr->rectBetween(fromIdx, toIdx);
			painter.fillRect(rect, g_Data->Visual.PanelErrorBgColor);
		}
	}

	// Draw Expr
	g_Data->getRootExpr()->draw(&painter);

	if (focusHighlightFlag)
	{
		QRect exprRect = c.FocusdExpr->Rect.getRect();
		painter.setPen(g_Data->Visual.PenFocusUnderline);
		painter.drawLine(QLine(exprRect.bottomLeft() + QPoint(1, 0), exprRect.bottomRight() + QPoint(1, 0)));
	}

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
	update();
}

void ArithmeticPanel::stopBlinking()
{
	CursorBlinkTimer->stop();
	CursorShowing = false;
}

void ArithmeticPanel::startBlinking()
{
	CursorShowing = true;
	CursorBlinkTimer->start();
}

ArithmeticPanel::~ArithmeticPanel()
{
}
