#include "VisualMgr.h"
#include <QFontMetrics>
#include <QVector>
#include <QDebug>
#include "GlobalMgr.h"
#include "CursorMgr.h"
#include "HorizontalExpression.h"
#include "FractionExpression.h"
#include "SimpleFuncExpression.h"
#include "SinExpression.h"
#include "CosExpression.h"
#include "TanExpression.h"
#include "SindExpression.h"
#include "CosdExpression.h"
#include "TandExpression.h"
#include "ArcsinExpression.h"
#include "ArccosExpression.h"
#include "ArctanExpression.h"
#include "AbsExpression.h"
#include "LnExpression.h"
#include "SqrtExpression.h"
#include "SqrtXYExpression.h"
#include "LogExpression.h"
#include "Log10Expression.h"

#pragma execution_character_set("utf-8")

VisualMgr::VisualMgr() :
	PanelExprFont("Microsoft YaHei UI", 16),
	PanelSubExprFont("Microsoft YaHei UI", 14),
	PanelMainColor(0, 0, 0),
	PanelSubColor(96, 96, 96),
	PanelFocusBgColor(254, 254, 254),
	PanelCursorColor(175, 39, 56),
	PanelErrorBgColor(255, 168, 168),
	ExprPosiiton(0, 0)
{	
	QVector<qreal> dashes;
	dashes << 2 << 2;
	PenFocusUnderline.setDashPattern(dashes);
	PenFocusUnderline.setWidth(2);
	PenFocusUnderline.setColor(PanelMainColor);
}

