#pragma once
#include "SimpleFuncExpression.h"
class CosdExpression :
	public SimpleFuncExpression<CosdExpression>
{
public:
	CosdExpression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};
