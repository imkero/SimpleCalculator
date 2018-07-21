#pragma once
enum KbButtonType
{
	Normal, // other
	Digit, // 0 - 9
	Op, // + - * /
};

enum KbButtonName
{
	Button0,
	Button1,
	Button2,
	Button3,
	Button4,
	Button5,
	Button6,
	Button7,
	Button8,
	Button9,
	ButtonAdd,
	ButtonSub,
	ButtonMul,
	ButtonDiv,
	ButtonEqual,
	ButtonAnswer,
	ButtonDot,
	ButtonShift,
	ButtonConstant,
	ButtonLn,
	ButtonLog,
	ButtonSqrt,
	ButtonFrac,
	ButtonPow,
	ButtonSin,
	ButtonCos,
	ButtonTan,
	ButtonBracketLeft,
	ButtonBracketRight,
	ButtonSci,
};

enum SymbolType
{
	Add,
	Sub,
	Mul,
	Div,
	LeftBracket,
	RightBracket
};

enum ExpressionType
{
	Symbol,
	Horizontal,
	Constant,
};