void VisualMgr::updateParamCache()
{
	QFontMetrics exprFontMetrics(PanelExprFont);
	QFontMetrics exprSubFontMetrics(PanelSubExprFont);

	PanelExprHeight = DualHeight(exprFontMetrics.height() / 2, exprFontMetrics.height() / 2);
	PanelSubExprHeight = DualHeight(exprSubFontMetrics.height() / 2, exprSubFontMetrics.height() / 2);

	ExprSuperscriptDelta = PanelExprHeight.Ascent;
	SubExprSuperscriptDelta = PanelSubExprHeight.Ascent;

	BasicCharHeightDelta = exprFontMetrics.ascent() - PanelExprHeight.Ascent;
	SubBasicCharHeightDelta = exprSubFontMetrics.ascent() - PanelSubExprHeight.Ascent;

	updateTokenWidth(Add, '+', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Sub, '-', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Mul, "¡Á", exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Div, "¡Â", exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Mod, '%', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(LeftBracket, '(', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(RightBracket, ')', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit0, '0', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit1, '1', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit2, '2', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit3, '3', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit4, '4', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit5, '5', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit6, '6', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit7, '7', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit8, '8', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Digit9, '9', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(DigitDot, '.', exprFontMetrics, exprSubFontMetrics);
	PanelTokenWidth[Pow] = 0;
	PanelSubTokenWidth[Pow] = 0;

	CursorMgr::updateParam();
	HorizontalExpression::updateParam();
	FractionExpression::updateParam();
	AbsExpression::updateParam();
	LogExpression::updateParam();
	SqrtExpression::updateParam();
	SqrtXYExpression::updateParam();
	SimpleFuncExpression<SinExpression>::updateParam();
	SimpleFuncExpression<CosExpression>::updateParam();
	SimpleFuncExpression<TanExpression>::updateParam();
	SimpleFuncExpression<SindExpression>::updateParam();
	SimpleFuncExpression<CosdExpression>::updateParam();
	SimpleFuncExpression<TandExpression>::updateParam();
	SimpleFuncExpression<ArcsinExpression>::updateParam();
	SimpleFuncExpression<ArccosExpression>::updateParam();
	SimpleFuncExpression<ArctanExpression>::updateParam();
	SimpleFuncExpression<LnExpression>::updateParam();
	SimpleFuncExpression<Log10Expression>::updateParam();
}

void VisualMgr::updateTokenWidth(TokenType token, char c, const QFontMetrics &exprFontMetrics, const QFontMetrics &exprSubFontMetrics)
{
	PanelTokenWidth[token] = exprFontMetrics.width(c);
	PanelSubTokenWidth[token] = exprSubFontMetrics.width(c);
}

void VisualMgr::updateTokenWidth(TokenType token, const char *s, const QFontMetrics &exprFontMetrics, const QFontMetrics &exprSubFontMetrics)
{
	PanelTokenWidth[token] = exprFontMetrics.width(s);
	PanelSubTokenWidth[token] = exprSubFontMetrics.width(s);
}

std::pair<int, int> VisualMgr::getWidth(const char *s)
{
	QFontMetrics exprFontMetrics(PanelExprFont);
	QFontMetrics exprSubFontMetrics(PanelSubExprFont);
	return std::make_pair(exprFontMetrics.width(s), exprSubFontMetrics.width(s));
}

void VisualMgr::ensureCursorInScreen()
{
	QRect cursorRect = g_Data->Cursor.getRect();
	bool modified = false;

	if (cursorRect.top() < VisibleRect.top() + ScrollYReserved)
	{
		modified = true;
		ExprPosiiton.ry() += VisibleRect.top() - cursorRect.top() + ScrollYReserved;
	}
	else if (cursorRect.bottom() > VisibleRect.bottom() - ScrollYReserved)
	{
		modified = true;
		ExprPosiiton.ry() -= cursorRect.bottom() - VisibleRect.bottom() + ScrollYReserved;
	}

	if (cursorRect.left() < VisibleRect.left() + ScrollXReserved)
	{
		modified = true;
		ExprPosiiton.rx() += VisibleRect.left() - cursorRect.left() + ScrollXReserved;
	}
	else if (cursorRect.left() > VisibleRect.right() - ScrollXReserved)
	{
		modified = true;
		ExprPosiiton.rx() -= cursorRect.left() - VisibleRect.right() + ScrollXReserved;
	}

	if (modified)
	{
		updateVisibleRectPos();
	}
}

void VisualMgr::exprPosLimit()
{
	updateVisibleRectPos();
	bool modified = false;
	bool vScrollable = g_Data->getRootExpr()->Rect.Height.total() > VisibleRect.height() - ScrollYReserved;
	bool hScrollable = g_Data->getRootExpr()->Rect.Width > VisibleRect.width() - ScrollXReserved;

	if (hScrollable)
	{
		// x range left limit
		if (ExprPosiiton.x() > 0)
		{
			modified = true;
			ExprPosiiton.setX(0);
		}
		// x range right limit
		else if (VisibleRect.right() - (ScrollXReserved - 1) > g_Data->getRootExpr()->Rect.Width)
		{
			modified = true;
			ExprPosiiton.setX(VisibleRect.width() - g_Data->getRootExpr()->Rect.Width - ScrollXReserved);
		}
	}
	else
	{
		// horizontal scroll lock
		if (ExprPosiiton.x() != 0)
		{
			modified = true;
			ExprPosiiton.setX(0);
		}
	}

	if (vScrollable)
	{
		// y range bottom limit
		if (VisibleRect.bottom() - (ScrollYReserved - 1) > g_Data->getRootExpr()->Rect.Height.Descent)
		{
			modified = true;
			ExprPosiiton.setY(VisibleRect.height() - g_Data->getRootExpr()->Rect.Height.Descent - ScrollYReserved);
		}
		// y range top limit
		else if (ExprPosiiton.y() > g_Data->getRootExpr()->Rect.Height.Ascent)
		{
			modified = true;
			ExprPosiiton.setY(g_Data->getRootExpr()->Rect.Height.Ascent);
		}
	}
	else
	{
		// vertical scroll lock
		if (ExprPosiiton.y() != g_Data->getRootExpr()->Rect.Height.Ascent)
		{
			modified = true;
			ExprPosiiton.setY(g_Data->getRootExpr()->Rect.Height.Ascent);
		}
	}

	if (modified)
	{
		updateVisibleRectPos();
	}
}

void VisualMgr::updateVisibleRectPos()
{
	VisibleRect.moveTopLeft(-ExprPosiiton);
}

void VisualMgr::updateVisibleRectSize(QSize size)
{
	VisibleRect.setSize(size);
}

void VisualMgr::smartMoveExpr(int dx, int dy)
{
	QPoint exprPosOld = ExprPosiiton;
	if (dx != 0)
		ExprPosiiton.rx() += dx;
	if (dy != 0)
		ExprPosiiton.ry() += dy;
	
	g_Data->Visual.exprPosLimit();
	if (exprPosOld != ExprPosiiton)
	{
		g_Data->repaintExpr();
	}
}

VisualMgr::~VisualMgr()
{
}
