#include "VerticalExpressionBase.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"
#include <qdebug.h>

VerticalExpressionBase::VerticalExpressionBase(ExpressionBase * parent, int childrenCount)
	: ExpressionBase(Vertical, parent), ChildrenCount(childrenCount)
{
	ChildrenArray = new HorizontalExpression *[childrenCount];
	IsSubExpr = parent->Type == Horizontal && parent->as<HorizontalExpression>()->getIsSubExpr();
}

void VerticalExpressionBase::remove(ExpressionBase *expr, bool moveCursor)
{
	auto hExpr = expr->as<HorizontalExpression>();
	if (ChildrenArray[0] == hExpr)
	{
		Parent->remove(this, moveCursor);
	}
	else
	{
		if (moveCursor)
		{
			g_Data->Cursor.moveLeft();
		}
	}
}

int VerticalExpressionBase::findChildPosition(ExpressionBase *expr)
{
	auto hExpr = expr->as<HorizontalExpression>();
	for (auto i = ChildrenCount - 1; i >= 0; i--)
	{
		if (ChildrenArray[i] == hExpr)
		{
			return i;
		}
	}
	return -1;
}

int VerticalExpressionBase::getLength()
{
	return ChildrenCount;
}

ValidateResult VerticalExpressionBase::validate()
{
	ValidateResult result = ChildrenArray[0]->validate();
	for (int i = 0; i < ChildrenCount; i++)
	{
		result = ChildrenArray[i]->validate();
		if (!result.good())
			break;
	}
	return result;
}


VerticalExpressionBase::~VerticalExpressionBase()
{
	if (ChildrenArray != nullptr)
	{
		delete[] ChildrenArray;
		ChildrenArray = nullptr;
	}	
}
