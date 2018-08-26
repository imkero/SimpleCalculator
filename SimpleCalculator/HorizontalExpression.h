#pragma once
#include "ExpressionBase.h"
#include "ExpressionElement.h"
#include "Enums.h"
#include "ValidateResult.h"
#include <vector>
#include <string>
#include <QPen>

class HorizontalExpression : public ExpressionBase
{
protected:
	static QPen PenEmptyBlock;

	bool IsSubExpr = false;
	const static int KeptWidth = 0;
	std::vector<ExpressionElement> Elements;

	ValidateResult validateInternal(int fromIdx, int toIdx);
	int findMatchingRightBracket(int leftBracketIdx, int maxIdx);
	int getBasicWidth();
public:
	HorizontalExpression(ExpressionBase *parent);
	HorizontalExpression(const HorizontalExpression &);
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
	void insertVariable(int pos, const std::string &);
	const DualHeight &getBasicHeight();
	QPoint pointAt(int, AnchorType anchor = AnchorType::Left);
	QRect rectBetween(int from, int to);
	void mouseClick(const QPoint &);

	const std::vector<ExpressionElement> &getElements();

	ExpressionBase *clone() const;
};

