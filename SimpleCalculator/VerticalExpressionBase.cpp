#include "VerticalExpressionBase.h"


VerticalExpressionBase::VerticalExpressionBase(ExpressionBase * parent, int childrenCount)
	: ExpressionBase(Vertical, parent)
{
	ChildrenArray = new HorizontalExpression *[childrenCount];
}

void VerticalExpressionBase::remove(ExpressionBase *, bool moveCursor)
{
}

VerticalExpressionBase::~VerticalExpressionBase()
{
	if (ChildrenArray != nullptr)
	{
		delete[] ChildrenArray;
		ChildrenArray = nullptr;
	}	
}
