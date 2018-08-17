#include "SinExpression.h"

const char *SinExpression::FuncName = "sin";

SinExpression::SinExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult SinExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	if (!left.good())
		return left;

	return ComputeResult(sin(left.Value));
}
