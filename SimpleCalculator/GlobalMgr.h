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
	HorizontalExpression *RootExpr = nullptr;

public:
	static void init();

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

	HorizontalExpression *getRootExpr() const;
	void setRootExpr(HorizontalExpression *);

	void repaintExpr();
	void updateResult();
	void setResult(ComputeResult);
	void clearResult();
	~GlobalMgr();
};

extern GlobalMgr *g_Data;