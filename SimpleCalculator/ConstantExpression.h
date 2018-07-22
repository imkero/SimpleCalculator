#pragma once
#include "ExpressionBase.h"
#include "ComputableExpression.h"
#include <string>
class ConstantExpression : public ComputableExpression
{
private:
	std::string Digits;
public:
	ConstantExpression(char digit);
	~ConstantExpression();
	
	virtual void computeRect();
	virtual double computeValue();

	virtual ExpressionBase *findSlibing(ExpressionBase *self, Direction dir);
	virtual int getLength();
	virtual bool insertAt(KbButtonName, int);

	static ConstantExpression* fromButtonName(KbButtonName);
};

