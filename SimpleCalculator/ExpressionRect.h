#pragma once
#include "Enums.h"
#include <QPoint>

struct DualHeight
{
	int Ascent;
	int Descent;
	
	DualHeight();
	DualHeight(int asc, int desc);

	int total() const;
	void merge(const DualHeight &);
};

struct ExpressionRect
{
	QPoint Pos;
	int Width;
	DualHeight Height;

	bool visible();
};

struct AnchoredPoint
{
	AnchorType Anchor = AnchorType::Left;
	QPoint Pos = QPoint(0, 0);
};
