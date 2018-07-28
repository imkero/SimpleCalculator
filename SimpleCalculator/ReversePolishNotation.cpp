#include "ReversePolishNotation.h"
#include "EnumConvert.h"
#include <iostream>
ReversePolishNotation::ReversePolishNotation()
{
}

void ReversePolishNotation::inputNumber(double num)
{
	RpnData input;
	input.Data.Number = NegativeSign ? -num : num;
	input.IsNumber = true;

	NegativeSign = false;

	if (LastInput.IsNumber)
	{
		inputToken(Mul);
	}
	Elements.push_back(input);
	LastInput = input;
}

void ReversePolishNotation::inputToken(TokenType token)
{
	if (!LastInput.IsNumber && token == Sub)
	{
		switch (LastInput.Data.Token)
		{
		case Add:
		case Sub:
		case Mul:
		case Div:
		case Mod:
		case LeftBracket:
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
			inputToken(Mul);
		}
		UnclosedLeftBracketCount++;
		break;
	case RightBracket:
		UnclosedLeftBracketCount--;
		break;
	}
	if (Stack.empty())
	{
		Stack.push(token);
	}
	else
	{
		if (token == LeftBracket)
		{
			Stack.push(LeftBracket);
		}
		else if (token == RightBracket)
		{
			while (!Stack.empty() && Stack.top() != LeftBracket)
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
			while (!Stack.empty() && getTokenPriority(Stack.top()) >= priority)
			{
				data.Data.Token = Stack.top();
				Elements.push_back(data);
				Stack.pop();
			}
			Stack.push(token);
		}
			
	}
	LastInput = input;
	
}

void ReversePolishNotation::endInput()
{
	for (int i = UnclosedLeftBracketCount; i > 0; i--)
	{
		inputToken(RightBracket);
	}
	while (!Stack.empty())
	{
		Elements.push_back(RpnData::token(Stack.top()));
		Stack.pop();
	}
}

double ReversePolishNotation::compute()
{
	std::stack<double> stack;
	int count = Elements.size();
	for (int i = 0; i < count; i++)
	{
		if (Elements[i].IsNumber)
		{
			stack.push(Elements[i].Data.Number);
		}
		else
		{
			double right = stack.top();
			stack.pop();
			double left = stack.top();
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
				stack.push(left / right);
				break;
			case Pow:
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
		std::cout << "RPN internal error, stack size != 1" << std::endl;
	}
	return stack.top();
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
