#pragma once
#include "FuncExpression.h"

class LogExpression :
	public FuncExpression
{
private:
	static int FuncNameWidth;
	static int FuncNameSubWidth;
	static DualHeight FuncNameHeight;
	static DualHeight FuncNameSubHeight;
public:
	LogExpression(ExpressionBase * parent);
	~LogExpression();

	void computeFuncNameSize();
	int computeFuncNamePositionPrefix();
	void drawFuncName(QPainter *);
	void mouseClick(const QPoint &);
	void computeSize();
	void computePosition(AnchoredPoint anchoredPos);
	ComputeResult computeValue();
	int findChildPosition(ExpressionBase *);
	HorizontalExpression * getChild(int index);
	static void updateParam();

	ExpressionBase *clone() const;
};

