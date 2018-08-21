#include "Util.h"
#include <windows.h>
#include <cstring>
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

int stringToInt(const char *str, bool *ok)
{
	std::stringstream stream(str);
	int int_temp;
	stream >> int_temp;
	if (ok != nullptr)
		*ok = !stream.fail();
	return int_temp;
}

void eatExtraZero(char *s)
{
	char *point = strchr(s, '.');
	if (point == nullptr) return;
	int length = strlen(s);
	char *p = s + length;
	while (*(p - 1) == '0' && p - 1 > point)
	{
		p--; // eat '0'
	}
	if (*(p - 1) == '.')
		p--; // eat '.' before '0'
	*p = '\0';
}

void playWarnSound()
{
	PlaySound(TEXT("Windows Background.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
