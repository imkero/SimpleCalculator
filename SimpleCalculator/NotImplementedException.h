#pragma once
#include <exception>
class NotImplementedException : public std::exception
{
public:
	NotImplementedException(const char *_Data) : exception(_Data) { }
};

