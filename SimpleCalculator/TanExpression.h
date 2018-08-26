#pragma once
#include "SimpleFuncExpression.h"
class TanExpression :
	public SimpleFuncExpression<TanExpression>
{
public:
	TanExpression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};

