#pragma once
#include "Enums.h"
#include <QPoint>
#include <QRect>

struct DualHeight
{
	int Ascent = 0;
	int Descent = 0;
	
	DualHeight();
	DualHeight(int asc, int desc);

	int total() const;
	void merge(const DualHeight &);
};

struct AnchoredPoint
{
	AnchorType Anchor = AnchorType::Left;
	QPoint Pos = QPoint(0, 0);
	AnchoredPoint()
	{

	}
	AnchoredPoint(QPoint point, AnchorType anchor) : Pos(point), Anchor(anchor)
	{

	}
};


struct ExpressionRect
{
	QPoint Pos;
	int Width;
	DualHeight Height;

	bool visible() const;
	void setPosWithAnchor(AnchoredPoint);
	QRect getRect() const;
};

