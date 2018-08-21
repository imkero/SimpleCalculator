#include "Util.h"
#include <windows.h>
#include <sstream>
#pragma comment(lib, "winmm.lib")

inline int clamp(int value, int min, int max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

inline int maxInt(int a, int b)
{
	return a > b ? a : b;
}

bool isNaN(double dat)
{
	__int64 & ref = reinterpret_cast<__int64 &>(dat);
	return (ref & 0x7FF0000000000000) == 0x7FF0000000000000 && (ref & 0xfffffffffffff) != 0;
}

int stringToInt(const char *str, bool *ok)
{
	std::stringstream stream(str);
	int int_temp;
	stream >> int_temp;
	if (ok != nullptr)
		*ok = !stream.fail();
	return int_temp;
}

void playWarnSound()
{
	PlaySound(TEXT("Windows Background.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
