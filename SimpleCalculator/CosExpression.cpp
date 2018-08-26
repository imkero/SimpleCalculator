#include "CosExpression.h"
#include "Util.h"

const char *CosExpression::FuncName = "cos";

CosExpression::CosExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult CosExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = cos(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * CosExpression::clone() const
{
	return new CosExpression(*this);
}
