#pragma once
#include <QFont>
#include <QColor>
#include <unordered_map>
#include "Enums.h"
#include "ExpressionElement.h"
#include <QRect>
#include "ExpressionRect.h"

class VisualMgr
{
public:
	QFont KeyBoardFont;
	QFont KeyBoardDigitFont;
	QFont PanelResultFont;
	QFont PanelExprFont;

	QColor PanelMainColor;
	QColor PanelSubColor;
	QColor PanelFocusBgColor;
	QColor PanelCursorColor;

	QRect VisibleRect;

	DualHeight PanelExprHeight;
	std::unordered_map<TokenType, int> PanelTokenWidth;

	DualHeight PanelSubExprHeight;
	std::unordered_map<TokenType, int> PanelSubTokenWidth;

	int ExprSuperscriptDelta;
	int SubExprSuperscriptDelta;

	QPoint ExprPosiiton;

	VisualMgr();
	~VisualMgr();

	void updateParamCache();
	void updateTokenWidth(TokenType, char, const QFontMetrics &, const QFontMetrics &);
	void drawToken(QPainter *, QPoint &, TokenType);
};
