#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type) : ExprType(type)
{
}

int ExpressionBase::getWidth()
{
	return Width;
}

int ExpressionBase::getHeight()
{
	return Height;
}

bool ExpressionBase::validate()
{
	return true;
}
