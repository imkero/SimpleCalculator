#pragma once
#include <vector>
#include <stack>
#include "Enums.h"
#include "ExpressionElement.h"

struct RpnData{
	bool IsNumber;
	union {
		TokenType Token;
		double Number;
	} Data;
	static RpnData token(TokenType t)
	{
		RpnData ret;
		ret.Data.Token = t;
		ret.IsNumber = false;
		return ret;
	}
	static RpnData number(double n)
	{
		RpnData ret;
		ret.Data.Number = n;
		ret.IsNumber = true;
		return ret;
	}
};

class ReversePolishNotation
{
private:
	std::vector<RpnData> Elements;
	std::stack<TokenType> Stack;
	RpnData LastInput = RpnData::token(Add);
	bool NegativeSign = false;
	int UnclosedLeftBracketCount = 0;
public:
	ReversePolishNotation();
	void inputNumber(double);
	void inputToken(TokenType);

	void endInput();
	double compute();
	static int getTokenPriority(TokenType);
};

