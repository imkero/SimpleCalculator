#include "ExpressionPaintUtil.h"
#include "GlobalMgr.h"

int ExpressionPaintUtil::ComputeBracketWidth(int height, bool isSub)
{
	return 6 + (isSub ? g_Data->Visual.PanelSubTokenWidth[RightBracket] : g_Data->Visual.PanelTokenWidth[RightBracket])
		* sqrt(static_cast<double>(height) / (isSub ? g_Data->Visual.PanelSubExprHeight.total() : g_Data->Visual.PanelExprHeight.total()));
}
