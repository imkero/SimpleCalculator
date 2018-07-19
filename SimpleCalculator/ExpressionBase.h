#pragma once
#include "Enums.h"

class ExpressionBase
{
protected:
	int Width = 0;
	int Height = 0;
public:
	const ExpressionType ExprType;

	ExpressionBase(ExpressionType);
	virtual double calcValue() = 0;
	virtual void calcRect() = 0;
	int getWidth();
	int getHeight();
	virtual bool validate();
	virtual ~ExpressionBase() = 0;
};