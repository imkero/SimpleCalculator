#include "SindExpression.h"
#include "Util.h"

const char *SindExpression::FuncName = "sind";

SindExpression::SindExpression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult SindExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	CompType result = sin(degToRad(left.Value));
	if (isNaN(result))
		return ComputeResult(MathError, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(result);
}
