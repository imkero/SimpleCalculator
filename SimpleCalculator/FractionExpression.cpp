#include "FractionExpression.h"
#include "HorizontalExpression.h"

FractionExpression::FractionExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 2)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[1] = new HorizontalExpression(this);
}

ComputeResult FractionExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	ComputeResult right = ChildrenArray[1]->computeValue();
	if (!left.good()) 
		return left;
	if (!right.good()) 
		return right;

	if (right.Value == 0)
		return ComputeResult(ValidateErrorType::DivideByZero, ChildrenArray[1], 0, ChildrenArray[1]->getLength() - 1);
	return ComputeResult(left.Value / right.Value);
}

void FractionExpression::computeSize()
{
}

void FractionExpression::computePosition(AnchoredPoint)
{
}

ValidateResult FractionExpression::validate()
{
	ValidateResult result = ChildrenArray[0]->validate();
	if (!result.good())
		return result;
	result = ChildrenArray[1]->validate();
	return result;
}

void FractionExpression::draw(QPainter *)
{
}

FractionExpression::~FractionExpression()
{
	if (ChildrenArray[1] != nullptr)
	{
		delete ChildrenArray[1];
		ChildrenArray[1] = nullptr;
	}
	if (ChildrenArray[0] != nullptr)
	{
		delete ChildrenArray[0];
		ChildrenArray[0] = nullptr;
	}
}
