#pragma once
#include "VerticalExpressionBase.h"
class FractionExpression :
	public VerticalExpressionBase
{
public:
	FractionExpression(ExpressionBase *parent);

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	ValidateResult validate();
	void draw(QPainter *);

	~FractionExpression();
};

