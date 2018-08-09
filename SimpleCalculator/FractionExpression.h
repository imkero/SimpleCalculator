#pragma once
#include "VerticalExpressionBase.h"
class FractionExpression :
	public VerticalExpressionBase
{
public:
	FractionExpression(ExpressionBase *parent);

	double computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	ValidateResult validate();
	int findChildPosition(ExpressionBase *);
	int getLength();
	void draw(QPainter *);

	~FractionExpression();
};

