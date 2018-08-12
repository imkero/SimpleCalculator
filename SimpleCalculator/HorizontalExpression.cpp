#include "HorizontalExpression.h"
#include "ReversePolishNotation.h"
#include "GlobalMgr.h"
#include "ExpressionRect.h"
#include "EnumConvert.h"
#include "Util.h"
#include <stack>

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

const DualHeight &HorizontalExpression::getBasicHeight()
{
	return IsSubExpr ? g_Data->Visual.PanelSubExprHeight : g_Data->Visual.PanelExprHeight;
}

int HorizontalExpression::getBasicWidth()
{
	return IsSubExpr ? g_Data->Visual.PanelSubTokenWidth[Digit0] : g_Data->Visual.PanelTokenWidth[Digit0];
}

HorizontalExpression::HorizontalExpression(ExpressionBase *parent)
	: ExpressionBase(Horizontal, parent)
{
}

HorizontalExpression::~HorizontalExpression()
{
	for (auto iter = Elements.cbegin(); iter != Elements.cend(); ++iter)
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
	const DualHeight &basicHeight = getBasicHeight();
	DualHeight height = basicHeight;

	auto tokenWidthMap = IsSubExpr ? &g_Data->Visual.PanelSubTokenWidth : &g_Data->Visual.PanelTokenWidth;
	std::stack<std::pair<ExpressionElement *, DualHeight>> bracketStack;

	for (auto iter = Elements.begin(); iter != Elements.end(); ++iter)
	{
		ExpressionElement & element = (*iter);
		if (element.isToken())
		{
			switch (element.Data.Token)
			{
			case LeftBracket:
				bracketStack.push(std::make_pair(&element, height));
				height = basicHeight;
				break;
			case RightBracket:
				element.RealHeight = height;
				if (!bracketStack.empty())
				{
					bracketStack.top().first->RealHeight = height;
					height.merge(bracketStack.top().second);
					bracketStack.pop();
				}
				break;
			case Pow:
				if (iter + 1 != Elements.end() && (*(iter + 1)).isExpression())
				{
					ExpressionBase *expr = (*(iter + 1)).Data.Expr;
					expr->computeSize();

					int powHeight = expr->Rect.Height.total() - (IsSubExpr ? g_Data->Visual.SubExprSuperscriptDelta : g_Data->Visual.ExprSuperscriptDelta);
					if (iter == Elements.begin() || (*(iter - 1)).isToken(LeftBracket) || (*(iter - 1)).isOperator())
					{
						element.RealHeight = basicHeight;
						width += element.RealWidth = getBasicWidth() + 2;
						powHeight += basicHeight.Ascent;
					}
					else
					{
						element.RealHeight = DualHeight(0, 0);
						element.RealWidth = 0;
						powHeight += (*(iter - 1)).RealHeight.Ascent;
					}
						
					if (height.Ascent < powHeight)
						height.Ascent = powHeight;
					
					++iter;

					width += (*iter).RealWidth = expr->Rect.Width;
					(*iter).RealHeight = DualHeight(powHeight, 0);
					continue;
				}
				break;
			}
			width += element.RealWidth = (*tokenWidthMap)[element.Data.Token];
			element.RealHeight = basicHeight;
		}
		else
		{
			ExpressionBase *expr = element.Data.Expr;
			expr->computeSize();
			width += element.RealWidth = expr->Rect.Width;
			element.RealHeight = expr->Rect.Height;
			height.merge(expr->Rect.Height);
		}
	}
	
	while (!bracketStack.empty())
	{
		bracketStack.top().first->RealHeight = height;
		height.merge(bracketStack.top().second);
		bracketStack.pop();
	}

	if (width == 0)
		width = getBasicWidth();

	Rect.Width = width;
	Rect.Height = height;
}

