#include "Util.h"
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>
#include <sstream>
#pragma comment(lib, "winmm.lib")

inline int clamp(int value, int min, int max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

bool isNaN(double dat)
{
	__int64 & ref = reinterpret_cast<__int64 &>(dat);
	return (ref & 0x7FF0000000000000) == 0x7FF0000000000000 && (ref & 0xfffffffffffff) != 0;
}

double radToDeg(double rad)
{
	return rad * (180 / M_PI);
}

double degToRad(double deg)
{
	return deg * (M_PI / 180);
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
