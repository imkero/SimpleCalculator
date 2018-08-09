#include "GlobalMgr.h"
#include <iostream>
#include "ResultPanel.h"
#include <QPoint>
GlobalMgr *g_Data = nullptr;

GlobalMgr::GlobalMgr()
{
	g_Data = this;
	Visual.updateParamCache();
	Visual.ExprPosiiton = QPoint(0, Visual.PanelExprHeight.Ascent);
	RootExpr = new HorizontalExpression(nullptr);
	Cursor.set(RootExpr, 0);
	markExprDirty();
}

void GlobalMgr::init()
{
	if (g_Data == nullptr)
	{
		new GlobalMgr();
	}
}

bool GlobalMgr::isExprDirty()
{
	return ExprDirtyFlag;
}

void GlobalMgr::markExprDirty()
{
	ExprDirtyFlag = true;
}

void GlobalMgr::clearExprDirtyFlag()
{
	ExprDirtyFlag = false;
}

void GlobalMgr::repaintExpr()
{
	ArithmeticPanel::getInstance()->update();
}

void GlobalMgr::updateResult()
{
	ExprResult = g_Data->RootExpr->computeValue();
	ResultPanel::getInstance()->showResult(ExprResult);
}

GlobalMgr::~GlobalMgr()
{
	if (RootExpr != nullptr)
	{
		delete RootExpr;
		RootExpr = nullptr;
	}
}
