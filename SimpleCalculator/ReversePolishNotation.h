#pragma once
#include <vector>
#include <stack>
#include "Enums.h"
#include "ExpressionElement.h"
#include "ComputeResult.h"
#include "CalcTypes.h"

struct RpnData{
	bool IsNumber;
	union {
		TokenType Token;
		CompType Number;
	} Data;
	int Index;
	static RpnData token(TokenType t, int index)
	{
		RpnData ret;
		ret.Data.Token = t;
		ret.IsNumber = false;
		ret.Index = index;
		return ret;
	}
	static RpnData token(std::pair<TokenType, int> pair)
	{
		RpnData ret;
		ret.Data.Token = pair.first;
		ret.IsNumber = false;
		ret.Index = pair.second;
		return ret;
	}
	static RpnData number(CompType n, int index)
	{
		RpnData ret;
		ret.Data.Number = n;
		ret.IsNumber = true;
		ret.Index = index;
		return ret;
	}
};

class ReversePolishNotation
{
private:
	std::vector<RpnData> Elements;
	std::stack<std::pair<TokenType, int>> Stack;
	RpnData LastInput = RpnData::token(Add, -1);
	bool NegativeSign = false;
	int UnclosedLeftBracketCount = 0;
public:
	ReversePolishNotation();
	void inputNumber(CompType, int);
	void inputToken(TokenType, int);

	void endInput();
	ComputeResult compute();
	static int getTokenPriority(TokenType);
};

