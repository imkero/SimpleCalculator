#include "SqrtExpression.h"

#include "SqrtExpression.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"

QPen SqrtExpression::LinePen;

SqrtExpression::SqrtExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 1)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[0]->setIsSubExpr(IsSubExpr);
}

ComputeResult SqrtExpression::computeValue()
{
	ComputeResult left = getChild(0)->computeValue();
	if (!left.good())
		return left;

	if (left.Value < 0)
		return ComputeResult(ComputeErrorType::SqrtNegative, getChild(0), 0, getChild(0)->getLength() - 1);
	return ComputeResult(sqrt(left.Value));
}

void SqrtExpression::computeSize()
{
	getChild(0)->computeSize();
	Rect.Height.Ascent = getChild(0)->Rect.Height.Ascent + TopLineWidth + TopLineDistance;
	Rect.Height.Descent = getChild(0)->Rect.Height.Descent;
	TailBWidth = Rect.Height.total() / LineSlope;
	Rect.Width = LRDistance + TailAWidth + TailBWidth + getChild(0)->Rect.Width + GapSpaceWidth * 2 + LRDistance;
}

void SqrtExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	QPoint point = Rect.Pos;
	point.rx() += LRDistance + TailAWidth + TailBWidth + GapSpaceWidth;

	getChild(0)->computePosition(AnchoredPoint(point, AnchorType::Left));
}

void SqrtExpression::draw(QPainter *painter)
{
	painter->save();

	QPoint point = Rect.Pos;
	QPainterPath lineA;

	point.rx() += LRDistance;
	point.ry() += Rect.Height.Descent - TailAHeight - 1;
	lineA.moveTo(point);

	point.ry() += TailAHeight;
	point.rx() += TailAWidth;
	lineA.lineTo(point);

	point.ry() -= Rect.Height.total() - 2;
	point.rx() += TailBWidth;
	lineA.lineTo(point);

	point.rx() += getChild(0)->Rect.Width + GapSpaceWidth * 2;
	lineA.lineTo(point);

	painter->setRenderHint(QPainter::Antialiasing, true);

	painter->setPen(LinePen);
	painter->drawPath(lineA);
	painter->restore();

	getChild(0)->draw(painter);
}

void SqrtExpression::mouseClick(const QPoint &mousePoint)
{
	// up-side
	if (mousePoint.x() < Rect.Pos.x() + LRDistance + TailAWidth)
	{
		// left-edge
		g_Data->Cursor.set(getChild(0), 0);
		g_Data->Cursor.moveLeft();
	}
	else if (mousePoint.x() < getChild(0)->Rect.Pos.x())
	{
		// left-edge
		g_Data->Cursor.set(getChild(0), 0);
	}
	else if (mousePoint.x() >= getChild(0)->Rect.Pos.x() + getChild(0)->Rect.Width)
	{
		g_Data->Cursor.set(getChild(0), getChild(0)->getLength());
	}
	else
	{
		getChild(0)->mouseClick(mousePoint);
	}
}

void SqrtExpression::updateParam()
{
	LinePen.setColor(g_Data->Visual.PanelSubColor);
	LinePen.setWidth(TopLineWidth);
}

SqrtExpression::~SqrtExpression()
{
	if (ChildrenArray[0] != nullptr)
	{
		delete ChildrenArray[0];
		ChildrenArray[0] = nullptr;
	}
}

ExpressionBase * SqrtExpression::clone() const
{
	return new SqrtExpression(*this);
}
