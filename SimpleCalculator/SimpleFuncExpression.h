#pragma once
#include "FuncExpression.h"
#include "GlobalMgr.h"
#include "ExpressionPaintUtil.h"
template <class T>
class SimpleFuncExpression :
	public FuncExpression
{
private:
	static int FuncNameWidth;
	static int FuncNameSubWidth;
	static DualHeight FuncNameHeight;
	static DualHeight FuncNameSubHeight;
public:
	static const char * FuncName;
	SimpleFuncExpression(ExpressionBase * parent);

	void computeFuncNameSize();
	int computeFuncNamePositionPrefix();
	void drawFuncName(QPainter *);
	void mouseClick(const QPoint &);

	static void updateParam();
};

template <class T>
SimpleFuncExpression<T>::SimpleFuncExpression(ExpressionBase * parent) : FuncExpression(parent)
{
}


template <class T>
void SimpleFuncExpression<T>::computeFuncNameSize()
{
	Rect.Width = IsSubExpr ? FuncNameSubWidth : FuncNameWidth;
	Rect.Height = IsSubExpr ? FuncNameHeight : FuncNameSubHeight;
}

template <class T>
int SimpleFuncExpression<T>::computeFuncNamePositionPrefix()
{
	return IsSubExpr ? FuncNameSubWidth : FuncNameWidth;
}
template <class T>
void SimpleFuncExpression<T>::drawFuncName(QPainter *painter)
{
	painter->save();
	painter->setFont(IsSubExpr ? g_Data->Visual.PanelSubExprFont : g_Data->Visual.PanelExprFont);
	painter->drawText(ExpressionPaintUtil::calcDrawTextPrefix(Rect.Pos, IsSubExpr), FuncName);
	painter->restore();
}

template<class T>
void SimpleFuncExpression<T>::mouseClick(const QPoint &mousePoint)
{
	QPoint point = Rect.Pos;
	point.rx() += computeFuncNamePositionPrefix();
	if (mousePoint.x() < point.x())
	{
		g_Data->Cursor.set(ChildrenArray[0], 0);
		g_Data->Cursor.moveLeft();
		return;
	}
	point.rx() += LeftB.RealWidth;
	if (mousePoint.x() < point.x())
	{
		g_Data->Cursor.set(ChildrenArray[0], 0);
		return;
	}
	point.rx() += ChildrenArray[0]->Rect.Width;
	if (mousePoint.x() < point.x())
	{
		ChildrenArray[0]->mouseClick(mousePoint);
		return;
	}
	g_Data->Cursor.set(ChildrenArray[0], ChildrenArray[0]->getLength());
}

template <class T>
void SimpleFuncExpression<T>::updateParam()
{
	QFontMetrics exprFontMetrics(g_Data->Visual.PanelExprFont);
	QFontMetrics exprSubFontMetrics(g_Data->Visual.PanelSubExprFont);
	FuncNameWidth = exprFontMetrics.width(FuncName);
	FuncNameSubWidth = exprSubFontMetrics.width(FuncName);
	FuncNameHeight = g_Data->Visual.PanelExprHeight;
	FuncNameSubHeight = g_Data->Visual.PanelSubExprHeight;
}

template <class T>
int SimpleFuncExpression<T>::FuncNameWidth = 0;
template <class T>
int SimpleFuncExpression<T>::FuncNameSubWidth = 0;
template <class T>
DualHeight SimpleFuncExpression<T>::FuncNameHeight;
template <class T>
DualHeight SimpleFuncExpression<T>::FuncNameSubHeight;
