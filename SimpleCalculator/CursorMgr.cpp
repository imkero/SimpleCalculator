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
				if (horExpr->Elements[Pos].Data.Expr->Type == Variable)
				{
					node.Expr = Expr;
					node.Pos = from == Direction::Left ? Pos + 1 : Pos;
				}
				else
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

int CursorMgr::CursorWidth = 3;

CursorMgr::CursorMgr()
{
}

void CursorMgr::updateParam()
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
		switch (pointer.Expr->Type)
		{
		case Vertical:
			if (pointer.Pos > 0)
			{
				pointer.Pos--;
				pointer = pointer.enterExpr(Direction::Right);
			}
			else
			{
				pointer = pointer.getParentExpr();
			}
			break;
		case Horizontal:
			// fix between pow(^) and expr
			auto horExpr = pointer.Expr->as<HorizontalExpression>();
			if (pointer.Pos > 0 && horExpr->Elements[pointer.Pos - 1].isToken(Pow))
			{
				pointer.Pos--;
			}
			break;
		}
	}
	else
	{
		pointer.Pos--;
		if (Current.FocusdExpr->Elements[pointer.Pos].isExpression())
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
		
		switch (pointer.Expr->Type)
		{
		case Vertical:
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
			break;
		case Horizontal:
			if (pointer.Pos != pointer.Expr->getLength())
				pointer.Pos++;
			break;
		}
	}
	else
	{
		if (Current.FocusdExpr->Elements[pointer.Pos].isExpression())
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

void CursorMgr::brighten()
{
	ArithmeticPanel::getInstance()->brightenCursor();
}

void CursorMgr::set(HorizontalExpression *expr, int pos)
{
	Current.FocusdExpr = expr;
	if (expr != nullptr)
	{
		Current.Pos = clamp(pos, 0, expr->getLength());
		brighten();
	}
	else
	{
		std::cerr << "CursorMgr: set focus failed. expr == null." << std::endl;
		Current.Pos = pos;
	}
}

void CursorMgr::setWithoutBrighten(HorizontalExpression *expr, int pos)
{
	Current.FocusdExpr = expr;
	if (expr != nullptr)
	{
		Current.Pos = clamp(pos, 0, expr->getLength());
	}
	else
	{
		std::cerr << "CursorMgr: set focus failed. expr == null." << std::endl;
		Current.Pos = pos;
	}
}

const Cursor &CursorMgr::get() const
{
	return Current;
}

ExpressionPointerEx CursorMgr::getPointer() const
{
	ExpressionPointerEx pointer;
	pointer.Expr = Current.FocusdExpr;
	pointer.Pos = Current.Pos;
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
	brighten();
}

QRect CursorMgr::getRect()
{
	QPoint point = Current.FocusdExpr->pointAt(Current.Pos, AnchorType::TopLeft);
	return QRect(point, QSize(CursorWidth, Current.FocusdExpr->getBasicHeight().total()));
}

CursorMgr::~CursorMgr()
{
}

bool Cursor::available() const
{
	return FocusdExpr != nullptr;
}
