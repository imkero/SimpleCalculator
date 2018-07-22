#pragma once
#include "ExpressionBase.h"
#include "ComputableExpression.h"
#include "Enums.h"
#include <vector>

class HorizontalExpression : public ComputableExpression
{
public:
	std::vector<ExpressionBase *> Elements;

	HorizontalExpression();
	~HorizontalExpression();

	virtual double computeValue();
	virtual void computeRect();
	virtual bool validate();

	virtual ExpressionBase *findSlibing(ExpressionBase *self, Direction dir);
	virtual int getLength();
	virtual bool insertAt(KbButtonName, int);
};

