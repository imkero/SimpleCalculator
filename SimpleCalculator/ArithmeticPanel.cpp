#include "ArithmeticPanel.h"
#include "GlobalMgr.h"
#include "Util.h"
#include <QtWidgets/QFrame>
#include <QPainter>
#include <iostream>

ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent)
{
	g_Data->registerExprPanel(this);
}

void ArithmeticPanel::paintEvent(QPaintEvent *)
{
	if (g_Data->isExprDirty())
	{
		g_Data->RootExpr->computeSize();
		g_Data->RootExpr->computePosition();
		g_Data->clearExprDirtyFlag();
	}

	QPainter painter(this);
	QRect panelRect = this->rect();

	// Draw Expr
	g_Data->Visual.VisibleRect.setTopLeft(-g_Data->Visual.ExprPosiiton);
	g_Data->Visual.VisibleRect.setSize(panelRect.size());
	g_Data->RootExpr->draw(&painter);

	// Draw Result
	if (!isNaN(g_Data->ExprResult))
	{
		char buffer[64];
		sprintf(buffer, "%f", g_Data->ExprResult);
		painter.setPen(g_Data->Visual.PanelMainColor);
		painter.setFont(g_Data->Visual.PanelResultFont);
		painter.drawText(0, 0, panelRect.width() - 1, panelRect.height() - 1,
			Qt::AlignBottom | Qt::AlignRight, buffer);
	}
	
}

ArithmeticPanel::~ArithmeticPanel()
{
}
