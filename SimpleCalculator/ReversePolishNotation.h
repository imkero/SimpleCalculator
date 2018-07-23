#pragma once
#include <vector>
#include <stack>
#include "Enums.h"
#include "ExpressionElement.h"

class ReversePolishNotation
{
private:
	std::vector<ExpressionElement> Elements;
	std::stack<TokenType> Stack;

public:
	void input(ExpressionElement);
	void endInput();
	double compute();
};

