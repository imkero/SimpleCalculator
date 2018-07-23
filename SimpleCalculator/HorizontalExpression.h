#pragma once
#include "ExpressionBase.h"
#include "ExpressionElement.h"
#include "Enums.h"
#include "ValidateResult.h"
#include <vector>

class HorizontalExpression : public ExpressionBase
{
protected:
	ValidateResult validateInternal(int fromIdx, int toIdx);
public:
	std::vector<ExpressionElement> Elements;
	ExpressionBase *Parent = nullptr;

	HorizontalExpression(ExpressionBase *parent);
	~HorizontalExpression();

	double computeValue();
	void computeRect();
	ValidateResult validate();
};

