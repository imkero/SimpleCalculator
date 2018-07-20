#include "ExpressionSymbol.h"
#include "Enums.h"
ExpressionSymbol::ExpressionSymbol(SymbolType symbol) : ExpressionBase(ExpressionType::Symbol), Symbol(symbol)
{
}

double ExpressionSymbol::calcValue()
{
	return 0.0;
}

void ExpressionSymbol::calcRect()
{
}

bool ExpressionSymbol::isOperator()
{
	return Symbol != LeftBracket && Symbol != RightBracket;
}

SymbolType ExpressionSymbol::getSymbol()
{
	return Symbol;
}

