#include "AbsExpression.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"

QPen AbsExpression::LinePen;

AbsExpression::AbsExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 1)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[0]->setIsSubExpr(IsSubExpr);
}

ComputeResult AbsExpression::computeValue()
{
	ComputeResult left = ChildrenArray[0]->computeValue();
	if (!left.good())
		return left;
	return ComputeResult(abs(left.Value));
}

void AbsExpression::computeSize()
{
	ChildrenArray[0]->computeSize();
	Rect.Height.Ascent = (IsSubExpr ? ReservedHeightSub : ReservedHeight) + ChildrenArray[0]->Rect.Height.Ascent;
	Rect.Height.Descent = (IsSubExpr ? ReservedHeightSub : ReservedHeight) + ChildrenArray[0]->Rect.Height.Descent;
	Rect.Width = ChildrenArray[0]->Rect.Width + ReservedTotalWidth;
}

void AbsExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	QPoint point = Rect.Pos;

	ChildrenArray[0]->computePosition(AnchoredPoint(QPoint(point.x() + ReservedSpaceWidth + LineWidth + ReservedSpaceWidthInternal, point.y()), AnchorType::Left));
}

void AbsExpression::draw(QPainter *painter)
{
	painter->save();
	painter->setPen(LinePen);
	QPoint point = Rect.Pos;
	point.rx() += ReservedSpaceWidth + 1;
	painter->drawLine(QPoint(point.rx(), point.ry() - Rect.Height.Ascent), QPoint(point.rx(), point.ry() + Rect.Height.Ascent));

	point.rx() += LineWidth + ReservedSpaceWidthInternal + ReservedSpaceWidthInternal;
	point.rx() += ChildrenArray[0]->Rect.Width;

	painter->drawLine(QPoint(point.rx(), point.ry() - Rect.Height.Ascent), QPoint(point.rx(), point.ry() + Rect.Height.Ascent));

	ChildrenArray[0]->draw(painter);

	painter->restore();
}

void AbsExpression::mouseClick(const QPoint &mousePoint)
{
	if (mousePoint.x() < ChildrenArray[0]->Rect.Pos.x())
	{
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

void AbsExpression::updateParam()
{
	LinePen.setColor(g_Data->Visual.PanelMainColor);
	LinePen.setWidth(LineWidth);
}

AbsExpression::~AbsExpression()
{
	if (ChildrenArray[0] != nullptr)
	{
		delete ChildrenArray[0];
		ChildrenArray[0] = nullptr;
	}
}
