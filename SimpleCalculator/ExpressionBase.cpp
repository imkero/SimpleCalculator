#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type, ExpressionBase *parent) : Type(type), Parent(parent)
{
}

ExpressionBase::ExpressionBase(const ExpressionBase &expr) : Type(expr.Type), Parent(nullptr)
{
}

ExpressionBase * ExpressionBase::getParent()
{
	return Parent;
}

void ExpressionBase::setParent(ExpressionBase *newParent)
{
	Parent = newParent;
}

ExpressionBase::~ExpressionBase()
{
}
