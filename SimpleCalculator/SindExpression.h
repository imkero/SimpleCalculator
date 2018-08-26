#pragma once
#include "SimpleFuncExpression.h"
class SindExpression :
	public SimpleFuncExpression<SindExpression>
{
public:
	SindExpression(ExpressionBase * parent);
	ComputeResult computeValue();
};
