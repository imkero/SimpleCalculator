#include "ExpressionElement.h"
#include "EnumConvert.h"

ExpressionElement::ExpressionElement(ExpressionBase *expr)
{
	IsToken = false;
	Data.Expr = expr;
}

ExpressionElement::ExpressionElement(TokenType token)
{
	IsToken = true;
	Data.Token = token;
}

bool ExpressionElement::isOperator() const
{
	if (!IsToken) return false;
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

bool ExpressionElement::isToken() const
{
	return IsToken;
}

bool ExpressionElement::isExpression() const
{
	return !IsToken;
}

bool ExpressionElement::isDigitOrDot() const
{
	if (!IsToken) return false;
	switch (Data.Token)
	{
	case Digit0:
	case Digit1:
	case Digit2:
	case Digit3:
	case Digit4:
	case Digit5:
	case Digit6:
	case Digit7:
	case Digit8:
	case Digit9:
	case DigitDot:
		return true;
	default:
		return false;
	}
}


bool ExpressionElement::isBracket() const
{
	if (!IsToken) return false;
	switch (Data.Token)
	{
	case LeftBracket:
	case RightBracket:
		return true;
	default:
		return false;
	}
}

char ExpressionElement::toChar() const
{
	if (!IsToken) return ' ';
	return EnumConvert::token2char(Data.Token);
}
