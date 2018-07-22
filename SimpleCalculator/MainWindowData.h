#pragma once
#include "HorizontalExpression.h"
#include "InputMgr.h"

class MainWindowData
{
public:
	MainWindowData();
	~MainWindowData();

	HorizontalExpression *RootExpr;
	InputMgr Input;
};

