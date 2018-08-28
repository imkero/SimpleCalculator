#pragma once
#include <unordered_map>
class ProgramSettings
{
protected:
	const static char* FileName;
	const static char* MagicNumber;

	static void readInt(int &, std::unordered_map<std::string, std::string> &, const char *);
	static void readBool(bool &, std::unordered_map<std::string, std::string> &, const char *);
public:
	// Config
	bool AutoCompute = true;
	bool RememberWindowSize = false;
	bool WindowMaximized = false;
	int WindowWidth = -1;
	int WindowHeight = -1;
	bool ThousandComma = false;

	ProgramSettings();
	~ProgramSettings();

	void readFromFile();
	void saveToFile();
};

