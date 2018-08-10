#include "ExpressionRect.h"
#include "Enums.h"
#include "GlobalMgr.h"
#include <QRect>

DualHeight::DualHeight() : Ascent(0), Descent(0)
{
}

DualHeight::DualHeight(int asc, int desc) : Ascent(asc), Descent(desc)
{
}

int DualHeight::total() const
{
	return Ascent + Descent;
}

void DualHeight::merge(const DualHeight &another)
{
	if (another.Ascent > Ascent)
		Ascent = another.Ascent;
	if (another.Descent > Descent)
		Descent = another.Descent;
}

bool ExpressionRect::visible()
{
	return g_Data->Visual.VisibleRect.intersects(QRect(Pos - QPoint(0, Height.Ascent), Pos + QPoint(Width, Height.Descent)));
}
