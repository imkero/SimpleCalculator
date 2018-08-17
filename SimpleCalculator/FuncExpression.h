#pragma once
#include "VerticalExpressionBase.h"
#include "ExpressionElement.h"

class FuncExpression :
	public VerticalExpressionBase
{
protected:
	virtual void computeFuncNameSize() = 0;
	virtual int computeFuncNamePositionPrefix() = 0;
	virtual void drawFuncName(QPainter *) = 0;
	ExpressionElement LeftB;
	ExpressionElement RightB;
public:
	FuncExpression(ExpressionBase * parent);
	void computeSize();
	void computePosition(AnchoredPoint);
	void draw(QPainter *);
	~FuncExpression();
};

