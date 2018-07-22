#include "ReversePolishNotation.h"

void ReversePolishNotation::input(ExpressionElement element)
{
	if (element.isSymbol)
	{
		if (Stack.empty())
		{
			Stack.push(element.data.symbol);
			return;
		}
		switch (element.data.symbol) 
		{
		case Add:
		case Sub:
			while (!Stack.empty() && Stack.top() != LeftBracket)
			{
				Elements.push_back(ExpressionElement(Stack.top()));
				Stack.pop();
			}
			Stack.push(element.data.symbol);
			break;
		case Mul:
		case Div:
			while (!Stack.empty() && (Stack.top() == Mul || Stack.top() == Div))
			{
				Elements.push_back(ExpressionElement(Stack.top()));
				Stack.pop();
			}
			Stack.push(element.data.symbol);
			break;
		case RightBracket:
			while (!Stack.empty() && Stack.top() != LeftBracket)
			{
				Elements.push_back(ExpressionElement(Stack.top()));
				Stack.pop();
			}
			Stack.pop();
			break;
		case LeftBracket:
			Stack.push(element.data.symbol);
			break;
		}
	}
	else
	{
		Elements.push_back(element);
	}
}

void ReversePolishNotation::endInput()
{
	while (!Stack.empty())
	{
		Elements.push_back(ExpressionElement(Stack.top()));
		Stack.pop();
	}
}

double ReversePolishNotation::compute()
{
	std::stack<double> stack;
	int count = Elements.size();
	for (int i = 0; i < count; i++)
	{
		if (Elements[i].isSymbol)
		{
			double right = stack.top();
			stack.pop();
			double left = stack.top();
			stack.pop();

			switch (Elements[i].data.symbol)
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
			}
		}
		else
		{
			stack.push(Elements[i].data.value);
		}
	}
	return stack.top();
}
