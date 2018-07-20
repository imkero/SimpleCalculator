#include "HorizontalExpression.h"
#include "ExpressionSymbol.h"
#include "ReversePolishNotation.h"

HorizontalExpression::HorizontalExpression() : ExpressionBase(ExpressionType::Horizontal)
{
}

HorizontalExpression::~HorizontalExpression()
{
}

double HorizontalExpression::calcValue()
{
	if (validate())
	{
		int leftBracketCount = 0;
		int count = Elements.size();
		ReversePolishNotation invPolishExpr;
		for (int i = 0; i < count; i++)
		{
			switch (Elements[i]->Type)
			{
			case Symbol: {
				ExpressionSymbol * symbolExpr = static_cast<ExpressionSymbol *>(Elements[i]);
				switch (symbolExpr->getSymbol())
				{
				case LeftBracket:
					leftBracketCount++;
					if (i > 0 && (Elements[i - 1]->Type != Symbol || static_cast<ExpressionSymbol *>(Elements[i - 1])->getSymbol() == RightBracket))
					{
						invPolishExpr.input(ExpressionElement(Mul));
					}
					break;
				case RightBracket:
					leftBracketCount--;
					break;
				}
				invPolishExpr.input(ExpressionElement(symbolExpr->getSymbol()));
				if (i + 1 < count && symbolExpr->isOperator())
				{
					// continuous operator parse. e.g.: 1+-1 = 0
					// consider "*+---", first "*" is op, 
					// and the following "+---", ignore every "+", just count "-" is odd or not
					int subCount = 0;
					while (Elements[i + 1]->Type == Symbol && static_cast<ExpressionSymbol *>(Elements[i + 1])->isOperator())
					{
						switch (static_cast<ExpressionSymbol *>(Elements[i + 1])->getSymbol())
						{
						case Add:
							break;
						case Sub:
							subCount++;
							break;
						default:
							//Error
							break;
						}
						i++;
					}
					if (subCount % 2 == 1)
					{
						invPolishExpr.input(ExpressionElement(-1));
						invPolishExpr.input(ExpressionElement(Mul));
					}
				}
			}
				break;
			default:
				invPolishExpr.input(ExpressionElement(Elements[i]->calcValue()));
				break;
			}
		}
		while (leftBracketCount > 0)
		{
			invPolishExpr.input(ExpressionElement(RightBracket));
			leftBracketCount--;
		}
		invPolishExpr.endInput();
		return invPolishExpr.calc();
	}
	return 0.0;
}

void HorizontalExpression::calcRect()
{
}

bool HorizontalExpression::validate()
{
	int rightBracketCount = 0;
	enum 
	{
		None,
		Calculatable,
		OperatorAddSub,
		OperatorMulDiv,
		LeftBracket,
		RightBracket
	} lastElement = None, currentElement = None;

	int count = Elements.size();
	bool calculatableFlag = false;

	for (int i = 0; i < count; i++)
	{
		switch (Elements[i]->Type)
		{
		case Symbol: {
			ExpressionSymbol *expr = static_cast<ExpressionSymbol *>(Elements[i]);
			switch (expr->getSymbol())
			{
			case Add:
			case Sub:
				currentElement = OperatorAddSub;
				break;
			case Mul:
			case Div:
				currentElement = OperatorMulDiv;
				break;
			case LeftBracket:
				currentElement = LeftBracket;
				break;
			case RightBracket:
				currentElement = RightBracket;
				break;
			}
		}
			break;
		default:
			currentElement = Calculatable;
			break;
		}

		switch (currentElement)
		{
		case Calculatable:
			calculatableFlag = true;
			switch (lastElement)
			{
			case RightBracket:
				return false;
			}
			break;
		case OperatorAddSub:
			break;
		case OperatorMulDiv:
			switch (lastElement)
			{
			case None:
			case OperatorAddSub:
			case OperatorMulDiv:
			case LeftBracket:
				return false;
			}
			break;
		case LeftBracket:
			rightBracketCount--;
			break;
		case RightBracket:
			rightBracketCount++;
			if (rightBracketCount > 0)
			{
				// extra right bracket ")"
				return false;
			}
			switch (lastElement)
			{
			case None:
			case OperatorAddSub:
			case OperatorMulDiv:
			case LeftBracket:
				return false;
			}
			break;
		}

		lastElement = currentElement;
	}
	switch (lastElement)
	{
		case OperatorAddSub:
		case OperatorMulDiv:
		case LeftBracket:
			return false;
	}
	if (!calculatableFlag)
	{
		// Empty Expression
		return false;
	}
	return true;
}
