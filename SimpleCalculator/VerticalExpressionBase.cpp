#include "VerticalExpressionBase.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"

VerticalExpressionBase::VerticalExpressionBase(ExpressionBase * parent, int childrenCount)
	: ExpressionBase(Vertical, parent), ChildrenCount(childrenCount)
{
	ChildrenArray = new HorizontalExpression *[childrenCount];
	IsSubExpr = Parent != nullptr && parent->Type == Horizontal && parent->as<HorizontalExpression>()->getIsSubExpr();
}

VerticalExpressionBase::VerticalExpressionBase(const VerticalExpressionBase &expr) : ExpressionBase(expr)
{
	ChildrenArray = new HorizontalExpression *[expr.ChildrenCount];
	ChildrenCount = expr.ChildrenCount;
	for (int i = 0; i < ChildrenCount; i++)
	{
		ChildrenArray[i] = static_cast<HorizontalExpression *>(expr.ChildrenArray[i]->clone());
		ChildrenArray[i]->setParent(this);
	}
}

void VerticalExpressionBase::remove(ExpressionBase *expr, bool moveCursor)
{
	auto hExpr = expr->as<HorizontalExpression>();
	if (getChild(0) == hExpr)
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

HorizontalExpression * VerticalExpressionBase::getChild(int index)
{
	return ChildrenArray[index];
}

ValidateResult VerticalExpressionBase::validate()
{
	ValidateResult result;
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

void VerticalExpressionBase::setParent(ExpressionBase *newParent)
{
	IsSubExpr = newParent != nullptr && newParent->Type == Horizontal && newParent->as<HorizontalExpression>()->getIsSubExpr();
	ExpressionBase::setParent(newParent);
}
