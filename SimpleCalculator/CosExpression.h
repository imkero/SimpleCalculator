#pragma once
#include "SimpleFuncExpression.h"

class CosExpression :
	public SimpleFuncExpression<CosExpression>
{
public:
	CosExpression(ExpressionBase * parent);
	ComputeResult computeValue();
};
