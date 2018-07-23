#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
class ExpressionElement
{
public:
	bool isToken; // false: Expression, true: Token
	union {
		ExpressionBase *Expr;
		TokenType Token;
	} Data;

	ExpressionElement(ExpressionBase *expr);
	ExpressionElement(TokenType token);

	bool isOperator();
};

