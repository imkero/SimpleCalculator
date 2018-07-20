#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type) : Type(type)
{
}


const ExpressionRect &ExpressionBase::getRect()
{
	return Rect;
}

bool ExpressionBase::validate()
{
	return true;
}

ExpressionBase::~ExpressionBase()
{
}
