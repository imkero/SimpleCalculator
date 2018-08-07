#pragma once
#include "ExpressionBase.h"
#include "HorizontalExpression.h"
#include "VerticalExpressionBase.h"

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

	bool available();
};

class CursorMgr
{
private:
	Cursor CurCursor;

public:
	CursorMgr();
	
	void moveLeft();
	void moveRight();
	void set(HorizontalExpression *, int);

	Cursor get() const;
	ExpressionPointerEx getPointer() const;
	void setPointer(ExpressionPointerEx);
	QRect getRect();

	~CursorMgr();
};

