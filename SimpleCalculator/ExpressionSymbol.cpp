#include "ExpressionSymbol.h"
#include "Enums.h"
#include "NotImplementedException.h"

ExpressionSymbol::ExpressionSymbol(SymbolType symbol) : ExpressionBase(ExpressionType::Symbol), Symbol(symbol)
{
}

void ExpressionSymbol::computeRect()
{
}

ExpressionBase * ExpressionSymbol::findSlibing(ExpressionBase *self, Direction dir)
{
	throw new NotImplementedException("ExpressionSymbol::getSlibing");
}

int ExpressionSymbol::getLength()
{
	return 1;
}

bool ExpressionSymbol::insertAt(KbButtonName, int)
{
	return false;
}

bool ExpressionSymbol::isOperator()
{
	return Symbol != LeftBracket && Symbol != RightBracket;
}

SymbolType ExpressionSymbol::getSymbol()
{
	return Symbol;
}

