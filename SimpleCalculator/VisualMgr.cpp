#include "VisualMgr.h"
#include <QFontMetrics>
#include <EnumConvert.h>
#include <QDebug>
#include <QVector>
#include <GlobalMgr.h>
#include "CursorMgr.h"

VisualMgr::VisualMgr() :
	PanelExprFont("Microsoft YaHei UI", 16),
	PanelSubExprFont("Microsoft YaHei UI", 14),
	PanelMainColor(0, 0, 0),
	PanelSubColor(128, 128, 128),
	PanelFocusBgColor(254, 254, 254),
	PanelCursorColor(175, 39, 56),
	ExprPosiiton(0, 0)
{	
	QVector<qreal> dashes;
	dashes << 2 << 2;
	PenEmptyBlock.setDashPattern(dashes);
	PenEmptyBlock.setWidth(1);
	PenEmptyBlock.setColor(PanelSubColor);
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
	updateTokenWidth(Mul, '*', exprFontMetrics, exprSubFontMetrics);
	updateTokenWidth(Div, '/', exprFontMetrics, exprSubFontMetrics);
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
	
}

void VisualMgr::updateTokenWidth(TokenType token, char c, const QFontMetrics &exprFontMetrics, const QFontMetrics &exprSubFontMetrics)
{
	PanelTokenWidth[token] = exprFontMetrics.width(c);
	PanelSubTokenWidth[token] = exprSubFontMetrics.width(c);
}

void VisualMgr::ensureCursorInScreen()
{
	QRect cursorRect = g_Data->Cursor.getRect();
	bool modified = false;

	if (cursorRect.top() - 20 < VisibleRect.top())
	{
		modified = true;
		ExprPosiiton.ry() += VisibleRect.top() - cursorRect.top() + 20;
	}
	else if (cursorRect.bottom() + 20 > VisibleRect.bottom())
	{
		modified = true;
		ExprPosiiton.ry() -= cursorRect.bottom() - VisibleRect.bottom() + 20;
	}

	if (cursorRect.left() - 40 < VisibleRect.left())
	{
		modified = true;
		ExprPosiiton.rx() += VisibleRect.left() - cursorRect.left() + 40;
	}
	else if (cursorRect.right() > VisibleRect.right() - 40)
	{
		modified = true;
		ExprPosiiton.rx() -= cursorRect.right() - VisibleRect.right() + 40;
	}

	if (modified)
	{
		updateVisibleRectPos();
	}
}

void VisualMgr::exprPosLimit()
{
	bool modified = false;
	
	if (g_Data->RootExpr->Rect.Height.total() > VisibleRect.height() && VisibleRect.bottom() > g_Data->RootExpr->Rect.Height.total())
	{
		modified = true;
		ExprPosiiton.setY(VisibleRect.height() - g_Data->RootExpr->Rect.Height.total());
	}

	if (g_Data->RootExpr->Rect.Width > VisibleRect.width() && VisibleRect.right() > g_Data->RootExpr->Rect.Width - 40)
	{
		modified = true;
		ExprPosiiton.setX(VisibleRect.width() - g_Data->RootExpr->Rect.Width - 40);
	}

	if ((g_Data->RootExpr->Rect.Width + 40 < VisibleRect.width() && ExprPosiiton.x() < 0) || ExprPosiiton.x() > 0)
	{
		modified = true;
		ExprPosiiton.setX(0);
	}

	if (ExprPosiiton.y() > g_Data->RootExpr->Rect.Height.Ascent)
	{
		modified = true;
		ExprPosiiton.setY(g_Data->RootExpr->Rect.Height.Ascent);
	}

	if (modified)
	{
		updateVisibleRectPos();
	}
}

void VisualMgr::updateVisibleRectPos()
{
	VisibleRect.setTopLeft(-ExprPosiiton);
}

void VisualMgr::updateVisibleRectSize(QSize size)
{
	VisibleRect.setSize(size);
}

VisualMgr::~VisualMgr()
{
}
