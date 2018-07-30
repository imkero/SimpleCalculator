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
	_Length
};

enum TokenType
{
	Add,
	Sub,
	Mul,
	Div,
	Pow,
	Mod,
	LeftBracket,
	RightBracket,
	Digit0,
	Digit1,
	Digit2,
	Digit3,
	Digit4,
	Digit5,
	Digit6,
	Digit7,
	Digit8,
	Digit9,
	DigitDot
};

enum ExpressionInterpretState {
	Begin, // begin of the expression
	ArithmeticOperator, // + - * / %
	PowerOperator, // ^
	Sign, // positive or negative sign
	ConstInt, // digits only
	ConstDouble, // dot after digits
	SubExpression, // variable or sub-expression 
				   // (allow omitting the multiplication)
	SubExpressionPower
};

enum ExpressionType
{
	Horizontal,
	Vertical,
};

enum ValidateErrorType
{
	Success,
	NotMatchingBracket,
	UnexceptedToken,
	UnexceptedDigit,
	InternalError,
};

enum class Direction
{
	Left,
	Right
};