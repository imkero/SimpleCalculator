#include "CosdExpression.h"
#include "Util.h"

const char *CosdExpression::FuncName = "cosd";

CosdExpression::CosdExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult CosdExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = cos(degToRad(left.Value));
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}

ExpressionBase * CosdExpression::clone() const
{
	return new CosdExpression(*this);
}
