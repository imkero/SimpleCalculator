#include "HorizontalExpression.h"
#include "ReversePolishNotation.h"
#include "GlobalMgr.h"
#include "ExpressionRect.h"
#include "Util.h"

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

void HorizontalExpression::computeSize()
{
	int width = 0;
	DualHeight height = IsSubExpr ? g_Data->Visual.PanelSubExprHeight : g_Data->Visual.PanelExprHeight;
	auto tokenWidthMap = IsSubExpr ? &g_Data->Visual.PanelSubTokenWidth : &g_Data->Visual.PanelTokenWidth;
	for (auto iter = Elements.cbegin(); iter != Elements.cend(); iter++)
	{
		if ((*iter).isToken())
		{
			width += (*tokenWidthMap)[(*iter).Data.Token];
		}
		else
		{
			(*iter).Data.Expr->computeSize();
			width += (*iter).Data.Expr->Rect.Width;
			if (iter != Elements.cbegin() && (*(iter - 1)).isToken(Pow))
			{
				height.Ascent = maxInt(height.Ascent, (*iter).Data.Expr->Rect.Height.total() 
					+ IsSubExpr ? g_Data->Visual.SubExprSuperscriptDelta : g_Data->Visual.ExprSuperscriptDelta);
			}
			else
			{
				height.Ascent = maxInt(height.Ascent, (*iter).Data.Expr->Rect.Height.Ascent);
				height.Descent = maxInt(height.Descent, (*iter).Data.Expr->Rect.Height.Descent);
			}
			
		}
	}
	if (width == 0)
		width = g_Data->Visual.PanelTokenWidth[Digit0];

	Rect.Width = width;
	Rect.Height = height;
}

void HorizontalExpression::computePosition()
{
	Rect.Pos = QPoint(0, 0);
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

bool HorizontalExpression::input(KbButtonName btnName, int pos)
{
	switch (btnName)
	{
	case Button0: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit0)); break;
	case Button1: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit1)); break;
	case Button2: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit2)); break;
	case Button3: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit3)); break;
	case Button4: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit4)); break;
	case Button5: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit5)); break;
	case Button6: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit6)); break;
	case Button7: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit7)); break;
	case Button8: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit8)); break;
	case Button9: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit9)); break;
	case ButtonAdd: Elements.insert(Elements.begin() + pos++, ExpressionElement(Add)); break;
	case ButtonSub: Elements.insert(Elements.begin() + pos++, ExpressionElement(Sub)); break;
	case ButtonMul : Elements.insert(Elements.begin() + pos++, ExpressionElement(Mul)); break;
	case ButtonDiv : Elements.insert(Elements.begin() + pos++, ExpressionElement(Div)); break;
	case ButtonBracketLeft : Elements.insert(Elements.begin() + pos++, ExpressionElement(LeftBracket)); break;
	case ButtonBracketRight : Elements.insert(Elements.begin() + pos++, ExpressionElement(RightBracket)); break;
	case ButtonBackspace: 
		if (pos == 0) return false;
		if (Elements[pos - 1].isToken())
		{
			Elements.erase(Elements.cbegin() + (pos - 1));
		}
		else
		{
			// To-Do
		}
		break;
	default: return false;
	}
	g_Data->Cursor.set(this, pos);
	g_Data->markExprDirty();
	return true;
}

void HorizontalExpression::draw(QPainter *painter)
{
	painter->setPen(g_Data->Visual.PanelMainColor);
	painter->setFont(g_Data->Visual.PanelExprFont);
	QPoint point = g_Data->Visual.ExprPosiiton + Rect.Pos;
	for (auto iter = Elements.cbegin(); iter != Elements.cend(); iter++)
	{
		if ((*iter).isToken())
		{
			g_Data->Visual.drawToken(painter, point, (*iter).Data.Token);
		}
		else
		{
		}
	}
}

bool HorizontalExpression::getIsSubExpr()
{
	return IsSubExpr;
}

void HorizontalExpression::setIsSubExpr(bool flag)
{
	IsSubExpr = flag;
}

