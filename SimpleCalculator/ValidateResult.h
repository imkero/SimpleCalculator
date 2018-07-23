#pragma once
#include "Enums.h"
struct ValidateResult
{
	ValidateErrorType Type;
	int Pos;
	ValidateResult()
	{
		Type = Success;
		Pos = 0;
	}
	ValidateResult(ValidateErrorType error, int pos)
	{
		Type = error;
		Pos = pos;
	}
};

