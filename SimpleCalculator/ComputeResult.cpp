#include "ComputeResult.h"
#include "HorizontalExpression.h"
ComputeResult::ComputeResult(CompType value) : Error(ComputeErrorType::Success)
{
	Value = value;
}
ComputeResult::ComputeResult() : Error(ComputeErrorType::Success)
{

}
ComputeResult::ComputeResult(ValidateResult validate) : Error(validate.Type), Expr(validate.Expr), IndexFrom(validate.Pos)
{

}
ComputeResult::ComputeResult(ComputeErrorType error, HorizontalExpression *expr, int index, int index2) : Error(error), Expr(expr), IndexFrom(index), IndexTo(index2)
{

}
ComputeResult::ComputeResult(ComputeErrorType error, int index) : Error(error), IndexFrom(index)
{

}
bool ComputeResult::good()
{
	return Error == ComputeErrorType::Success;
}