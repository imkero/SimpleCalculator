#pragma once
#include "HorizontalExpression.h"
class MainWindowData
{
public:
	MainWindowData();
	HorizontalExpression *RootExpr = nullptr;
	~MainWindowData();
};

