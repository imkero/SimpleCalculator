#pragma once
#include "Enums.h"
class HorizontalExpression;

struct ValidateResult
{
	ValidateErrorType Type;
	int Pos;
	HorizontalExpression *Expr;

	ValidateResult(HorizontalExpression *expr)
	{
		Type = Success;
		Pos = 0;
		Expr = expr;
	}
	ValidateResult(ValidateErrorType error, HorizontalExpression *expr, int pos)
	{
		Type = error;
		Pos = pos;
		Expr = expr;
	}
	bool good()
	{
		return Type == Success;
	}
};

