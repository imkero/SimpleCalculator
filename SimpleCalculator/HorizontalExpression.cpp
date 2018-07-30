#include "HorizontalExpression.h"
#include "ReversePolishNotation.h"

ValidateResult HorizontalExpression::validateInternal(int fromIdx, int toIdx)
{
	// Guaranteed: All brackets are matched

	ExpressionInterpretState State = Begin;

	auto bracketSubExpressionHandler = [toIdx, this](int &i) -> ValidateResult {
		int rightBracketIdx = findMatchingRightBracket(i, toIdx);
		bool rightBracketFound = true;
		if (rightBracketIdx == -1)
		{
			rightBracketIdx = toIdx + 1;
			rightBracketFound = false;
		}
		ValidateResult result = validateInternal(i + 1, rightBracketIdx - 1);
		i = rightBracketIdx;
		return result;
	};

	for (int i = fromIdx; i <= toIdx; i++)
	{
		ExpressionElement *curElement = &Elements[i];

		switch (State)
		{
		case Begin:
		case ArithmeticOperator:
		case Sign:
			if (curElement->isToken())
			{
				switch (curElement->Data.Token)
				{
				case Mul:
				case Div:
				case Pow:
				case Mod:
					return ValidateResult(UnexceptedToken, this, i);
				case Add:
				case Sub:
					State = Sign;
					break;
				case LeftBracket:
					State = SubExpression;
					{
						ValidateResult r = bracketSubExpressionHandler(i);
						if (!r.good())
						{
							return r;
						}
					}
					break;
				case RightBracket:
					return ValidateResult(NotMatchingBracket, this, i);
				case Digit0:
				case Digit1:
				case Digit2:
				case Digit3:
				case Digit4:
				case Digit5:
				case Digit6:
				case Digit7:
				case Digit8:
				case Digit9:
					State = ConstInt;
					break;
				case DigitDot:
					State = ConstDouble;
					break;
				}
			}
			else if (curElement->isExpression())
			{
				State = SubExpression;
				{
					ValidateResult result = curElement->Data.Expr->validate();
					if (!result.good())
					{
						return result;
					}
				}
			}
			break;
		case PowerOperator:
			if (curElement->isExpression())
			{
				State = SubExpressionPower;
				{
					ValidateResult result = curElement->Data.Expr->validate();
					if (!result.good())
					{
						return result;
					}
				}
			}
			else
			{
				return ValidateResult(InternalError, this, i);
			}
			break;
		case ConstInt:
		case ConstDouble:
			if (curElement->isToken())
			{
				switch (curElement->Data.Token)
				{
				case Mul:
				case Div:
				case Mod:
				case Add:
				case Sub:
					State = ArithmeticOperator;
					break;
				case Pow:
					State = PowerOperator;
					break;
				case LeftBracket:
					State = SubExpression;
					{
						ValidateResult r = bracketSubExpressionHandler(i);
						if (!r.good())
						{
							return r;
						}
					}
					break;
				case RightBracket:
					return ValidateResult(NotMatchingBracket, this, i);
				case Digit0:
				case Digit1:
				case Digit2:
				case Digit3:
				case Digit4:
				case Digit5:
				case Digit6:
				case Digit7:
				case Digit8:
				case Digit9:
					State = ConstInt;
					break;
				case DigitDot:
					if (State == ConstDouble)
					{
						return ValidateResult(UnexceptedToken, this, i);
					}
					State = ConstDouble;
					break;
				}
			}
			else if (curElement->isExpression())
			{
				State = SubExpression;
				{
					ValidateResult result = curElement->Data.Expr->validate();
					if (!result.good())
					{
						return result;
					}
				}
			}
			break;
		case SubExpression:
		case SubExpressionPower:
			if (curElement->isToken())
			{
				switch (curElement->Data.Token)
				{
				case Mul:
				case Div:
				case Mod:
				case Add:
				case Sub:
					State = ArithmeticOperator;
					break;
				case Pow:
					if (State == SubExpressionPower)
					{
						return ValidateResult(UnexceptedToken, this, i);
					}
					State = PowerOperator;
				case LeftBracket:
					if (State == SubExpressionPower)
					{
						return ValidateResult(UnexceptedToken, this, i);
					}
					State = SubExpression;
					{
						ValidateResult r = bracketSubExpressionHandler(i);
						if (!r.good())
						{
							return r;
						}
					}
					break;
				case RightBracket:
					return ValidateResult(NotMatchingBracket, this, i);
				case Digit0:
				case Digit1:
				case Digit2:
				case Digit3:
				case Digit4:
				case Digit5:
				case Digit6:
				case Digit7:
				case Digit8:
				case Digit9:
					return ValidateResult(UnexceptedDigit, this, i);
				case DigitDot:
					return ValidateResult(UnexceptedToken, this, i);
					break;
				}
			}
			else if (curElement->isExpression())
			{
				State = SubExpression;
				{
					ValidateResult result = curElement->Data.Expr->validate();
					if (!result.good())
					{
						return result;
					}
				}
			}
			break;
		}
		
	}
	switch (State)
	{
	case Begin:
	case ArithmeticOperator:
	case PowerOperator:
	case Sign:
		return ValidateResult(UnexceptedToken, this, toIdx);
	}
	return ValidateResult(this);
}

int HorizontalExpression::findMatchingRightBracket(int leftBracketIdx, int maxIdx)
{
	int leftBracketCount = 1;
	for (int i = leftBracketIdx + 1; i <= maxIdx; i++)
	{
		if (Elements[i].isToken())
		{
			switch (Elements[i].Data.Token)
			{
			case LeftBracket:
				leftBracketCount++;
				break;
			case RightBracket:
				leftBracketCount--;
				break;
			}
			if (leftBracketCount == 0)
				return i;
		}
	}
	return -1;
}

HorizontalExpression::HorizontalExpression(ExpressionBase *parent)
	: ExpressionBase(Horizontal, parent)
{
}

HorizontalExpression::~HorizontalExpression()
{
	for (auto iter = Elements.cbegin(); iter != Elements.cend(); iter++)
	{
		if ((*iter).isExpression())
		{
			delete (*iter).Data.Expr;
		}
	}
}

double HorizontalExpression::computeValue()
{
	if (!validate().good()) return NAN;
	
	ReversePolishNotation rpn;
	int length = Elements.size();

	std::string numberCache;

	for (int i = 0; i < length; i++)
	{
		auto curElement = &Elements[i];
		if (curElement->isDigitOrDot())
		{
			i--;
			while (i + 1 < length && Elements[i + 1].isDigitOrDot())
			{
				numberCache.push_back(Elements[i + 1].toChar());
				i++;
			}
			double numberDouble;
			sscanf_s(numberCache.c_str(), "%lf", &numberDouble);
			numberCache.clear();
			rpn.inputNumber(numberDouble);
		}
		else if (curElement->isExpression())
		{
			rpn.inputNumber(curElement->Data.Expr->computeValue());
		}
		else
		{
			rpn.inputToken(curElement->Data.Token);
		}
	}
	
	rpn.endInput();
	return rpn.compute();
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
		if (Elements[i].isToken())
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
					return ValidateResult(NotMatchingBracket, this, i);
				}
				break;
			}
		}
	}
	return validateInternal(0, length - 1);
}

int HorizontalExpression::findChildPosition(ExpressionBase *toFind)
{
	int count = Elements.size();
	for (int i = 0; i < count; i++)
	{
		if (Elements[i].isExpression() && Elements[i].Data.Expr == toFind)
		{
			return i;
		}
	}
	return -1;
}


int HorizontalExpression::getLength()
{
	return Elements.size();
}

