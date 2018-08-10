#include "ArithmeticPanel.h"
#include "GlobalMgr.h"
#include "Util.h"
#include <QtWidgets/QFrame>
#include <QPainter>
#include <QDebug>
#include <iostream>
#include "CursorMgr.h"

ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent), Singleton<ArithmeticPanel>()
{
	
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
	
	// saved space for expr xy move
	painter.translate(QPoint(10, 10));

	// ExprPosition offset
	g_Data->Visual.updateVisibleRectPos();
	g_Data->Visual.updateVisibleRectSize(painter.viewport().size());

	if (g_Data->isEnsureCursorShowing())
	{
		g_Data->Visual.ensureCursorInScreen();
		g_Data->clearEnsureCursorShowingFlag();
	}
	g_Data->Visual.exprPosLimit();

	// Draw Expr
	painter.translate(g_Data->Visual.ExprPosiiton);
	g_Data->RootExpr->draw(&painter);

	painter.fillRect(g_Data->Cursor.getRect(), g_Data->Visual.PanelCursorColor);

	painter.restore();
}

ArithmeticPanel::~ArithmeticPanel()
{
}
