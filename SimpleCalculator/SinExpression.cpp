#include "SinExpression.h"
#include "Util.h"

const char *SinExpression::FuncName = "sin";

SinExpression::SinExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult SinExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = sin(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * SinExpression::clone() const
{
	return new SinExpression(*this);
}
