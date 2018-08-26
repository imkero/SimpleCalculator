#pragma once
#include "VerticalExpressionBase.h"
#include <QPen>

class AbsExpression :
	public VerticalExpressionBase
{
private:
	// abs line width
	const static int LineWidth = 2;

	const static int ReservedSpaceWidth = 4;
	const static int ReservedSpaceWidthInternal = 4;
	const static int ReservedTotalWidth = (ReservedSpaceWidth + ReservedSpaceWidthInternal + LineWidth) * 2;

	const static int ReservedHeight = 2;
	const static int ReservedHeightSub = 0;

	static QPen LinePen;
public:
	AbsExpression(ExpressionBase *parent);

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	void draw(QPainter *);
	void mouseClick(const QPoint &);

	static void updateParam();

	~AbsExpression();

	ExpressionBase *clone() const;
};

