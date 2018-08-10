#include "GlobalMgr.h"
#include <iostream>
#include "ResultPanel.h"
#include <QPoint>
GlobalMgr *g_Data = nullptr;

GlobalMgr::GlobalMgr()
{
	g_Data = this;

	Visual.updateParamCache();

	RootExpr = new HorizontalExpression(nullptr);
	Cursor.set(RootExpr, 0);

	markExprDirty();
	markEnsureCursorShowing();
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

bool GlobalMgr::isEnsureCursorShowing()
{
	return EnsureCursorShowing;
}

void GlobalMgr::markEnsureCursorShowing()
{
	EnsureCursorShowing = true;
}

void GlobalMgr::clearEnsureCursorShowingFlag()
{
	EnsureCursorShowing = false;
}

bool GlobalMgr::isRequireCompute()
{
	return RequireCompute;
}

void GlobalMgr::markRequireCompute()
{
	RequireCompute = true;
}

void GlobalMgr::clearRequireComputeFlag()
{
	RequireCompute = false;
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
