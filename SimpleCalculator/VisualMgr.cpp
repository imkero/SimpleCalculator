#include "VisualMgr.h"
#include <QFontMetrics>
#include <EnumConvert.h>
#include <GlobalMgr.h>
#include "CursorMgr.h"

VisualMgr::VisualMgr() :
	PanelExprFont("Microsoft YaHei UI", 16),
	PanelSubExprFont("Microsoft YaHei UI", 12),
	PanelMainColor(0, 0, 0),
	PanelSubColor(128, 128, 128),
	PanelFocusBgColor(254, 254, 254),
	PanelCursorColor(175, 39, 56)
{
	
}

void VisualMgr::updateParamCache()
{
	QFontMetrics exprFontMetrics(PanelExprFont);
	QFontMetrics exprSubFontMetrics(PanelSubExprFont);

	PanelExprHeight = DualHeight(exprFontMetrics.height() / 2, exprFontMetrics.height() / 2);
	PanelSubExprHeight = DualHeight(exprSubFontMetrics.height() / 2, exprSubFontMetrics.height() / 2);

	ExprSuperscriptDelta = PanelExprHeight.Ascent * 1 / 4;
	SubExprSuperscriptDelta = PanelSubExprHeight.Ascent * 1 / 2;

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

VisualMgr::~VisualMgr()
{
}
