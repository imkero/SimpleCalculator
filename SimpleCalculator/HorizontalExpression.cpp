#include "HorizontalExpression.h"
#include "ReversePolishNotation.h"
#include "GlobalMgr.h"
#include "ExpressionRect.h"
#include "EnumConvert.h"
#include "Util.h"
#include <stack>
#include "ExpressionPaintUtil.h"
#include "FractionExpression.h"
#include "AbsExpression.h"
#include "SinExpression.h"
#include "CosExpression.h"
#include "TanExpression.h"
#include "SindExpression.h"
#include "CosdExpression.h"
#include "TandExpression.h"
#include "ArcsinExpression.h"
#include "ArccosExpression.h"
#include "ArctanExpression.h"
#include "LnExpression.h"
#include "Log10Expression.h"
#include "LogExpression.h"
#include "SqrtExpression.h"
#include "SqrtXYExpression.h"
#include "VariableExpression.h"

#pragma execution_character_set("utf-8")

QPen HorizontalExpression::PenEmptyBlock;

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
		return ValidateResult(EmptyExpression, this, fromIdx);
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

HorizontalExpression::HorizontalExpression(const HorizontalExpression &expr) : ExpressionBase(expr), IsSubExpr(expr.IsSubExpr)
{
	for (auto iter = expr.Elements.cbegin(); iter != expr.Elements.cend(); ++iter)
	{
		Elements.push_back((*iter).clone());
		if (Elements.back().isExpression())
		{
			Elements.back().Data.Expr->setParent(this);
		}
	}
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

void HorizontalExpression::updateParam()
{
	QVector<qreal> dashes;
	dashes << 2 << 2;
	PenEmptyBlock.setDashPattern(dashes);
	PenEmptyBlock.setWidth(1);
	PenEmptyBlock.setColor(g_Data->Visual.PanelSubColor);
}

ComputeResult HorizontalExpression::computeValue()
{
	ValidateResult v = validate();
	if (!v.good()) return ComputeResult(v);

	ComputeResult result;

	ReversePolishNotation rpn;
	int length = Elements.size();

	std::string numberCache;
	for (int i = 0; i < length; i++)
	{
		auto curElement = &Elements[i];
		if (curElement->isDigitOrDot())
		{
			int savedIndex = i;
			i--;
			while (i + 1 < length && Elements[i + 1].isDigitOrDot())
			{
				numberCache.push_back(Elements[i + 1].toChar());
				i++;
			}
			CompType numberDouble;
			if (numberCache == ".")
				numberDouble = 0;
			else
				sscanf(numberCache.c_str(), "%lf", &numberDouble);
			numberCache.clear();
			rpn.inputNumber(numberDouble, savedIndex);
		}
		else if (curElement->isExpression())
		{
			result = curElement->Data.Expr->computeValue();
			if (result.good())
			{
				rpn.inputToken(LeftBracket, -1);
				rpn.inputNumber(result.Value, i);
				rpn.inputToken(RightBracket, -1);
			}
			else
			{
				return result;
			}
		}
		else
		{
			rpn.inputToken(curElement->Data.Token, i);
		}
	}
	rpn.endInput();

	result = rpn.compute();
	result.Expr = this;
	if (result.Error == ComputeErrorType::ZeroPowZero)
	{
		result.Expr = Elements[result.IndexFrom + 1].Data.Expr->as<HorizontalExpression>();
		result.IndexFrom = 0;
		result.IndexTo = result.Expr->getLength() - 1;
	}
	return result;
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
				height = element.RealHeight = basicHeight;
				element.RealWidth = (*tokenWidthMap)[LeftBracket];
				break;
			case RightBracket:
				// right bracket param
				element.RealHeight = height;
				element.RealWidth = ExpressionPaintUtil::computeBracketWidth(height.total(), IsSubExpr);

				// add right bracket width
				width += element.RealWidth;

				if (!bracketStack.empty())
				{
					// sync left bracket param
					bracketStack.top().first->RealHeight = height;
					bracketStack.top().first->RealWidth = element.RealWidth;
					
					// add left bracket width
					width += element.RealWidth;

					// pop height
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
				}
				break;
			default:
				width += element.RealWidth = (*tokenWidthMap)[element.Data.Token];
				element.RealHeight = basicHeight;
				break;
			}
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
		// left bracket param
		bracketStack.top().first->RealHeight = height;
		bracketStack.top().first->RealWidth = ExpressionPaintUtil::computeBracketWidth(height.total(), IsSubExpr);

		// pop height
		height.merge(bracketStack.top().second);

		// left bracket width
		width += bracketStack.top().first->RealWidth;

		bracketStack.pop();
	}

	if (width == 0)
		width = getBasicWidth();

	Rect.Width = width + KeptWidth;
	Rect.Height = height;
}

void HorizontalExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	
	QPoint pos = Rect.Pos;
	for (auto iter = Elements.begin(); iter != Elements.end(); ++iter)
	{
		if ((*iter).isToken(Pow))
		{
			pos.rx() += (*iter).RealWidth;
			if (iter + 1 != Elements.end() && (*(iter + 1)).isExpression())
			{
				AnchoredPoint p(pos, AnchorType::BottomLeft);
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
			pos.rx() += (*++iter).RealWidth;
		}
		else 
		{
			if ((*iter).isExpression())
			{
				(*iter).Data.Expr->computePosition(AnchoredPoint(pos, AnchorType::Left));
			}
			pos.rx() += (*iter).RealWidth;
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
	case Button0: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit0)); goto afterInsert;
	case Button1: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit1)); goto afterInsert;
	case Button2: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit2)); goto afterInsert;
	case Button3: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit3)); goto afterInsert;
	case Button4: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit4)); goto afterInsert;
	case Button5: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit5)); goto afterInsert;
	case Button6: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit6)); goto afterInsert;
	case Button7: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit7)); goto afterInsert;
	case Button8: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit8)); goto afterInsert;
	case Button9: Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit9)); goto afterInsert;
	case ButtonAdd: Elements.insert(Elements.begin() + pos++, ExpressionElement(Add)); goto afterInsert;
	case ButtonSub: Elements.insert(Elements.begin() + pos++, ExpressionElement(Sub)); goto afterInsert;
	case ButtonMul : Elements.insert(Elements.begin() + pos++, ExpressionElement(Mul)); goto afterInsert;
	case ButtonDiv : Elements.insert(Elements.begin() + pos++, ExpressionElement(Div)); goto afterInsert;
	case ButtonBracketLeft : Elements.insert(Elements.begin() + pos++, ExpressionElement(LeftBracket)); goto afterInsert;
	case ButtonBracketRight : Elements.insert(Elements.begin() + pos++, ExpressionElement(RightBracket)); goto afterInsert;
	case ButtonDot: Elements.insert(Elements.begin() + pos++, ExpressionElement(DigitDot)); goto afterInsert;
	case ButtonBackspace: 
		if (pos == 0)
		{
			if (Parent != nullptr)
			{
				Parent->remove(this, true);
				return true;
			}
			else
			{
				return false;
			}
		}
		if (Elements[pos - 1].isToken() || Elements[pos - 1].isVariable())
		{
			Elements.erase(Elements.cbegin() + (pos - 1));
			pos--;
			goto afterInsert;
		}
		else
		{
			g_Data->Cursor.moveLeft();
			return true;
		}
		break;
	case ButtonPow:
	{
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Pow));
		HorizontalExpression *expr = new HorizontalExpression(this);
		expr->setIsSubExpr(true);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr, 0);
		return true;
	}
	break;
	case ButtonFrac:
	{
		FractionExpression *expr = new FractionExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonAbs:
	{
		AbsExpression *expr = new AbsExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonSin:
	{
		SinExpression *expr = new SinExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonCos:
	{
		CosExpression *expr = new CosExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonTan:
	{
		TanExpression *expr = new TanExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonSind:
	{
		SindExpression *expr = new SindExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonCosd:
	{
		CosdExpression *expr = new CosdExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonTand:
	{
		TandExpression *expr = new TandExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonArcsin:
	{
		ArcsinExpression *expr = new ArcsinExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonArccos:
	{
		ArccosExpression *expr = new ArccosExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonArctan:
	{
		ArctanExpression *expr = new ArctanExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonLn:
	{
		LnExpression *expr = new LnExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonLog10:
	{
		Log10Expression *expr = new Log10Expression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonLog:
	{
		LogExpression *expr = new LogExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break; 
	case ButtonSqrt:
	{
		SqrtExpression *expr = new SqrtExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonSqrtXY:
	{
		SqrtXYExpression *expr = new SqrtXYExpression(this);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr->getChild(0), 0);
		return true;
	}
	break;
	case ButtonDelete:
		if (pos == getLength())
			return false;
		removeAt(pos, true);
		return true;
		break;
	case ButtonSci:
	{
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Mul));
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit1));
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Digit0));
		Elements.insert(Elements.begin() + pos++, ExpressionElement(Pow));
		HorizontalExpression *expr = new HorizontalExpression(this);
		expr->setIsSubExpr(true);
		Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
		g_Data->Cursor.set(expr, 0);
		return true;
	}
	break;
	default: return false;
	}
	afterInsert:
	g_Data->Cursor.set(this, pos);
	
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
				drawEmptyBlock(painter, point);
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
		drawEmptyBlock(painter, point);
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
	char c[4];
	const char *cPtr = c;
	switch (element->Data.Token)
	{
	case LeftBracket:
		ExpressionPaintUtil::drawLeftBracket(painter, point, element);
		break;
	case RightBracket:
		ExpressionPaintUtil::drawRightBracket(painter, point, element);
		break;
	case Mul:
		cPtr = "¡Á";
		goto drawChar;
	case Div:
		cPtr = "¡Â";
		goto drawChar;
	default:
		c[0] = EnumConvert::token2char(element->Data.Token);
		c[1] = '\0';
	drawChar:
		painter->save();
		if (element->isOperator())
		{
			painter->setPen(g_Data->Visual.PanelSubColor);
		}
		painter->drawText(ExpressionPaintUtil::calcDrawTextPrefix(point, IsSubExpr), cPtr);
		painter->restore();

		break;
	}
}
void HorizontalExpression::drawEmptyBlock(QPainter *painter, QPoint point)
{
	painter->save();

	painter->setPen(PenEmptyBlock);
	painter->drawRect(QRect(point + QPoint(0, -getBasicHeight().Ascent), QSize(getBasicWidth() + KeptWidth, getBasicHeight().total())));

	painter->restore();
}

void HorizontalExpression::remove(ExpressionBase *expr, bool moveCursor)
{
	int index = findChildPosition(expr);
	if (index == -1) return;
	removeAt(index, moveCursor);
}

void HorizontalExpression::removeAt(int index, bool moveCursor)
{
	if (index < 0 || index >= Elements.size())
		return;
	auto elementIter = Elements.begin() + index;
	ExpressionElement & element = *(Elements.begin() + index);
	if (element.isToken() || element.isVariable())
	{
		if (element.Data.Token == Pow)
		{
			delete (*(elementIter + 1)).Data.Expr;
			Elements.erase(elementIter, elementIter + 2);
		}
		else
		{
			Elements.erase(elementIter);
		}
		if (moveCursor)
		{
			g_Data->Cursor.set(this, index);
		}
	}
	else
	{
		if (index > 0 && (*(elementIter - 1)).isToken(Pow))
		{
			delete (*elementIter).Data.Expr;
			Elements.erase(elementIter - 1, elementIter + 1);
			if (moveCursor)
			{
				g_Data->Cursor.set(this, index - 1);
			}
		}
		else
		{
			delete (*elementIter).Data.Expr;
			Elements.erase(elementIter);
			if (moveCursor)
			{
				g_Data->Cursor.set(this, index);
			}
		}
	}
}

void HorizontalExpression::insertVariable(int pos, const std::string &varName)
{
	VariableExpression *expr = new VariableExpression(this, varName);
	Elements.insert(Elements.begin() + pos++, ExpressionElement(expr));
	g_Data->Cursor.set(this, pos);
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

QRect HorizontalExpression::rectBetween(int from, int to)
{
	QRect rect;
	if (Elements.size() == 0)
	{
		return QRect(pointAt(0, AnchorType::TopLeft), QSize(getBasicWidth() + KeptWidth, getBasicHeight().total()));
	}
	else if (from >= Elements.size())
	{
		return QRect(pointAt(Elements.size(), AnchorType::TopLeft), QSize(getBasicWidth() + KeptWidth, getBasicHeight().total()));
	}
	else
	{
		QPoint pos = Rect.Pos;
		for (int i = 0; i < from; i++)
		{
			pos.rx() += Elements[i].RealWidth;
		}
		int width = 0;
		DualHeight height = getBasicHeight();
		int length = Elements.size();
		for (int i = from; i <= to && i < length; i++)
		{
			width += Elements[i].RealWidth;
			height.merge(Elements[i].RealHeight);
		}
		if (to >= length)
		{
			width += getBasicWidth();
		}
		return QRect(QPoint(pos.x(), pos.y() - height.Ascent), QSize(width, height.total()));
	}
	return rect;
}

void HorizontalExpression::mouseClick(const QPoint &mousePoint)
{
	QPoint point = Rect.Pos;
	if (Elements.size() == 0)
	{
		if (Rect.getRect().contains(mousePoint))
		{
			g_Data->Cursor.set(this, 0);
			return;
		}
	}
	else
	{
		// mouse click before the begin of expr
		if (mousePoint.x() < point.x())
		{
			g_Data->Cursor.set(this, 0);
		}
		for (auto iter = Elements.cbegin(); iter != Elements.cend(); ++iter)
		{
			const ExpressionElement & element = *iter;
			if (element.RealWidth <= 0)
				continue;
			if (point.x() <= mousePoint.x() && mousePoint.x() < point.x() + element.RealWidth &&
				point.y() - element.RealHeight.Ascent <= mousePoint.y() && mousePoint.y() <= point.y() + element.RealHeight.Descent
			)
			{
				if (element.isExpression() && element.Data.Expr->Type != Variable)
				{
					element.Data.Expr->mouseClick(mousePoint);
					return;
				}
				else if (element.isToken(Pow))
				{
					g_Data->Cursor.set(this, iter - Elements.cbegin());
					return;
				}
				else
				{
					int leftDistance = mousePoint.x() - point.x();
					int rightDistance = element.RealWidth - leftDistance;
					if (rightDistance > leftDistance)
					{
						// cursor on left-side
						g_Data->Cursor.set(this, iter - Elements.cbegin());
					}
					else
					{
						// cursor on right-side
						g_Data->Cursor.set(this, iter - Elements.cbegin() + 1);
					}
					return;
				}
			}
			point.rx() += element.RealWidth;
		}
		// mouse click after the end of expr
		if (mousePoint.x() >= point.x())
		{
			g_Data->Cursor.set(this, getLength());
		}
	}
	
}

const std::vector<ExpressionElement>& HorizontalExpression::getElements()
{
	return Elements;
}

ExpressionBase * HorizontalExpression::clone() const
{
	return new HorizontalExpression(*this);
}

