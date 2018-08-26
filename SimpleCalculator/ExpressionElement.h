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

	int RealWidth;
	DualHeight RealHeight;

	ExpressionElement(ExpressionBase *expr);
	ExpressionElement(TokenType token);

	bool isOperator() const;
	bool isToken() const;
	bool isToken(TokenType) const;
	bool isExpression() const;
	bool isVariable() const;
	bool isDigitOrDot() const;
	bool isBracket() const;
	char toChar() const;
	ExpressionElement clone() const;
};

