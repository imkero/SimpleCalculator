#pragma once
#include "ValidateResult.h"
#include "CalcTypes.h"
#include "corecrt_math.h"
class ExpressionBase;

struct ComputeResult
{
	ComputeErrorType Error;
	HorizontalExpression *Expr;
	int IndexFrom = -1;
	int IndexTo = -1;
	CompType Value = 0;
	ComputeResult::ComputeResult(CompType value);
	ComputeResult::ComputeResult();
	ComputeResult::ComputeResult(ValidateResult validate);
	ComputeResult::ComputeResult(ComputeErrorType error, int index);
	ComputeResult::ComputeResult(ComputeErrorType error, HorizontalExpression *expr, int index);
	ComputeResult::ComputeResult(ComputeErrorType error, HorizontalExpression *expr, int index, int index2);
	bool ComputeResult::good();
};