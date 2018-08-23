#pragma once
#include "SimpleFuncExpression.h"

class LnExpression :
	public SimpleFuncExpression<LnExpression>
{
public:
	LnExpression(ExpressionBase * parent);
	ComputeResult computeValue();
};
