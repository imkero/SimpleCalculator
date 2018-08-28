#pragma once
#include <qwindowdefs.h>

extern int clamp(int value, int min, int max);
extern void playWarnSound();
extern bool isNaN(double);
extern double radToDeg(double);
extern double degToRad(double);
extern int stringToInt(const char *, bool * = nullptr);
extern double nthRoot(double x, double n);
extern void addThousandComma(char *destText, const char *sourceText);
extern void setQtWindowIcon(WId wid);