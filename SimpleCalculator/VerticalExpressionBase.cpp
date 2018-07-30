#include "VerticalExpressionBase.h"


VerticalExpressionBase::VerticalExpressionBase(ExpressionBase * parent, int childrenCount)
	: ExpressionBase(Vertical, parent)
{
	ChildrenArray = new HorizontalExpression *[childrenCount];
}

VerticalExpressionBase::~VerticalExpressionBase()
{
	if (ChildrenArray != nullptr)
	{
		delete[] ChildrenArray;
		ChildrenArray = nullptr;
	}	
}
