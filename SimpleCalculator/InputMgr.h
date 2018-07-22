#pragma once
#include "ComputableExpression.h"
class InputMgr
{
public:
	ExpressionBase *Focus = nullptr;
	int CursorPos = 0;

	InputMgr();
	~InputMgr();

	void handle(KbButtonName);
	void cursorMove(Direction dir);
};

