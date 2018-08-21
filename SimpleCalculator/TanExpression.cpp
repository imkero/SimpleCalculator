#include "TanExpression.h"

const char *TanExpression::FuncName = "tan";

TanExpression::TanExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult TanExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	if (!left.good())
		return left;

	return ComputeResult(tan(left.Value));
}
