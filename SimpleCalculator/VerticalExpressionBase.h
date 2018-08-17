#pragma once
#include "ExpressionBase.h"
#include <vector>
class VerticalExpressionBase :
	public ExpressionBase
{
protected:
	int ChildrenCount;
	bool IsSubExpr;
public:
	HorizontalExpression **ChildrenArray;
	VerticalExpressionBase(ExpressionBase *parent, int childrenCount);
	void remove(ExpressionBase *, bool moveCursor);
	int findChildPosition(ExpressionBase *);
	int getLength();
	ValidateResult validate();
	virtual ~VerticalExpressionBase();
};

