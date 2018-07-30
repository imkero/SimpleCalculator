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
	virtual int getLength() = 0;
	virtual int findChildPosition(ExpressionBase *) = 0;
	
	template <class T>
	T *as();

	virtual ~ExpressionBase() = 0;
};

template<class T>
inline T * ExpressionBase::as()
{
	return static_cast<T *>(this);
}
