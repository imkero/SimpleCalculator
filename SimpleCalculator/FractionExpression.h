#pragma once
#include "VerticalExpressionBase.h"
#include <QPen>

class FractionExpression :
	public VerticalExpressionBase
{
private:
	// fraction line height
	const static int LineHeight = 2;
	
	const static int ReservedSpaceWidth = 3;
	const static int ReservedTotalWidth = (5 + ReservedSpaceWidth) * 2;
	
	// height between line and sub-expr
	const static int ReservedHeight = 3;
	const static int ReservedHeightSub = 2;

	static QPen LinePen;
public:
	FractionExpression(ExpressionBase *parent);

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	void draw(QPainter *);
	void mouseClick(const QPoint &);

	static void updateParam();

	~FractionExpression();

	ExpressionBase *clone() const;
};

