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

	bool available();
};

class CursorMgr
{
private:
	static QSize CursorSize;
	Cursor CurCursor;

public:
	CursorMgr();
	
	static void updateParam();

	void moveLeft();
	void moveRight();
	void set(HorizontalExpression *, int);

	Cursor get() const;
	ExpressionPointerEx getPointer() const;
	void setPointer(ExpressionPointerEx);
	QRect getRect();

	~CursorMgr();
};

