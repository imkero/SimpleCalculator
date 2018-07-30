#pragma once
#include "ExpressionBase.h"
#include "HorizontalExpression.h"
#include "VerticalExpressionBase.h"

struct ExpressionPointerEx
{
	ExpressionBase *Expr = nullptr;
	int Pos = 0;
	bool isCursor()
	{
		return Expr != nullptr && Expr->Type == Horizontal;
	}

	bool available()
	{
		return Expr != nullptr;
	}

	ExpressionPointerEx getParentExpr()
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

	ExpressionPointerEx enterExpr(Direction from)
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

};

struct Cursor
{
	HorizontalExpression *FocusdExpr;
	int Pos;
};

class CursorMgr
{
private:
	Cursor CurCursor;

public:
	CursorMgr();
	
	void moveLeft();
	void moveRight();

	ExpressionPointerEx getPointer() const;
	void setPointer(ExpressionPointerEx);

	~CursorMgr();
};

