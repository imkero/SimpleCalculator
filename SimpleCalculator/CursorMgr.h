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
	static int CursorWidth;
	Cursor Current;

public:
	CursorMgr();
	
	static void updateParam();

	void moveLeft();
	void moveRight();
	
	void brighten();

	Cursor get() const;
	void set(HorizontalExpression *, int);

	ExpressionPointerEx getPointer() const;
	void setPointer(ExpressionPointerEx);

	QRect getRect();

	~CursorMgr();
};

