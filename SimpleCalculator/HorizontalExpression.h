#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
#include <vector>

class HorizontalExpression : public ExpressionBase
{
public:
	std::vector<ExpressionBase *> Elements;
	ExpressionBase *Parent = nullptr;

	HorizontalExpression();
	~HorizontalExpression();

	double calcValue();
	void calcRect();
	bool validate();
};

