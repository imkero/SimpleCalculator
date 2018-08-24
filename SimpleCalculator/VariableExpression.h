#pragma once
#include "ExpressionBase.h"
#include <string>
#include <unordered_map>

class VariableExpression :
	public ExpressionBase
{
protected:
	std::string VarName;
	std::unordered_map<std::string, std::pair<int, int>> WidthCache;
public:
	VariableExpression(ExpressionBase *parent, const std::string &varName);

	ComputeResult computeValue();
	void computeSize();
	void computePosition(AnchoredPoint);
	void draw(QPainter *);
	void mouseClick(const QPoint &);
	int getLength();
	void remove(ExpressionBase *, bool moveCursor);
	ValidateResult validate();
	int findChildPosition(ExpressionBase *);

	~VariableExpression();
};

