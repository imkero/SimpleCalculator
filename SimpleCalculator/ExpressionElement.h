#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
class ExpressionElement
{
	bool IsToken; // false: Expression, true: Token
public:
	union {
		ExpressionBase *Expr;
		TokenType Token;
	} Data;

	ExpressionElement(ExpressionBase *expr);
	ExpressionElement(TokenType token);

	bool isOperator() const;
	bool isToken() const;
	bool isExpression() const;
	bool isDigitOrDot() const;
	bool isBracket() const;
	char toChar() const;
};

