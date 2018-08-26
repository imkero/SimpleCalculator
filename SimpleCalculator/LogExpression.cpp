#include "LogExpression.h"
#include "GlobalMgr.h"
#include "Util.h"
#include "ExpressionPaintUtil.h"

LogExpression::LogExpression(ExpressionBase * parent) : FuncExpression(parent)
{
	HorizontalExpression *child0 = ChildrenArray[0];
	delete[] ChildrenArray;
	ChildrenCount = 2;
	ChildrenArray = new HorizontalExpression *[2];
	ChildrenArray[0] = child0;
	ChildrenArray[1] = new HorizontalExpression(this);
	ChildrenArray[1]->setIsSubExpr(true);
}

LogExpression::~LogExpression()
{
	if (ChildrenArray[1] != nullptr)
	{
		delete ChildrenArray[1];
		ChildrenArray[1] = nullptr;
	}
}

void LogExpression::computeFuncNameSize()
{
	Rect.Width = (IsSubExpr ? FuncNameSubWidth : FuncNameWidth) + ChildrenArray[1]->Rect.Width;
	Rect.Height = IsSubExpr ? FuncNameHeight : FuncNameSubHeight;
	Rect.Height.Descent = qMax(Rect.Height.Descent, ChildrenArray[1]->Rect.Height.total());
}

int LogExpression::computeFuncNamePositionPrefix()
{
	return (IsSubExpr ? FuncNameSubWidth : FuncNameWidth) + ChildrenArray[1]->Rect.Width;
}

void LogExpression::drawFuncName(QPainter *painter)
{
	painter->save();
	painter->setFont(IsSubExpr ? g_Data->Visual.PanelSubExprFont : g_Data->Visual.PanelExprFont);
	painter->drawText(ExpressionPaintUtil::calcDrawTextPrefix(Rect.Pos, IsSubExpr), "log");
	ChildrenArray[1]->draw(painter);
	painter->restore();
}

void LogExpression::mouseClick(const QPoint &mousePoint)
{
	if (ChildrenArray[1]->Rect.getRect().contains(mousePoint))
	{
		ChildrenArray[1]->mouseClick(mousePoint);
	}
	else
	{
		QPoint point = Rect.Pos;
		point.rx() += IsSubExpr ? FuncNameSubWidth : FuncNameWidth;
		if (mousePoint.x() < point.x())
		{
			g_Data->Cursor.set(ChildrenArray[1], 0);
			g_Data->Cursor.moveLeft();
			return;
		}
		point.rx() += ChildrenArray[1]->Rect.Width + LeftB.RealWidth;
		if (mousePoint.x() < point.x())
		{
			g_Data->Cursor.set(ChildrenArray[0], 0);
			return;
		}
		point.rx() += ChildrenArray[0]->Rect.Width;
		if (mousePoint.x() < point.x())
		{
			ChildrenArray[0]->mouseClick(mousePoint);
			return;
		}
		g_Data->Cursor.set(ChildrenArray[0], ChildrenArray[0]->getLength());

	}
}

void LogExpression::computeSize()
{
	ChildrenArray[1]->computeSize();
	FuncExpression::computeSize();
}

void LogExpression::computePosition(AnchoredPoint anchoredPos)
{
	FuncExpression::computePosition(anchoredPos);
	QPoint point = Rect.Pos;
	point.rx() += IsSubExpr ? FuncNameSubWidth : FuncNameWidth;
	ChildrenArray[1]->computePosition(AnchoredPoint(point, AnchorType::TopLeft));
}

ComputeResult LogExpression::computeValue()
{
	ComputeResult a = ChildrenArray[1]->computeValue();
	if (!a.good())
		return a;
	if (a.Value <= 0 || a.Value == 1)
		return ComputeResult(ComputeErrorType::LnBaseOutOfRange, ChildrenArray[1], 0, ChildrenArray[1]->getLength() - 1);

	ComputeResult x = ChildrenArray[0]->computeValue();
	if (!x.good())
		return x;
	if (x.Value <= 0)
		return ComputeResult(ComputeErrorType::LnPowOutOfRange, ChildrenArray[0], 0, ChildrenArray[0]->getLength() - 1);

	CompType result = log10(x.Value) / log10(a.Value);
	if (isNaN(a.Value) || isNaN(x.Value) || isNaN(result))
		return ComputeResult(ComputeErrorType::MathError, Parent->as<HorizontalExpression>(), Parent->findChildPosition(this));
	return ComputeResult(result);
}

int LogExpression::findChildPosition(ExpressionBase *expr)
{
	if (expr == ChildrenArray[0])
		return 1;
	else if (expr == ChildrenArray[1])
		return 0;
	else
		return -1;
}

HorizontalExpression * LogExpression::getChild(int index)
{
	switch (index)
	{
	case 0:
		return ChildrenArray[1];
	case 1:
		return ChildrenArray[0];
	default:
		return nullptr;
	}
}


void LogExpression::updateParam()
{
	QFontMetrics exprFontMetrics(g_Data->Visual.PanelExprFont);
	QFontMetrics exprSubFontMetrics(g_Data->Visual.PanelSubExprFont);
	FuncNameWidth = exprFontMetrics.width("log");
	FuncNameSubWidth = exprSubFontMetrics.width("log");
	FuncNameHeight = g_Data->Visual.PanelExprHeight;
	FuncNameSubHeight = g_Data->Visual.PanelSubExprHeight;
}

ExpressionBase * LogExpression::clone() const
{
	return new LogExpression(*this);
}

int LogExpression::FuncNameWidth = 0;
int LogExpression::FuncNameSubWidth = 0;
DualHeight LogExpression::FuncNameHeight;
DualHeight LogExpression::FuncNameSubHeight;
