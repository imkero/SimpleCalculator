#include "Log10Expression.h"
#include <math.h>

const char *Log10Expression::FuncName = "log10";

Log10Expression::Log10Expression(ExpressionBase * parent) : SimpleFuncExpression(parent)
{
}

ComputeResult Log10Expression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;
	if (left.Value <= 0)
	{
		return ComputeResult(LnPowOutOfRange, getChild(0), 0, getChild(0)->getLength() - 1);
	}
	return ComputeResult(log10(left.Value));
}
