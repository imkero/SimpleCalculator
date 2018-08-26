#pragma once
#include <QPoint>
#include "HorizontalExpression.h"
#include "CursorMgr.h"
#include "VisualMgr.h"
#include "HistoryMgr.h"
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
	ComputeResult ExprResult;

	bool ReadOnlyShowing = false;

	CursorMgr Cursor;
	VisualMgr Visual;
	VariableMgr Variable;
	HistoryMgr History;

	ProgramSettings Config;

	bool isExprDirty();
	void markExprDirty();
	void clearExprDirtyFlag();

	bool isEnsureCursorInScreen();
	void markEnsureCursorInScreen();
	void clearEnsureCursorInScreenFlag();

	void doCompute();

	void repaintExpr();
	void updateResult();
	void clearResult();
	~GlobalMgr();
};

extern GlobalMgr *g_Data;