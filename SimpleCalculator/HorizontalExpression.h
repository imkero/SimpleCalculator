#pragma once
#include "ExpressionBase.h"
#include "ExpressionElement.h"
#include "Enums.h"
#include "ValidateResult.h"
#include <vector>

class HorizontalExpression : public ExpressionBase
{
protected:
	ValidateResult validateInternal(int fromIdx, int toIdx);
	int findMatchingRightBracket(int leftBracketIdx, int maxIdx);
	bool IsSubExpr = false;
public:
	std::vector<ExpressionElement> Elements;
	ExpressionBase *Parent = nullptr;

	HorizontalExpression(ExpressionBase *parent);
	~HorizontalExpression();

	double computeValue();
	void computeSize();
	void computePosition();
	ValidateResult validate();
	int findChildPosition(ExpressionBase *);
	int getLength();

	bool input(KbButtonName, int pos);
	void draw(QPainter *);
	bool getIsSubExpr();
	void setIsSubExpr(bool);

	
};

