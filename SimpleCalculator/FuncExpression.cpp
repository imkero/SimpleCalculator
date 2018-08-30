#include "FuncExpression.h"
#include "HorizontalExpression.h"
#include "ExpressionPaintUtil.h"

FuncExpression::FuncExpression(ExpressionBase * parent) : VerticalExpressionBase(parent, 1), LeftB(LeftBracket), RightB(RightBracket)
{
	ChildrenArray[0] = new HorizontalExpression(this);
	ChildrenArray[0]->setIsSubExpr(IsSubExpr);
}

void FuncExpression::computeSize()
{
	computeFuncNameSize();
	ChildrenArray[0]->computeSize();
	LeftB.RealHeight = RightB.RealHeight = ChildrenArray[0]->Rect.Height;
	LeftB.RealWidth = ExpressionPaintUtil::computeBracketWidth(LeftB.RealHeight.total(), IsSubExpr);
	RightB.RealWidth = ExpressionPaintUtil::computeBracketWidth(RightB.RealHeight.total(), IsSubExpr);
	Rect.Width += LeftB.RealWidth + RightB.RealWidth + ChildrenArray[0]->Rect.Width;
	Rect.Height.merge(LeftB.RealHeight);
	Rect.Height.merge(ChildrenArray[0]->Rect.Height);
}

void FuncExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
	QPoint point = Rect.Pos;
	point.rx() += computeFuncNamePositionPrefix() + LeftB.RealWidth;
	ChildrenArray[0]->computePosition(AnchoredPoint(point, AnchorType::Left));
}

void FuncExpression::draw(QPainter *painter)
{
	QPoint point = Rect.Pos;

	drawFuncName(painter);
	point.rx() += computeFuncNamePositionPrefix();

	ExpressionPaintUtil::drawLeftBracket(painter, point, &LeftB);
	point.rx() += LeftB.RealWidth;

	ChildrenArray[0]->draw(painter);
	point.rx() += ChildrenArray[0]->Rect.Width;

	ExpressionPaintUtil::drawRightBracket(painter, point, &LeftB);
}


FuncExpression::~FuncExpression()
{
	if (ChildrenArray[0] != nullptr)
	{
		delete ChildrenArray[0];
		ChildrenArray[0] = nullptr;
	}
}
