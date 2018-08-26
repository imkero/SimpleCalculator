#include "ArcsinExpression.h"
#include "Util.h"

const char *ArcsinExpression::FuncName = "arcsin";

ArcsinExpression::ArcsinExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult ArcsinExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = asin(left.Value);
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}
