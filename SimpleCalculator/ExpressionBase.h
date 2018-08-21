#pragma once
#include "Enums.h"
#include "ValidateResult.h"
#include "ExpressionRect.h"
#include "ComputeResult.h"
#include <QPainter>
#include <QPoint>

class ExpressionBase
{
protected:
	ExpressionBase *Parent;
public:
	const ExpressionType Type;
	ExpressionRect Rect;

	ExpressionBase(ExpressionType, ExpressionBase *parent);
	ExpressionBase *getParent();
	virtual void setParent(ExpressionBase *);
	virtual ComputeResult computeValue() = 0;
	virtual void computeSize() = 0;
	virtual void computePosition(AnchoredPoint) = 0;
	virtual ValidateResult validate() = 0;
	virtual int getLength() = 0;
	virtual int findChildPosition(ExpressionBase *) = 0;
	virtual void draw(QPainter *) = 0;
	virtual void remove(ExpressionBase *, bool moveCursor) = 0;
	virtual void mouseClick(const QPoint &) = 0;

	template <class T>
	T *as();

	virtual ~ExpressionBase();
};

template<class T>
inline T * ExpressionBase::as()
{
	return static_cast<T *>(this);
}
