#pragma once
#include "SimpleFuncExpression.h"

class Log10Expression :
	public SimpleFuncExpression<Log10Expression>
{
public:
	Log10Expression(ExpressionBase * parent);
	ComputeResult computeValue();
	ExpressionBase *clone() const;
};
