#pragma once
#include "ExpressionBase.h"
#include <vector>
class VerticalExpressionBase :
	public ExpressionBase
{
protected:
	int ChildrenCount;
	bool IsSubExpr;
	HorizontalExpression **ChildrenArray;
public:
	VerticalExpressionBase(ExpressionBase *parent, int childrenCount);
	VerticalExpressionBase(const VerticalExpressionBase &);
	virtual ~VerticalExpressionBase();

	void setParent(ExpressionBase *);

	void remove(ExpressionBase *, bool moveCursor);
	int findChildPosition(ExpressionBase *);
	int getLength();
	virtual HorizontalExpression * getChild(int index);
	ValidateResult validate();
};

