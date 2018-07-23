#include "HorizontalExpression.h"
#include "ExpressionSymbol.h"
#include "ReversePolishNotation.h"
#include "ConstantExpression.h"
#include "NotImplementedException.h"

HorizontalExpression::HorizontalExpression() : ComputableExpression(Horizontal)
{
}

HorizontalExpression::~HorizontalExpression()
{
}

double HorizontalExpression::computeValue()
{
	if (validate())
	{
		int leftBracketCount = 0;
		int count = Elements.size();
		ReversePolishNotation invPolishExpr;
		for (int i = 0; i < count; i++)
		{
			if (Elements[i]->isComputable())
			{
<<<<<<< HEAD
				auto exprSymbol = Elements[i]->to<ExpressionSymbol>();
				switch (exprSymbol->getSymbol())
=======
			case Symbol: {
				ExpressionSymbol * symbolExpr = static_cast<ExpressionSymbol *>(Elements[i]);
				switch (symbolExpr->getSymbol())
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
				{
				case LeftBracket:
					leftBracketCount++;
					if (i > 0 && (Elements[i - 1]->Type != Symbol || Elements[i - 1]->to<ExpressionSymbol>()->getSymbol() == RightBracket))
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
					while (!Elements[i + 1]->isComputable() && Elements[i + 1]->to<ExpressionSymbol>()->isOperator())
					{
						switch (Elements[i + 1]->to<ExpressionSymbol>()->getSymbol())
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
<<<<<<< HEAD
			else 
			{
				auto * exprSymbol = Elements[i]->to<ComputableExpression>();
				rpn.input(ExpressionElement(exprSymbol->computeValue()));
=======
				break;
			default:
				invPolishExpr.input(ExpressionElement(Elements[i]->calcValue()));
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
				break;
			}
		}
		while (leftBracketCount > 0)
		{
			invPolishExpr.input(ExpressionElement(RightBracket));
			leftBracketCount--;
		}
<<<<<<< HEAD
		rpn.endInput();
		return rpn.compute();
=======
		invPolishExpr.endInput();
		return invPolishExpr.calc();
>>>>>>> parent of bb8cf9f... Rearrange MainWindowUI Buttons. Connect Signal-Slot of Keyboard Buttons.
	}
	return 0.0;
}

void HorizontalExpression::computeRect()
{
}

bool HorizontalExpression::validate()
{
	int rightBracketCount = 0;
	enum 
	{
		None,
		Computable,
		OperatorAddSub,
		OperatorMulDiv,
		LeftBracket,
		RightBracket
	} lastElement = None, currentElement = None;

	int count = Elements.size();
	bool computedFlag = false;

	for (int i = 0; i < count; i++)
	{
		if (Elements[i]->isComputable())
		{
			currentElement = Computable;
		}
		else
		{
			auto expr = Elements[i]->to<ExpressionSymbol>();
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

		switch (currentElement)
		{
		case Computable:
			computedFlag = true;
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
	if (!computedFlag)
	{
		// Empty Expression
		return false;
	}
	return true;
}

ExpressionBase * HorizontalExpression::findSlibing(ExpressionBase * self, Direction dir)
{
	int count = Elements.size();
	bool find = false;
	int i = 0;
	for (; i < count; i++)
	{
		if (Elements[i] == self)
		{
			find = true;
			break;
		}
	}
	if (find)
	{
		if (dir == LEFT)
		{	
			if (i > 0) return Elements[i - 1];
		}
		else
		{
			if (i < count - 1) return Elements[i + 1];
		}
		return getSlibing(dir);
	}
	return nullptr;
}

int HorizontalExpression::getLength()
{
	return Elements.size();
}

bool HorizontalExpression::insertAt(KbButtonName btnName, int pos)
{
	if (getLength() != 0)
	{
		throw new NotImplementedException("insertAt not empty HorizontalExpression");
	}
	switch (btnName)
	{
	case Button0:
	case Button1:
	case Button2:
	case Button3:
	case Button4:
	case Button5:
	case Button6:
	case Button7:
	case Button8:
	case Button9:
	{
		ConstantExpression *constExpr = ConstantExpression::fromButtonName(btnName);
		Elements.push_back(constExpr);
	}
	break;
	}
	return true;
}

