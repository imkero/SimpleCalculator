#pragma once
#include "Enums.h"
#include <QPoint>

struct DualHeight
{
	int Ascent;
	int Descent;
	
	DualHeight();
	DualHeight(int asc, int desc);

	int total();
};

struct ExpressionRect
{
	QPoint Pos;
	int Width;
	DualHeight Height;
};

