#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type, ExpressionBase *parent) : Type(type), Parent(parent)
{
}

ExpressionBase * ExpressionBase::getParent()
{
	return Parent;
}

ExpressionBase::~ExpressionBase()
{
}
