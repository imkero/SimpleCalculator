#pragma once
#include <vector>
#include <stack>
#include "Enums.h"
struct ExpressionElement
{
	bool isSymbol;
	union {
		SymbolType symbol;
		double value;
	} data;
	ExpressionElement(SymbolType symbol)
	{
		isSymbol = true;
		data.symbol = symbol;
	}
	ExpressionElement(double value)
	{
		isSymbol = false;
		data.value = value;
	}
};
class ReversePolishNotation
{
private:
	std::vector<ExpressionElement> Elements;
	std::stack<SymbolType> Stack;
public:
	// Input infix expression 
	// and translate into postfix expression.
	void input(ExpressionElement);
	void endInput();
	double compute();
};

