#pragma once
#include "SimpleFuncExpression.h"
class ArcsinExpression :
	public SimpleFuncExpression<ArcsinExpression>
{
public:
	ArcsinExpression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};
