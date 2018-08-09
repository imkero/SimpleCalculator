#include "FractionExpression.h"
#include "HorizontalExpression.h"

FractionExpression::FractionExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 2)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[1] = new HorizontalExpression(this);
}

double FractionExpression::computeValue()
{
	return ChildrenArray[0]->computeValue() / ChildrenArray[1]->computeValue();
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

int FractionExpression::findChildPosition(ExpressionBase *expr)
{
	if (expr == ChildrenArray[0])
		return 0;
	else if (expr == ChildrenArray[1])
		return 1;
	else
		return -1;
}

int FractionExpression::getLength()
{
	return 2;
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
