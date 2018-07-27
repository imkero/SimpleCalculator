#pragma once
#include "Enums.h"
class EnumConvert
{
public:
	static TokenType char2token(char);
	static char token2char(TokenType);
};