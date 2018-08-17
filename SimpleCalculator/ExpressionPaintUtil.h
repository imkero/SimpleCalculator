#pragma once
#include "ExpressionElement.h"
#include <QPainter>
#include <QPoint>

class ExpressionPaintUtil
{
public:
	static int computeBracketWidth(int height, bool isSub);
	static void drawLeftBracket(QPainter *painter, QPoint anchorPoint, const ExpressionElement *element);
	static void drawRightBracket(QPainter *painter, QPoint anchorPoint, const ExpressionElement *element);
	static QPoint calcDrawTextPrefix(QPoint, bool);
};

