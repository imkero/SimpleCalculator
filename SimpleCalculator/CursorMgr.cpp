#include "CursorMgr.h"
#include "VerticalExpressionBase.h"
#include "Util.h"
#include <iostream>
#include "GlobalMgr.h"

bool ExpressionPointerEx::isCursor()
{
	return Expr != nullptr && Expr->Type == Horizontal;
}

bool ExpressionPointerEx::available()
{
	return Expr != nullptr;
}

ExpressionPointerEx ExpressionPointerEx::getParentExpr()
{
	ExpressionPointerEx node;
	if (available())
	{
		node.Expr = Expr->getParent();
		if (node.Expr != nullptr)
		{
			node.Pos = node.Expr->findChildPosition(Expr);
		}
	}
	return node;
}

ExpressionPointerEx ExpressionPointerEx::enterExpr(Direction from)
{
	ExpressionPointerEx node;
	if (available())
	{
		switch (Expr->Type)
		{
		case Horizontal:
		{
			auto horExpr = Expr->as<HorizontalExpression>();
			if (horExpr->Elements[Pos].isExpression())
			{
				node.Expr = horExpr->Elements[Pos].Data.Expr;
				if (node.Expr->Type == Vertical)
				{
					node.Expr =
						node.Expr->as<VerticalExpressionBase>()->
						ChildrenArray[from == Direction::Right ? node.Expr->getLength() - 1 : 0];
				}
				node.Pos = from == Direction::Right ? node.Expr->getLength() : 0;
			}
		}
		break;
		case Vertical:
		{
			node.Expr =
				Expr->as<VerticalExpressionBase>()->
				ChildrenArray[Pos];
			node.Pos = from == Direction::Right ? node.Expr->getLength() : 0;
		}
		break;
		}

	}
	return node;
}

QSize CursorMgr::CursorSize(0, 0);

CursorMgr::CursorMgr()
{
}

void CursorMgr::updateParam()
{
	CursorSize.setWidth(3);
	CursorSize.setHeight(g_Data->Visual.PanelExprHeight.total());
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

void CursorMgr::set(HorizontalExpression *expr, int pos)
{
	CurCursor.FocusdExpr = expr;
	if (expr != nullptr)
	{
		CurCursor.Pos = clamp(pos, 0, expr->getLength());
	}
	else
	{
		std::cerr << "CursorMgr: set focus failed. expr == null." << std::endl;
		CurCursor.Pos = pos;
	}
}

Cursor CursorMgr::get() const
{
	return CurCursor;
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
		set(pointer.Expr->as<HorizontalExpression>(), pointer.Pos);
	}
	else
	{
		std::cerr << "CursorMgr: setPointer failed. Expr is not HorizontalExpression." << std::endl;
	}
}

QRect CursorMgr::getRect()
{
	QPoint point = CurCursor.FocusdExpr->pointAt(CurCursor.Pos, AnchorType::TopLeft);
	return QRect(point, CursorSize);
}

CursorMgr::~CursorMgr()
{
}

bool Cursor::available()
{
	return FocusdExpr != nullptr;
}
