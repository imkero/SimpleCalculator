#include "ExpressionElement.h"

ExpressionElement::ExpressionElement(ExpressionBase *expr)
{
	isToken = false;
	Data.Expr = expr;
}

ExpressionElement::ExpressionElement(TokenType token)
{
	isToken = true;
	Data.Token = token;
}

bool ExpressionElement::isOperator()
{
	switch (Data.Token)
	{
	case Add:
	case Sub:
	case Mul:
	case Div:
	case Pow:
	case Mod:
		return true;
	default:
		return false;
	}
}
