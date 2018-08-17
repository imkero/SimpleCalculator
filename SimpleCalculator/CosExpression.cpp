#include "CosExpression.h"

const char *CosExpression::FuncName = "cos";

CosExpression::CosExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult CosExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	if (!left.good())
		return left;

	return ComputeResult(cos(left.Value));
}
