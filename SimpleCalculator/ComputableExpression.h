#pragma once
#include "ExpressionBase.h"
class ComputableExpression :
	public ExpressionBase
{
public:
	ComputableExpression(ExpressionType);
	~ComputableExpression();

	virtual double computeValue() = 0;
};

