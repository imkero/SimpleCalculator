#pragma once
#include "Enums.h"
#include <QPoint>
#include <QRect>

struct DualHeight
{
	int Ascent;
	int Descent;
	
	DualHeight();
	DualHeight(int asc, int desc);

	int total() const;
	void merge(const DualHeight &);
};

struct AnchoredPoint
{
	AnchorType Anchor = AnchorType::Left;
	QPoint Pos = QPoint(0, 0);
};


struct ExpressionRect
{
	QPoint Pos;
	int Width;
	DualHeight Height;

	bool visible() const;
	void setPos(AnchoredPoint);
	QRect getRect() const;
};

