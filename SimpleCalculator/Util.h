#pragma once
extern int clamp(int value, int min, int max);
extern void playWarnSound();
extern int maxInt(int a, int b);
extern int stringToInt(const char *, bool * = nullptr);
extern void eatExtraZero(char *);