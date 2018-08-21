#include "ComputeResult.h"
#include "HorizontalExpression.h"
ComputeResult::ComputeResult(CompType value) : Error(ValidateErrorType::Success)
{
	Value = value;
}
ComputeResult::ComputeResult() : Error(ValidateErrorType::Success)
{

}
ComputeResult::ComputeResult(ValidateResult validate) : Error(validate.Type), Expr(validate.Expr), IndexFrom(validate.Pos)
{

}
ComputeResult::ComputeResult(ValidateErrorType error, HorizontalExpression *expr, int index) : Error(error), Expr(expr), IndexFrom(index)
{

}
ComputeResult::ComputeResult(ValidateErrorType error, HorizontalExpression *expr, int index, int index2) : Error(error), Expr(expr), IndexFrom(index), IndexTo(index2)
{

}
ComputeResult::ComputeResult(ValidateErrorType error, int index) : Error(error), IndexFrom(index)
{

}
bool ComputeResult::good()
{
	return Error == ValidateErrorType::Success;
}