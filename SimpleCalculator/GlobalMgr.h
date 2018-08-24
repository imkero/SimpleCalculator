#pragma once
#include <QPoint>
#include "HorizontalExpression.h"
#include "CursorMgr.h"
#include "VisualMgr.h"
#include "VariableMgr.h"
#include "ArithmeticPanel.h"
#include "ProgramSettings.h"

class GlobalMgr
{
private:
	GlobalMgr();
	bool ExprDirtyFlag = false;
	bool EnsureCursorInScreenFlag = false;
	bool RequireComputeFlag = false;
public:
	static void init();
	HorizontalExpression *RootExpr = nullptr;

	CursorMgr Cursor;
	VisualMgr Visual;
	VariableMgr Variable;

	ComputeResult ExprResult;

	ProgramSettings Config;

	bool isExprDirty();
	void markExprDirty();
	void clearExprDirtyFlag();

	bool isEnsureCursorInScreen();
	void markEnsureCursorInScreen();
	void clearEnsureCursorInScreenFlag();

	bool isRequireCompute();
	void markRequireCompute();
	void clearRequireComputeFlag();

	void repaintExpr();
	void updateResult();
	void clearResult();
	~GlobalMgr();
};

extern GlobalMgr *g_Data;