#pragma once
#include "ExpressionBase.h"
class ConstantExpression :
	public ExpressionBase
{
private:
	double Value;
public:
	ConstantExpression(double value = 0);
	void setValue(double value);
	double getValue();
	double calcValue();
	void calcRect();
	~ConstantExpression();
};

