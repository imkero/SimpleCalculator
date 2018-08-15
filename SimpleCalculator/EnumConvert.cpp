#include "EnumConvert.h"

#pragma execution_character_set("utf-8")

TokenType EnumConvert::char2token(char c)
{
	switch (c)
	{
	case '+': return Add;
	case '-': return Sub;
	case '*': return Mul;
	case '/': return Div;
	case '^': return Pow;
	case '%': return Mod;
	case '(': return LeftBracket;
	case ')': return RightBracket;
	case '0': return Digit0;
	case '1': return Digit1;
	case '2': return Digit2;
	case '3': return Digit3;
	case '4': return Digit4;
	case '5': return Digit5;
	case '6': return Digit6;
	case '7': return Digit7;
	case '8': return Digit8;
	case '9': return Digit9;
	default:
	case '.': return DigitDot;
	}
}
char EnumConvert::token2char(TokenType token)
{
	switch (token)
	{
	case Add: return '+';
	case Sub: return '-';
	case Mul: return '*';
	case Div: return '/';
	case Pow: return '^';
	case Mod: return '%';
	case LeftBracket: return '(';
	case RightBracket: return ')';
	case Digit0: return '0';
	case Digit1: return '1';
	case Digit2: return '2';
	case Digit3: return '3';
	case Digit4: return '4';
	case Digit5: return '5';
	case Digit6: return '6';
	case Digit7: return '7';
	case Digit8: return '8';
	case Digit9: return '9';
	case DigitDot: return '.';
	default: return ' ';
	}
}

const char * EnumConvert::error2string(ValidateErrorType error)
{
	switch (error)
	{
	case ValidateErrorType::Success:
		return "算式无误";
	case ValidateErrorType::DivideByZero:
		return "0不能作为除数";
	case ValidateErrorType::NotMatchingBracket:
		return "不成对的括号";
	case ValidateErrorType::InternalError:
		return "程序内部错误";
	case ValidateErrorType::UnexceptedDigit:
		return "此处不应有数字";
	case ValidateErrorType::UnexceptedToken:
		return "多余的符号或不完整的表达式";
	case ValidateErrorType::EmptyExpression:
		return "括号内或表达式内为空";
	case ValidateErrorType::ZeroPowZero:
		return "0的0次幂无意义";
	case ValidateErrorType::MathError:
		return "数学错误";
	default:
		return "";
	}
}
