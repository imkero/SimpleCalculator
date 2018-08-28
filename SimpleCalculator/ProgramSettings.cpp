#include "ProgramSettings.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <Util.h>

const char *ProgramSettings::FileName = "config.dat";
const char *ProgramSettings::MagicNumber = "SCAL";

void ProgramSettings::readInt(int &out, std::unordered_map<std::string, std::string> &map, const char *name)
{
	auto found = map.find(name);
	if (found == map.end()) return;
	bool convertSuccess;
	int data = stringToInt((*found).second.c_str(), &convertSuccess);
	if (convertSuccess)
		out = data;
}

void ProgramSettings::readBool(bool &out, std::unordered_map<std::string, std::string> &map, const char *name)
{
	auto found = map.find(name);
	if (found == map.end()) return;
	bool convertSuccess;
	int data = stringToInt((*found).second.c_str(), &convertSuccess);
	if (convertSuccess)
		out = data != 0;
}

ProgramSettings::ProgramSettings()
{
}

void ProgramSettings::readFromFile()
{
	std::ifstream fileStream;
	fileStream.open(FileName);
	
	if (!fileStream.is_open()) return;

	// Check Magic Number
	std::string magicNumber;
	if (getline(fileStream, magicNumber))
	{
		if (magicNumber != MagicNumber)
			return;
	}
	else
	{
		return;
	}

	std::string name;
	std::string value;
	std::unordered_map<std::string, std::string> configInFile;
	while (getline(fileStream, name))
	{
		if (getline(fileStream, value))
		{
			configInFile[name] = value;
		}
	}
	fileStream.close();

	readBool(AutoCompute, configInFile, "AutoCompute");
	readBool(RememberWindowSize, configInFile, "RememberWindowSize");
	readInt(WindowWidth, configInFile, "WindowWidth");
	readInt(WindowHeight, configInFile, "WindowHeight");
	readBool(WindowMaximized, configInFile, "WindowMaximized");
	readBool(ThousandComma, configInFile, "ThousandComma");
}

void ProgramSettings::saveToFile()
{
	std::ofstream fileStream;
	fileStream.open(FileName);
	if (!fileStream.is_open()) return;

	fileStream << MagicNumber << std::endl;

	fileStream << "AutoCompute" << std::endl << AutoCompute << std::endl;
	fileStream << "RememberWindowSize" << std::endl << RememberWindowSize << std::endl;
	fileStream << "WindowWidth" << std::endl << WindowWidth << std::endl;
	fileStream << "WindowHeight" << std::endl << WindowHeight << std::endl;
	fileStream << "WindowMaximized" << std::endl << WindowMaximized << std::endl;
	fileStream << "ThousandComma" << std::endl << ThousandComma << std::endl;

	fileStream.close();
}

ProgramSettings::~ProgramSettings()
{
}
