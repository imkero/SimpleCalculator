#include "ExpressionOperator.h"
#include "Enums.h"
ExpressionOperator::ExpressionOperator(ExpressionOp op) : ExpressionBase(ExpressionType::Operator), Operator(op)
{
}

int ExpressionOperator::getPriority()
{
	switch (Operator)
	{
	case Add:
	case Sub:
		return 1;
	case Mul:
	case Div:
		return 2;
	}
	return 0;
}

ExpressionOp ExpressionOperator::getOperator()
{
	return Operator;
}

