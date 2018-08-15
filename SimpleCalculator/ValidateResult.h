#pragma once
#include "Enums.h"
class HorizontalExpression;

struct ValidateResult
{
	ValidateErrorType Type;
	int Pos;
	int PosTo;
	HorizontalExpression *Expr;

	ValidateResult(HorizontalExpression *expr)
	{
		Type = Success;
		Expr = expr;
		Pos = 0;
	}
	ValidateResult(ValidateErrorType error, HorizontalExpression *expr, int pos)
	{
		Type = error;
		Expr = expr;
		Pos = pos;
	}
	ValidateResult(ValidateErrorType error, HorizontalExpression *expr, int pos, int pos2)
	{
		Type = error;
		Expr = expr;
		Pos = pos;
		PosTo = pos2;
	}
	bool good()
	{
		return Type == Success;
	}
};

