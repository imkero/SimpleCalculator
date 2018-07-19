#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
class ExpressionOperator : public ExpressionBase
{
protected:
	ExpressionOp Operator; // + - * /
public:
	ExpressionOperator(ExpressionOp op);
	int getPriority();
	ExpressionOp getOperator();
};

