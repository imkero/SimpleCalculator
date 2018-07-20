#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
class ExpressionSymbol : public ExpressionBase
{
protected:
	SymbolType Symbol; // + - * /
public:
	ExpressionSymbol(SymbolType);
	double calcValue();
	void calcRect();
	bool isOperator();
	SymbolType getSymbol();
};

