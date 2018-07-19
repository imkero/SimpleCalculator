#pragma once
#include "ExpressionBase.h"
#include <vector>

class HorizontalExpression : public ExpressionBase
{
public:
	std::vector<ExpressionBase *> Expr;
	ExpressionBase *Parent = nullptr;

	HorizontalExpression();
	~HorizontalExpression();

	void RearrangeBracket();
	double calcValue();
	void calcRect();
	bool validate();
};

