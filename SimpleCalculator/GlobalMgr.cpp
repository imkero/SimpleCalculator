#include "GlobalMgr.h"
#include <iostream>

GlobalMgr *g_Data = nullptr;

GlobalMgr::GlobalMgr()
{
	RootExpr = new HorizontalExpression(nullptr);
	Cursor.set(RootExpr, 0);
}

void GlobalMgr::init()
{
	if (g_Data == nullptr)
	{
		g_Data = new GlobalMgr();
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
	ExprPanel->update();
}

void GlobalMgr::registerExprPanel(ArithmeticPanel *panel)
{
	ExprPanel = panel;
}

GlobalMgr::~GlobalMgr()
{
	if (RootExpr != nullptr)
	{
		delete RootExpr;
		RootExpr = nullptr;
	}
}
