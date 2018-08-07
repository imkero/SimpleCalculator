#pragma once
#include "HorizontalExpression.h"
#include "CursorMgr.h"
#include "VisualMgr.h"
#include <QPoint>
#include "ArithmeticPanel.h"

class GlobalMgr
{
private:
	GlobalMgr();
	ArithmeticPanel *ExprPanel;
	bool ExprDirtyFlag = false;
public:
	static void init();
	HorizontalExpression *RootExpr = nullptr;
	CursorMgr Cursor;
	VisualMgr Visual;

	double ExprResult = NAN;

	bool isExprDirty();
	void markExprDirty();
	void clearExprDirtyFlag();

	void repaintExpr();
	void registerExprPanel(ArithmeticPanel *);
	~GlobalMgr();
};

extern GlobalMgr *g_Data;