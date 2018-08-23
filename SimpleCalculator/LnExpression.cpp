#include "LnExpression.h"
#include <math.h>
const char *LnExpression::FuncName = "ln";

LnExpression::LnExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult LnExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	if (!left.good())
		return left;
	if (left.Value <= 0)
	{
		return ComputeResult(LnPowOutOfRange, ChildrenArray[0], 0, ChildrenArray[0]->getLength() - 1);
	}
	return ComputeResult(log(left.Value));
}
