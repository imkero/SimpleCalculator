#pragma once
#include "SimpleFuncExpression.h"
class ArctanExpression :
	public SimpleFuncExpression<ArctanExpression>
{
public:
	ArctanExpression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};
