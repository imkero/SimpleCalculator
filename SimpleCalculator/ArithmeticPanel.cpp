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

ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent), Singleton<ArithmeticPanel>()
{
	CursorBlinkTimer = new QTimer(this);
	CursorBlinkTimer->setInterval(500);
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

	if (g_Data->isEnsureCursorShowing())
	{
		g_Data->Visual.ensureCursorInScreen();
		g_Data->clearEnsureCursorShowingFlag();
	}
	g_Data->Visual.exprPosLimit();

	// Draw Focus Background


	// Draw Expr
	painter.translate(g_Data->Visual.ExprPosiiton);
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
