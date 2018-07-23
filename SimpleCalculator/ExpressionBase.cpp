#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type, ExpressionBase *parent) : Type(type), Parent(parent)
{
}

ExpressionBase * ExpressionBase::getParent()
{
	return Parent;
}

ValidateResult ExpressionBase::validate()
{
	return ValidateResult();
}

ExpressionBase::~ExpressionBase()
{
}
