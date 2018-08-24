#include "ReversePolishNotation.h"
#include "EnumConvert.h"
#include <iostream>

ReversePolishNotation::ReversePolishNotation()
{
}

void ReversePolishNotation::inputNumber(CompType num, int index)
{
	RpnData input;
	input.Data.Number = NegativeSign ? -num : num;
	input.IsNumber = true;
	input.Index = index;

	NegativeSign = false;

	if (LastInput.IsNumber)
	{
		inputToken(Mul, -1);
	}
	Elements.push_back(input);
	LastInput = input;
}

void ReversePolishNotation::inputToken(TokenType token, int index)
{
	if (!LastInput.IsNumber && (token == Sub || token == Add))
	{
		switch (LastInput.Data.Token)
		{
		case Add:
		case Sub:
		case Mul:
		case Div:
		case Mod:
		case LeftBracket:
			if (token == Sub)
				NegativeSign = !NegativeSign;
			return;
		}
	}
	
	RpnData input;
	input.Data.Token = token;
	input.IsNumber = false;
	int priority = getTokenPriority(token);
	switch (token)
	{
	case LeftBracket: 
		if (LastInput.IsNumber || (!LastInput.IsNumber && LastInput.Data.Token == RightBracket))
		{
			inputToken(Mul, index);
		}
		if (!LastInput.IsNumber && NegativeSign)
		{
			inputNumber(1, -1);
			inputToken(Mul, -1);
		}
		UnclosedLeftBracketCount++;
		break;
	case RightBracket:
		UnclosedLeftBracketCount--;
		break;
	}
	if (Stack.empty())
	{
		Stack.push(std::make_pair(token, index));
	}
	else
	{
		if (token == LeftBracket)
		{
			Stack.push(std::make_pair(LeftBracket, index));
		}
		else if (token == RightBracket)
		{
			while (!Stack.empty() && Stack.top().first != LeftBracket)
			{
				Elements.push_back(RpnData::token(Stack.top()));
				Stack.pop();
			}
			Stack.pop();
		}
		else
		{
			RpnData data;
			data.IsNumber = false;
			while (!Stack.empty() && getTokenPriority(Stack.top().first) >= priority)
			{
				data.Data.Token = Stack.top().first;
				data.Index = Stack.top().second;
				Elements.push_back(data);
				Stack.pop();
			}
			Stack.push(std::make_pair(token, index));
		}
			
	}
	LastInput = input;
	
}

void ReversePolishNotation::endInput()
{
	for (int i = UnclosedLeftBracketCount; i > 0; i--)
	{
		inputToken(RightBracket, -1);
	}
	while (!Stack.empty())
	{
		Elements.push_back(RpnData::token(Stack.top()));
		Stack.pop();
	}
}

ComputeResult ReversePolishNotation::compute()
{
	std::stack<CompType> stack;
	int count = Elements.size();
	for (int i = 0; i < count; i++)
	{
		if (Elements[i].IsNumber)
		{
			stack.push(Elements[i].Data.Number);
		}
		else
		{
			CompType right = stack.top();
			stack.pop();
			CompType left = stack.top();
			stack.pop();

			switch (Elements[i].Data.Token)
			{
			case Add:
				stack.push(left + right);
				break;
			case Sub:
				stack.push(left - right);
				break;
			case Mul:
				stack.push(left * right);
				break;
			case Div:
				if (right == 0)
				{
					return ComputeResult(ValidateErrorType::DivideByZero, Elements[i].Index);
				}
				stack.push(left / right);
				break;
			case Pow:
				if (left == 0 && right == 0)
				{
					return ComputeResult(ValidateErrorType::ZeroPowZero, Elements[i].Index);
				}
				stack.push(pow(left, right));
				break;
			case Mod:
				stack.push(fmod(left, right));
				break;
			}
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "RPN internal error, stack size != 1" << std::endl;
	}
	return ComputeResult(stack.top());
}

int ReversePolishNotation::getTokenPriority(TokenType token)
{
	switch (token)
	{
	case Pow:
		return 3;
	case Mul:
	case Div:
	case Mod:
		return 2;
	case Add:
	case Sub:
		return 1;
	default:
		return 0;
	}
}
