#pragma once
#include "SimpleFuncExpression.h"
class TandExpression :
	public SimpleFuncExpression<TandExpression>
{
public:
	TandExpression(ExpressionBase * parent);
	ComputeResult computeValue();
};
