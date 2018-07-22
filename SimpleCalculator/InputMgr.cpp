#include "InputMgr.h"
#include "HorizontalExpression.h"

InputMgr::InputMgr()
{
}


InputMgr::~InputMgr()
{
}

void InputMgr::handle(KbButtonName btnName)
{
	if (!Focus->insertAt(btnName, CursorPos))
	{
		if (CursorPos == 0)
			Focus->insertBeside(btnName, LEFT);
		else if (CursorPos == Focus->getLength())
			Focus->insertBeside(btnName, RIGHT);
	}
	if (Focus->Type == Horizontal && Focus->getLength() > 0)
	{
		// focus enter
		Focus = Focus->to<HorizontalExpression>()->Elements[0];
		CursorPos = 0;
	}
	switch (btnName)
	{
	case Button0:
	case Button1:
	case Button2:
	case Button3:
	case Button4:
	case Button5:
	case Button6:
	case Button7:
	case Button8:
	case Button9:
	case ButtonDot:
		cursorMove(RIGHT);
	break;
	}
	

}

void InputMgr::cursorMove(Direction dir)
{
	ExpressionBase *slibing;
	if (dir == RIGHT)
	{
		CursorPos++;
		if (CursorPos > Focus->getLength())
		{
			slibing = Focus->getSlibing(RIGHT);
			if (slibing)
				Focus = slibing;
		}
	}
	else
	{
		CursorPos--;
		
		if (CursorPos < 0)
		{
			slibing = Focus->getSlibing(LEFT);
			if (slibing)
				Focus = slibing;
		}
	}
}
