#pragma once
#include <QFont>
#include <QColor>
#include <unordered_map>
#include "Enums.h"
#include "ExpressionElement.h"
#include <QRect>
#include <QPen>
#include "ExpressionRect.h"

class VisualMgr
{
private:
	const static int ScrollYReserved = 20;
	const static int ScrollXReserved = 40;
public:
	QFont PanelExprFont;
	QFont PanelSubExprFont;

	QColor PanelMainColor;
	QColor PanelSubColor;
	QColor PanelFocusBgColor;
	QColor PanelCursorColor;
	QColor PanelErrorBgColor;
	QPen PenFocusUnderline;

	QRect VisibleRect;
	QPoint ExprPosiiton;

	DualHeight PanelExprHeight;
	int BasicCharHeightDelta;
	int SubBasicCharHeightDelta;
	std::unordered_map<TokenType, int> PanelTokenWidth;

	DualHeight PanelSubExprHeight;
	std::unordered_map<TokenType, int> PanelSubTokenWidth;

	int ExprSuperscriptDelta;
	int SubExprSuperscriptDelta;

	VisualMgr();
	~VisualMgr();

	void updateParamCache();
	void updateTokenWidth(TokenType, char, const QFontMetrics &, const QFontMetrics &);
	void updateTokenWidth(TokenType, const char *, const QFontMetrics &, const QFontMetrics &);
	std::pair<int, int> getWidth(const char *);
	void ensureCursorInScreen();
	void exprPosLimit();

	void updateVisibleRectPos();
	void updateVisibleRectSize(QSize);

	void smartMoveExpr(int dx, int dy);
};
