#include "MainWindowData.h"

MainWindowData::MainWindowData()
{
	Input.Focus = RootExpr = new HorizontalExpression();
	Input.CursorPos = 0;
}

MainWindowData::~MainWindowData()
{
}
