#pragma once
#include "SimpleFuncExpression.h"
class ArccosExpression :
	public SimpleFuncExpression<ArccosExpression>
{
public:
	ArccosExpression(ExpressionBase * parent);
	ComputeResult computeValue();
};
