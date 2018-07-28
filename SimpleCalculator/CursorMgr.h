#pragma once
#include "HorizontalExpression.h"
class CursorMgr
{
public:
	CursorMgr();
	void Focus(HorizontalExpression *, int index = 0);
	void MoveLeft();
	void MoveRight();
	~CursorMgr();
};

