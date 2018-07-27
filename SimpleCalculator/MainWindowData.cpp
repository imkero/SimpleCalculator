#include "MainWindowData.h"

MainWindowData::MainWindowData()
{
	RootExpr = new HorizontalExpression(nullptr);
}

MainWindowData::~MainWindowData()
{
	if (RootExpr != nullptr)
	{
		delete RootExpr;
		RootExpr = nullptr;
	}
}
