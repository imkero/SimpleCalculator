#pragma once
#include "Enums.h"
#include "ExpressionRect.h"
#include "ValidateResult.h"

class ExpressionBase
{
protected:
	ExpressionBase *Parent;
public:
	const ExpressionType Type;
	ExpressionRect Rect;

	ExpressionBase(ExpressionType, ExpressionBase *parent);
	ExpressionBase *getParent();
	virtual double computeValue() = 0;
	virtual void computeRect() = 0;
	virtual ValidateResult validate() = 0;
	virtual ~ExpressionBase() = 0;
};