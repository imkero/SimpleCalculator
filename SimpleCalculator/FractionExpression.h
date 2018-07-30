#pragma once
#include "VerticalExpressionBase.h"
class FractionExpression :
	public VerticalExpressionBase
{
public:
	FractionExpression(ExpressionBase *parent);

	double computeValue();
	void computeRect();
	ValidateResult validate();
	int findChildPosition(ExpressionBase *);
	int getLength();

	~FractionExpression();
};

