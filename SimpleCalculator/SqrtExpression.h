#pragma once
#include "VerticalExpressionBase.h"
#include <QPen>

class SqrtExpression :
	public VerticalExpressionBase
{
private:
	constexpr static double LineSlope = 5;

	const static int TailAWidth = 4;
	const static int TailAHeight = 6;
	
	const static int LRDistance = 2;
	const static int TopLineDistance = 2;
	const static int TopLineWidth = 2;
	const static int GapSpaceWidth = 2;

	int TailBWidth = 0;

	static QPen LinePen;
public:
	SqrtExpression(ExpressionBase *parent);

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	void draw(QPainter *);
	void mouseClick(const QPoint &);

	static void updateParam();

	~SqrtExpression();

	ExpressionBase *clone() const;
};

