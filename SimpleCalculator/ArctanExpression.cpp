#include "ArctanExpression.h"
#include "Util.h"

const char *ArctanExpression::FuncName = "arctan";

ArctanExpression::ArctanExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult ArctanExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = atan(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * ArctanExpression::clone() const
{
	return new ArctanExpression(*this);
}
