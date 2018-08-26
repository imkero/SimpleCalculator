#pragma once
#include "SimpleFuncExpression.h"

class SinExpression :
	public SimpleFuncExpression<SinExpression>
{
public:
	SinExpression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};
