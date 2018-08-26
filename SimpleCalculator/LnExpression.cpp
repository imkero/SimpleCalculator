#include "LnExpression.h"
#include <math.h>
const char *LnExpression::FuncName = "ln";

LnExpression::LnExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult LnExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	if (left.Value <= 0)
	{
		return ComputeResult(LnPowOutOfRange, getChild(0), 0, getChild(0)->getLength() - 1);
	}
	return ComputeResult(log(left.Value));
}

ExpressionBase * LnExpression::clone() const
{
	return new LnExpression(*this);
}
