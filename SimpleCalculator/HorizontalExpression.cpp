#include "HorizontalExpression.h"

HorizontalExpression::HorizontalExpression() : ExpressionBase(ExpressionType::Horizontal)
{
}

void HorizontalExpression::RearrangeBracket()
{
	if (Parent == nullptr || Parent->ExprType != ExpressionType::Horizontal)
	{
		// join all children horizontal expr and rearrange
		// leave ")" at the outermost horizontal expr

	}
	else
	{
		static_cast<HorizontalExpression *>(Parent)->RearrangeBracket();
	}
}

HorizontalExpression::~HorizontalExpression()
{
}

double HorizontalExpression::calcValue()
{
	if (validate())
	{
		// consider "++---", first "+" is op, 
		// and the following "+---", ignore every "+", just count "-" is odd or not

	}
	else
	{
		// throw exception
	}
	return 0.0;
}

void HorizontalExpression::calcRect()
{
}

bool HorizontalExpression::validate()
{
	// contains ")" means bad format expression
	// no any expr after operation is also bad format expression 
	// two expr without op between them is not good as well
	return true;
}
