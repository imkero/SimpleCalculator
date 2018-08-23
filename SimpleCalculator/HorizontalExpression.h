#pragma once
#include "ExpressionBase.h"
#include "ExpressionElement.h"
#include "Enums.h"
#include "ValidateResult.h"
#include <vector>
#include <QPen>

class HorizontalExpression : public ExpressionBase
{
protected:
	ValidateResult validateInternal(int fromIdx, int toIdx);
	int findMatchingRightBracket(int leftBracketIdx, int maxIdx);
	bool IsSubExpr = false;
	int getBasicWidth();
	static QPen PenEmptyBlock;
	const static int KeptWidth = 0;
public:
	std::vector<ExpressionElement> Elements;

	HorizontalExpression(ExpressionBase *parent);
	~HorizontalExpression();

	static void updateParam();

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	ValidateResult validate();
	int findChildPosition(ExpressionBase *);
	int getLength();

	bool input(KbButtonName, int pos);
	void draw(QPainter *);
	bool getIsSubExpr();
	void setIsSubExpr(bool);
	void drawToken(QPainter *, QPoint, const ExpressionElement *);
	void drawEmptyBlock(QPainter *, QPoint);
	void remove(ExpressionBase *, bool moveCursor);
	void removeAt(int, bool moveCursor);
	const DualHeight &getBasicHeight();
	QPoint pointAt(int, AnchorType anchor = AnchorType::Left);
	QRect rectBetween(int from, int to);
	void mouseClick(const QPoint &);
};

