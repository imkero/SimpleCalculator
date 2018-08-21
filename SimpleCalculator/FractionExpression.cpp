#include "FractionExpression.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"

QPen FractionExpression::LinePen;

FractionExpression::FractionExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 2)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[1] = new HorizontalExpression(this);
	ChildrenArray[0]->setIsSubExpr(IsSubExpr);
	ChildrenArray[1]->setIsSubExpr(IsSubExpr);
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
	ChildrenArray[0]->computeSize();
	ChildrenArray[1]->computeSize();
	Rect.Height.Ascent = (IsSubExpr ? ReservedHeightSub : ReservedHeight) + ChildrenArray[0]->Rect.Height.total();
	Rect.Height.Descent = (IsSubExpr ? ReservedHeightSub : ReservedHeight) + ChildrenArray[1]->Rect.Height.total();
	Rect.Width = qMax(ChildrenArray[0]->Rect.Width, ChildrenArray[1]->Rect.Width) + ReservedTotalWidth;
}

void FractionExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	QPoint point = Rect.Pos;
	point.rx() += Rect.Width / 2;

	ChildrenArray[0]->computePosition(AnchoredPoint(QPoint(point.x(), point.y() - (IsSubExpr ? ReservedHeightSub : ReservedHeight)), AnchorType::Bottom));
	ChildrenArray[1]->computePosition(AnchoredPoint(QPoint(point.x(), point.y() + (IsSubExpr ? ReservedHeightSub : ReservedHeight)), AnchorType::Top));
}

void FractionExpression::draw(QPainter *painter)
{
	painter->save();
	painter->setPen(LinePen);
	QPoint point = Rect.Pos;
	painter->drawLine(QPoint(point.rx() + ReservedSpaceWidth, point.ry()), QPoint(point.rx() + Rect.Width - ReservedSpaceWidth, point.ry()));

	ChildrenArray[0]->draw(painter);
	ChildrenArray[1]->draw(painter);

	painter->restore();
}

void FractionExpression::mouseClick(const QPoint &mousePoint)
{
	if (mousePoint.y() < Rect.Pos.y())
	{
		// up-side
		if (mousePoint.x() < ChildrenArray[0]->Rect.Pos.x())
		{
			// left-edge
			g_Data->Cursor.set(ChildrenArray[0], 0);
		}
		else if (mousePoint.x() >= ChildrenArray[0]->Rect.Pos.x() + ChildrenArray[0]->Rect.Width)
		{
			g_Data->Cursor.set(ChildrenArray[0], ChildrenArray[0]->getLength());
		}
		else
		{
			ChildrenArray[0]->mouseClick(mousePoint);
		}
	}
	else
	{
		// down-side
		if (mousePoint.x() < ChildrenArray[1]->Rect.Pos.x())
		{
			// left-edge
			g_Data->Cursor.set(ChildrenArray[1], 0);
		}
		else if (mousePoint.x() >= ChildrenArray[1]->Rect.Pos.x() + ChildrenArray[1]->Rect.Width)
		{
			g_Data->Cursor.set(ChildrenArray[1], ChildrenArray[1]->getLength());
		}
		else
		{
			ChildrenArray[1]->mouseClick(mousePoint);
		}
	}
}

void FractionExpression::updateParam()
{
	LinePen.setColor(g_Data->Visual.PanelSubColor);
	LinePen.setWidth(LineHeight);
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
