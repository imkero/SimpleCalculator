#include "ExpressionBase.h"

ExpressionBase::ExpressionBase(ExpressionType type) : Type(type)
{
}

ExpressionBase::~ExpressionBase()
{
}

bool ExpressionBase::validate()
{
	return true;
}

bool ExpressionBase::isComputable()
{
	return Type != Symbol;
}

ExpressionBase * ExpressionBase::getSlibing(Direction dir)
{
	if (Parent != nullptr)
	{
		return Parent->findSlibing(this, dir);
	}
	return nullptr;
}

bool ExpressionBase::insertBeside(KbButtonName btnName, Direction dir)
{
	ExpressionBase *slibing = getSlibing(dir);
	if (slibing != nullptr)
	{
		return slibing->insertAt(btnName, dir == LEFT ? slibing->getLength() : 0);
	}
	return false;
}

