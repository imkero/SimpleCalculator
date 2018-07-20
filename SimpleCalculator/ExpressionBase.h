#pragma once
#include "Enums.h"
#include "ExpressionRect.h"
class ExpressionBase
{
protected:
	ExpressionRect Rect;
public:
	const ExpressionType Type;

	ExpressionBase(ExpressionType);
	virtual double calcValue() = 0;
	virtual void calcRect() = 0;
	const ExpressionRect &getRect();
	virtual bool validate();
	virtual ~ExpressionBase() = 0;
};