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
	Cursor.setWithoutBrighten(RootExpr, 0);

	Config.readFromFile();

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

void GlobalMgr::doCompute()
{
	updateResult();
	ResultPanel::getInstance()->update();
}

HorizontalExpression * GlobalMgr::getRootExpr() const
{
	return RootExpr;
}

void GlobalMgr::setRootExpr(HorizontalExpression *expr)
{
	if (!History.contains(RootExpr))
	{
		delete RootExpr;
		clearResult();
	}
	RootExpr = expr;
}

void GlobalMgr::repaintExpr()
{
	ArithmeticPanel::getInstance()->update();
}

void GlobalMgr::updateResult()
{
	ExprResult = RootExpr->computeValue();
	if (RootExpr->getLength() == 0)
		ResultPanel::getInstance()->hideResult();
	else
		ResultPanel::getInstance()->showResult(ExprResult);
}

void GlobalMgr::setResult(ComputeResult result)
{
	ExprResult = result;
	if (RootExpr->getLength() == 0)
		ResultPanel::getInstance()->hideResult();
	else
		ResultPanel::getInstance()->showResult(ExprResult);
}

void GlobalMgr::clearResult()
{
	ExprResult.Value = 0;
	ExprResult.Expr = nullptr;
	ExprResult.Error = ComputeErrorType::Success;
	ResultPanel::getInstance()->hideResult();
}

GlobalMgr::~GlobalMgr()
{
	if (RootExpr != nullptr)
	{
		if (!History.contains(RootExpr))
		{
			delete RootExpr;
			RootExpr = nullptr;
		}
	}
}