void HorizontalExpression::computePosition(AnchoredPoint point)
{
	Rect.setPos(point);
	
	QPoint posPoint = Rect.Pos;
	for (auto iter = Elements.begin(); iter != Elements.end(); ++iter)
	{
		posPoint.rx() += (*iter).RealWidth;
		if ((*iter).isToken(Pow))
		{
			if (iter + 1 != Elements.end() && (*(iter + 1)).isExpression())
			{
				AnchoredPoint p;
				p.Anchor = AnchorType::BottomLeft;
				p.Pos = posPoint;
				int powDelta = IsSubExpr ? g_Data->Visual.SubExprSuperscriptDelta : g_Data->Visual.ExprSuperscriptDelta;
				if (iter == Elements.begin() || (*(iter - 1)).isToken(LeftBracket))
				{
					powDelta -= getBasicHeight().Ascent;
				}
				else
				{
					powDelta -= (*(iter - 1)).RealHeight.Ascent;
				}
				p.Pos.ry() += powDelta;
				(*(iter + 1)).Data.Expr->computePosition(p);
			}
		}
		
	}
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
	case ButtonDot: Elements.insert(Elements.begin() + pos++, ExpressionElement(DigitDot)); break;
	case ButtonBackspace: 
		if (pos == 0) return false;
		if (Elements[pos - 1].isToken())
		{
			Elements.erase(Elements.cbegin() + (pos - 1));
			pos--;
		}
		else
		{
			// To-Do
		}
		break;
	case ButtonPow:
	{
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Pow));
		HorizontalExpression *expr = new HorizontalExpression(this);
		expr->setIsSubExpr(true);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr, 0);
		g_Data->markExprDirty();
		return true;
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
	if (!Rect.visible()) return;
	painter->save();
	painter->setPen(g_Data->Visual.PanelMainColor);
	painter->setFont(IsSubExpr ? g_Data->Visual.PanelSubExprFont : g_Data->Visual.PanelExprFont);
	QPoint point = Rect.Pos;
	for (auto iter = Elements.cbegin(); iter != Elements.cend(); ++iter)
	{
		if ((*iter).isToken(Pow))
		{
			if ((*iter).RealWidth > 0)
			{
				drawEmptyRect(painter, point);
			}
		}
		else if ((*iter).isToken())
		{
			drawToken(painter, point, &(*iter));
		}
		else
		{
			(*iter).Data.Expr->draw(painter);
		}
		point.rx() += (*iter).RealWidth;
	}
	if (Elements.size() == 0 && Parent != nullptr)
	{
		drawEmptyRect(painter, point);
	}
	painter->restore();
}

bool HorizontalExpression::getIsSubExpr()
{
	return IsSubExpr;
}

void HorizontalExpression::setIsSubExpr(bool flag)
{
	IsSubExpr = flag;
}

void HorizontalExpression::drawToken(QPainter *painter, QPoint point, const ExpressionElement *element)
{
	char c[2];
	c[0] = EnumConvert::token2char(element->Data.Token);
	c[1] = '\0';
	painter->save();
	if (element->isOperator() || element->isBracket())
	{
		painter->setPen(g_Data->Visual.PanelSubColor);
	}
	painter->drawText(point + QPoint(0, IsSubExpr ? g_Data->Visual.SubBasicCharHeightDelta : g_Data->Visual.BasicCharHeightDelta), c);
	painter->restore();
}

void HorizontalExpression::drawEmptyRect(QPainter *painter, QPoint point)
{
	painter->save();

	painter->setPen(g_Data->Visual.PenEmptyBlock);
	painter->drawRect(QRect(point + QPoint(0, -getBasicHeight().Ascent), QSize(getBasicWidth(), getBasicHeight().total())));

	painter->restore();
}


QPoint HorizontalExpression::pointAt(int offset, AnchorType anchor)
{
	QPoint point = Rect.Pos;
	int length = Elements.size();
	if (offset > length)
		offset = length;
	for (int i = 0; i < offset && i < length; i++)
	{
		point.rx() += Elements[i].RealWidth;
	}
	switch (anchor)
	{
	case AnchorType::BottomLeft:
		point.ry() += getBasicHeight().Descent;
		break;
	case AnchorType::TopLeft:
		point.ry() -= getBasicHeight().Ascent;
		break;
	}
	return point;
}

