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
	markEnsureCursorInScreen();
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

bool GlobalMgr::isEnsureCursorInScreen()
{
	return EnsureCursorInScreenFlag;
}

void GlobalMgr::markEnsureCursorInScreen()
{
	EnsureCursorInScreenFlag = true;
}

void GlobalMgr::clearEnsureCursorInScreenFlag()
{
	EnsureCursorInScreenFlag = false;
}

bool GlobalMgr::isRequireCompute()
{
	return RequireComputeFlag;
}

void GlobalMgr::markRequireCompute()
{
	RequireComputeFlag = true;
}

void GlobalMgr::clearRequireComputeFlag()
{
	RequireComputeFlag = false;
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
