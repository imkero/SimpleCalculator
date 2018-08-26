#include "TanExpression.h"
#include "Util.h"

const char *TanExpression::FuncName = "tan";

TanExpression::TanExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult TanExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = tan(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * TanExpression::clone() const
{
	return new TanExpression(*this);
}
