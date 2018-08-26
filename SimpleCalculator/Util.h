#pragma once
extern int clamp(int value, int min, int max);
extern void playWarnSound();
extern bool isNaN(double);
extern double radToDeg(double);
extern double degToRad(double);
extern int stringToInt(const char *, bool * = nullptr);