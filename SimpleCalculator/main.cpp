#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "EnumConvert.h"
#include "FractionExpression.h"
#include <iostream>

int main(int argc, char *argv[])
{
	CursorMgr cursor;
	ExpressionPointerEx p = ExpressionPointerEx();
	HorizontalExpression * expr = new HorizontalExpression(nullptr);
	HorizontalExpression * exprPow = new HorizontalExpression(expr);
	FractionExpression *exprFrac = new FractionExpression(expr);
	p.Expr = expr;
	p.Pos = 0;
	cursor.setPointer(p);
	expr->Elements.push_back(EnumConvert::char2token('1'));
	expr->Elements.push_back(EnumConvert::char2token('+'));
	expr->Elements.push_back(ExpressionElement(exprFrac));
	expr->Elements.push_back(EnumConvert::char2token('+'));
	expr->Elements.push_back(EnumConvert::char2token('2'));
	expr->Elements.push_back(EnumConvert::char2token('^'));

	exprPow->Elements.push_back(EnumConvert::char2token('3'));

	exprFrac->ChildrenArray[0]->Elements.push_back(EnumConvert::char2token('1'));
	exprFrac->ChildrenArray[1]->Elements.push_back(EnumConvert::char2token('2'));

	expr->Elements.push_back(ExpressionElement(exprPow));
	
	
	std::cout << "Calc Result:" << expr->computeValue() << std::endl;
	std::cout << "1+1/2+2^3" << std::endl;

	std::cout << "Pointer: Main @ " << p.Pos << std::endl;
	for (int i = 0; i < 13; i++)
	{
		cursor.moveRight();
		p = cursor.getPointer();
		if (p.Expr == expr)
		{
			std::cout << "Pointer: Main @ " << p.Pos;
		}
		else if (p.Expr == exprPow)
		{
			std::cout << "Pointer: Pow @ " << p.Pos;
		}
		else if (p.Expr == exprFrac)
		{
			std::cout << "Pointer: Frac @ " << p.Pos;
		}
		else if (p.Expr == exprFrac->ChildrenArray[0])
		{
			std::cout << "Pointer: FracA @ " << p.Pos;
		}
		else if (p.Expr == exprFrac->ChildrenArray[1])
		{
			std::cout << "Pointer: FracB @ " << p.Pos;
		}
		else
		{
			std::cout << "Pointer: Unknown @ " << p.Pos;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 13; i++)
	{
		cursor.moveLeft();
		p = cursor.getPointer();
		if (p.Expr == expr)
		{
			std::cout << "Pointer: Main @ " << p.Pos;
		}
		else if (p.Expr == exprPow)
		{
			std::cout << "Pointer: Pow @ " << p.Pos;
		}
		else if (p.Expr == exprFrac)
		{
			std::cout << "Pointer: Frac @ " << p.Pos;
		}
		else if (p.Expr == exprFrac->ChildrenArray[0])
		{
			std::cout << "Pointer: FracA @ " << p.Pos;
		}
		else if (p.Expr == exprFrac->ChildrenArray[1])
		{
			std::cout << "Pointer: FracB @ " << p.Pos;
		}
		else
		{
			std::cout << "Pointer: Unknown @ " << p.Pos;
		}
		std::cout << std::endl;
	}
	getchar();
	return 0;

	QApplication app(argc, argv);
	MainWindow mainWnd;
	mainWnd.show();
	return app.exec();
}
