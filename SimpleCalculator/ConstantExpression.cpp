#include "ConstantExpression.h"


ConstantExpression::ConstantExpression(double value) : ExpressionBase(Constant), Value(value)
{
}

void ConstantExpression::setValue(double value)
{
	Value = value;
}

double ConstantExpression::getValue()
{
	return Value;
}

double ConstantExpression::calcValue()
{
	return Value;
}

void ConstantExpression::calcRect()
{
}


ConstantExpression::~ConstantExpression()
{
}
