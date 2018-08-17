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

bool ExpressionRect::visible() const
{
	return g_Data->Visual.VisibleRect.intersects(getRect());
}

void ExpressionRect::setPosWithAnchor(AnchoredPoint point)
{
	Pos = point.Pos;
	switch (static_cast<AnchorType>(static_cast<int>(point.Anchor) & 0b1100))
	{
	case AnchorType::Center:
		Pos.rx() -= Width / 2;
		break;
	case AnchorType::Right:
		Pos.rx() -= Width;
		break;
	}
	switch (static_cast<int>(point.Anchor) & 0b11)
	{
	case 0b01: // Top
		Pos.ry() += Height.Ascent;
		break;
	case 0b10: // Bottom
		Pos.ry() -= Height.Descent;
		break;
	}
}

QRect ExpressionRect::getRect() const
{
	return QRect(Pos - QPoint(0, Height.Ascent), Pos + QPoint(Width, Height.Descent));
}
