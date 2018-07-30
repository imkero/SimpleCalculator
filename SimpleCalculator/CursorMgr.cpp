#include "CursorMgr.h"
#include "VerticalExpressionBase.h"
#include <iostream>

CursorMgr::CursorMgr()
{
}


void CursorMgr::moveLeft()
{
	ExpressionPointerEx pointer = getPointer();
	if (!pointer.available()) return;

	if (pointer.Pos == 0)
	{
		pointer = pointer.getParentExpr();
		if (!pointer.available()) return;
		
		if (pointer.Expr->Type != Horizontal)
		{
			if (pointer.Pos > 0)
			{
				pointer.Pos--;
				pointer = pointer.enterExpr(Direction::Right);
			}
			else
			{
				pointer = pointer.getParentExpr();
			}
		}
		else
		{
			// fix between pow(^) and expr
			auto horExpr = pointer.Expr->as<HorizontalExpression>();
			if (pointer.Pos > 0 && horExpr->Elements[pointer.Pos - 1].isToken(Pow))
			{
				pointer.Pos--;
			}
		}
	}
	else
	{
		pointer.Pos--;
		if (CurCursor.FocusdExpr->Elements[pointer.Pos].isExpression())
		{
			pointer = pointer.enterExpr(Direction::Right);
		}
	}
	setPointer(pointer);
}

void CursorMgr::moveRight()
{
	ExpressionPointerEx pointer = getPointer();
	if (!pointer.available()) return;

	if (pointer.Pos == pointer.Expr->getLength())
	{
		pointer = pointer.getParentExpr();
		
		if (!pointer.available()) return;
		
		if (pointer.Expr->Type != Horizontal)
		{
			if (pointer.Pos < pointer.Expr->getLength() - 1)
			{
				pointer.Pos++;
				pointer = pointer.enterExpr(Direction::Left);
			}
			else
			{
				pointer = pointer.getParentExpr();
				pointer.Pos++;
			}
		}
		else
		{
			if (pointer.Pos != pointer.Expr->getLength())
				pointer.Pos++;
		}
	}
	else
	{
		if (CurCursor.FocusdExpr->Elements[pointer.Pos].isExpression())
		{
			pointer = pointer.enterExpr(Direction::Left);
		}
		else
		{
			pointer.Pos++;
			// fix between pow(^) and expr
			auto horExpr = pointer.Expr->as<HorizontalExpression>();
			if (pointer.Pos > 0 && horExpr->Elements[pointer.Pos - 1].isToken(Pow))
			{
				pointer = pointer.enterExpr(Direction::Left);
			}
		}
	}
	setPointer(pointer);
}


ExpressionPointerEx CursorMgr::getPointer() const
{
	ExpressionPointerEx pointer;
	pointer.Expr = CurCursor.FocusdExpr;
	pointer.Pos = CurCursor.Pos;
	return pointer;
}

void CursorMgr::setPointer(ExpressionPointerEx pointer)
{
	if (pointer.available() && pointer.Expr->Type == Horizontal)
	{
		CurCursor.FocusdExpr = pointer.Expr->as<HorizontalExpression>();
		CurCursor.Pos = pointer.Pos;
	}
	else
	{
		std::cout << "CursorMgr: setPointer failed." << std::endl;
	}
}


CursorMgr::~CursorMgr()
{
}
