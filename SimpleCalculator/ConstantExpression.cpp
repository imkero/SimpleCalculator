#include "ConstantExpression.h"
#include "NotImplementedException.h"

ConstantExpression::ConstantExpression(char digit) : ComputableExpression(Constant)
{
	Digits.push_back(digit);
}

ConstantExpression::~ConstantExpression()
{
}

double ConstantExpression::computeValue()
{
	double value;
	sscanf_s(Digits.c_str(), "%lf", &value);
	return value;
}

ExpressionBase * ConstantExpression::findSlibing(ExpressionBase * self, Direction dir)
{
	throw new NotImplementedException("ConstantExpression::findSlibing");
}

int ConstantExpression::getLength()
{
	return Digits.length();
}

bool ConstantExpression::insertAt(KbButtonName btnName, int pos)
{
	char c;
	switch (btnName)
	{
	default:
		return false;
	case Button0: c = '0'; break;
	case Button1: c = '1'; break;
	case Button2: c = '2'; break;
	case Button3: c = '3'; break;
	case Button4: c = '4'; break;
	case Button5: c = '5'; break;
	case Button6: c = '6'; break;
	case Button7: c = '7'; break;
	case Button8: c = '8'; break;
	case Button9: c = '9'; break;
	case ButtonDot: c = '.'; break;
	}
	Digits.insert(static_cast<size_t>(pos), 1, 'c');
	return true;
}

ConstantExpression * ConstantExpression::fromButtonName(KbButtonName btnName)
{
	char c;
	switch (btnName)
	{
	default:
		return nullptr;
	case Button0: c = '0'; break;
	case Button1: c = '1'; break;
	case Button2: c = '2'; break;
	case Button3: c = '3'; break;
	case Button4: c = '4'; break;
	case Button5: c = '5'; break;
	case Button6: c = '6'; break;
	case Button7: c = '7'; break;
	case Button8: c = '8'; break;
	case Button9: c = '9'; break;
	case ButtonDot: c = '.'; break;
	}
	return new ConstantExpression(c);
}

void ConstantExpression::computeRect()
{
}
