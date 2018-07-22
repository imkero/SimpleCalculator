#pragma once
#include "Enums.h"
#include "ExpressionRect.h"
class ExpressionBase
{
public:
	const ExpressionType Type;
	ExpressionRect Rect;
	ExpressionBase *Parent = nullptr;

	ExpressionBase(ExpressionType);
	virtual ~ExpressionBase() = 0;

	virtual void computeRect() = 0;
	virtual bool validate();
	bool isComputable();
	ExpressionBase *getSlibing(Direction dir);
	virtual ExpressionBase *findSlibing(ExpressionBase *self, Direction dir) = 0;
	virtual int getLength() = 0;
	virtual bool insertAt(KbButtonName, int) = 0;
	bool insertBeside(KbButtonName, Direction dir);

	template <class T>
	T *to()
	{
		return static_cast<T *>(this);
	}

};
