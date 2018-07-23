#include "HorizontalExpression.h"
#include "ReversePolishNotation.h"

ValidateResult HorizontalExpression::validateInternal(int fromIdx, int toIdx)
{
	// Guaranteed: All brackets are matched

	enum {
		Begin, // begin of the expression
		ArithmeticOperator, // + - * / %
		PowerOperator,
		Sign, // positive or negative sign
		ConstInt, // digits only
		ConstDouble, // dot after digits
		Variable,
	} State = Begin;
	
	for (int i = fromIdx; i < toIdx; i++)
	{
		ExpressionElement *curElement = &Elements[i];
		switch (State)
		{
		case Begin:
			if (curElement->isToken)
			{
				switch (curElement->Data.Token)
				{
				case RightBracket:
					return ValidateResult(NotMatchingRightBracket, i);
				case Mul:
				case Div:

					break;
				}
			}
			else
			{

			}
			break;
		}
	}
	return ValidateResult();
}

HorizontalExpression::HorizontalExpression(ExpressionBase *parent) : ExpressionBase(Horizontal, parent)
{
}

HorizontalExpression::~HorizontalExpression()
{
}

double HorizontalExpression::computeValue()
{
	return NAN;
}

void HorizontalExpression::computeRect()
{
}

ValidateResult HorizontalExpression::validate()
{
	int rightBracketCount = 0;
	int length = Elements.size();
	for (int i = 0; i < length; i++)
	{
		if (Elements[i].isToken)
		{
			switch (Elements[i].Data.Token)
			{
			case LeftBracket:
				rightBracketCount--;
				break;
			case RightBracket:
				rightBracketCount++;
				if (rightBracketCount > 0)
				{
					return ValidateResult(NotMatchingRightBracket, i);
				}
				break;
			}
		}
	}

	return validateInternal(0, length);
}
