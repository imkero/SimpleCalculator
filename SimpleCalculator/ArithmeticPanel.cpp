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

	QPainter painter(this);
	painter.save();
	
	// saved space for expr xy move
	QRect viewport = painter.viewport();
	viewport.adjust(10, 10, -10, -10);
	painter.setViewport(viewport);

	// ExprPosition offset
	painter.translate(g_Data->Visual.ExprPosiiton);

	// Draw Expr
	g_Data->Visual.VisibleRect.setTopLeft(-g_Data->Visual.ExprPosiiton);
	g_Data->Visual.VisibleRect.setSize(painter.viewport().size());
	g_Data->RootExpr->draw(&painter);

	painter.fillRect(g_Data->Cursor.getRect(), QColor(0, 0, 0));

	painter.restore();
}

ArithmeticPanel::~ArithmeticPanel()
{
}
