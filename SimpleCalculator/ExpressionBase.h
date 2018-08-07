#pragma once
#include "Enums.h"
#include "ValidateResult.h"
#include "ExpressionRect.h"
#include "QPainter.h"

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
	virtual void computeSize() = 0;
	virtual void computePosition() = 0;
	virtual ValidateResult validate() = 0;
	virtual int getLength() = 0;
	virtual int findChildPosition(ExpressionBase *) = 0;
	virtual void draw(QPainter *) = 0;

	template <class T>
	T *as();

	virtual ~ExpressionBase() = 0;
};

template<class T>
inline T * ExpressionBase::as()
{
	return static_cast<T *>(this);
}
