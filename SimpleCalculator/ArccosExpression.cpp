#include "ArccosExpression.h"
#include "Util.h"

const char *ArccosExpression::FuncName = "arccos";

ArccosExpression::ArccosExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult ArccosExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = acos(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * ArccosExpression::clone() const
{
	return new ArccosExpression(*this);
}
