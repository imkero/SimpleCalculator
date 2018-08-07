#include "ExpressionRect.h"
#include "Enums.h"

DualHeight::DualHeight() : Ascent(0), Descent(0)
{
}

DualHeight::DualHeight(int asc, int desc) : Ascent(asc), Descent(desc)
{
}

int DualHeight::total()
{
	return Ascent + Descent;
}
