#pragma once
#include "HorizontalExpression.h"
#include "CursorMgr.h"

class MainWindowData
{
public:
	MainWindowData();
	HorizontalExpression *RootExpr = nullptr;
	CursorMgr Cursor;
	~MainWindowData();
};

