#pragma once
#include "VerticalExpressionBase.h"
class SimpleFuncExpression :
	public VerticalExpressionBase
{
public:
	SimpleFuncExpression(ExpressionBase * parent);
	~SimpleFuncExpression();
};

