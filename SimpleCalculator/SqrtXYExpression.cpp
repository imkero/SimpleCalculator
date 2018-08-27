#include "SqrtXYExpression.h"
#include "HorizontalExpression.h"
#include "GlobalMgr.h"
#include "Util.h"

QPen SqrtXYExpression::LinePen;

SqrtXYExpression::SqrtXYExpression(ExpressionBase * parent)
	: VerticalExpressionBase(parent, 2)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[0]->setIsSubExpr(true);
	ChildrenArray[1] = new HorizontalExpression(this);
	ChildrenArray[1]->setIsSubExpr(IsSubExpr);
}

ComputeResult SqrtXYExpression::computeValue()
{
	ComputeResult x = getChild(1)->computeValue();
	if (!x.good())
		return x;

	ComputeResult n = getChild(0)->computeValue();
	if (!n.good())
		return n;

	if (x.Value < 0)
		return ComputeResult(ComputeErrorType::SqrtNegative, getChild(1), 0, getChild(1)->getLength() - 1);
	if (n.Value == 0)
		return ComputeResult(ComputeErrorType::SqrtPowZero, getChild(0), 0, getChild(0)->getLength() - 1);
	
	if (n.Value < 0 && x.Value == 0)
		return ComputeResult(ComputeErrorType::MathError, Parent->as<HorizontalExpression>(), Parent->findChildPosition(this));

	return ComputeResult(nthRoot(x.Value, n.Value));
}

void SqrtXYExpression::computeSize()
{
	getChild(0)->computeSize();
	getChild(1)->computeSize();

	Rect.Height.Ascent = getChild(1)->Rect.Height.Ascent + TopLineWidth + TopLineDistance;
	Rect.Height.Ascent += qMax(0, getChild(0)->Rect.Height.total() - g_Data->Visual.PanelSubExprHeight.total());

	Rect.Height.Descent = getChild(1)->Rect.Height.Descent;

	TailBWidth = (getChild(1)->Rect.Height.total() + TopLineWidth + TopLineDistance) / LineSlope;

	Rect.Width = getChild(1)->Rect.Width + GapSpaceWidth * 2 + LRDistance;
	Rect.Width += qMax(LRDistance + TailAWidth + TailBWidth, getChild(0)->Rect.Width + SubExprDistance);
}

void SqrtXYExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	QPoint point = Rect.Pos;
	point.rx() += LRDistance + qMax(TailAWidth + TailBWidth, getChild(0)->Rect.Width + SubExprDistance) - SubExprDistance;
	point.ry() -= getChild(1)->Rect.Height.Ascent + TopLineWidth + TopLineDistance - g_Data->Visual.PanelSubExprHeight.total();
	getChild(0)->computePosition(AnchoredPoint(point, AnchorType::BottomRight));
	point = Rect.Pos;
	point.rx() += LRDistance + qMax(TailAWidth + TailBWidth, getChild(0)->Rect.Width + SubExprDistance) + GapSpaceWidth;
	getChild(1)->computePosition(AnchoredPoint(point, AnchorType::Left));
}

void SqrtXYExpression::draw(QPainter *painter)
{
	painter->save();

	QPoint point = Rect.Pos;
	QPainterPath lineA;

	point.rx() += LRDistance + qMax(0, getChild(0)->Rect.Width + SubExprDistance - (TailAWidth + TailBWidth));
	point.ry() += Rect.Height.Descent - TailAHeight - 1;
	lineA.moveTo(point);

	point.ry() += TailAHeight;
	point.rx() += TailAWidth;
	lineA.lineTo(point);

	point.ry() -= getChild(1)->Rect.Height.total() - 1 + TopLineDistance;
	point.rx() += TailBWidth;
	lineA.lineTo(point);

	point.rx() += getChild(1)->Rect.Width + GapSpaceWidth * 2;
	lineA.lineTo(point);

	painter->setRenderHint(QPainter::Antialiasing, true);

	painter->setPen(LinePen);
	painter->drawPath(lineA);
	painter->restore();

	getChild(0)->draw(painter);
	getChild(1)->draw(painter);
}

void SqrtXYExpression::mouseClick(const QPoint &mousePoint)
{
	HorizontalExpression *child0 = getChild(0);
	HorizontalExpression *child1 = getChild(1);
	if (child0->Rect.getRect().contains(mousePoint))
	{
		child0->mouseClick(mousePoint);
	}
	else if (child1->Rect.getRect().contains(mousePoint))
	{
		child1->mouseClick(mousePoint);
	}
	else if (mousePoint.x() < Rect.Pos.x() + LRDistance)
	{
		g_Data->Cursor.set(child0, 0);
		g_Data->Cursor.moveLeft();
	}
	else if (mousePoint.x() < child1->Rect.Pos.x())
	{
		g_Data->Cursor.set(child1, 0);
	}
	else if (mousePoint.x() >= child1->Rect.Pos.x() + child1->Rect.Width)
	{
		g_Data->Cursor.set(child1, child1->getLength());
	}
}

void SqrtXYExpression::updateParam()
{
	LinePen.setColor(g_Data->Visual.PanelSubColor);
	LinePen.setWidth(TopLineWidth);
}

SqrtXYExpression::~SqrtXYExpression()
{
	if (ChildrenArray[0] != nullptr)
	{
		delete ChildrenArray[0];
		ChildrenArray[0] = nullptr;
	}
}

ExpressionBase * SqrtXYExpression::clone() const
{
	return new SqrtXYExpression(*this);
}
