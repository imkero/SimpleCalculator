#pragma once
#include "ExpressionBase.h"
#include "HorizontalExpression.h"
#include "VerticalExpressionBase.h"
#include <QSize>
struct ExpressionPointerEx
{
	ExpressionBase *Expr = nullptr;
	int Pos = 0;

	bool isCursor();
	bool available();

	ExpressionPointerEx getParentExpr();
	ExpressionPointerEx enterExpr(Direction from);
};

struct Cursor
{
	HorizontalExpression *FocusdExpr;
	int Pos;

	bool available() const;
};

class CursorMgr
{
private:
	static int CursorWidth;
	Cursor Current;

public:
	CursorMgr();
	
	static void updateParam();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	
	void brighten();

	const Cursor & get() const;
	void set(HorizontalExpression *, int);
	void setWithoutBrighten(HorizontalExpression *, int);

	ExpressionPointerEx getPointer() const;
	void setPointer(ExpressionPointerEx);

	void moveToFront();
	void moveToBack();

	QRect getRect();

	~CursorMgr();
};

