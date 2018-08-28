#include "Util.h"
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>
#include <string>
#include <sstream>
#include "windows.h"
#include "resource.h"

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

double nthRoot(double x, double n)
{
	return pow(x, 1.0 / n);
}

void addThousandComma(char *destText, const char *sourceText)
{
	std::string s(sourceText);
	std::size_t pointPos = s.rfind('.');
	if (pointPos == std::string::npos)
	{
		pointPos = s.size();
	}
	while (pointPos > 3)
	{
		s.insert(s.begin() + (pointPos - 3), ',');
		pointPos -= 3;
	}
	strcpy(destText, s.c_str());
}

void setQtWindowIcon(WId wid)
{
	SendMessage(reinterpret_cast<HWND>(wid), WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
}

void playWarnSound()
{
	PlaySound(TEXT("Windows Background.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
