#include "VariableMgr.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <QRegExp>
#include <QRegExpValidator>
#pragma execution_character_set("utf-8")


bool VariableMgr::hasKey(std::map<std::string, CompType> &map, const std::string &key)
{
	auto found = map.find(key);
	return found != map.end();
}

VariableMgr::VariableMgr()
{
	Constant["¦Ð"] = M_PI;
	Constant["e"] = M_E;
}

bool VariableMgr::modifiable(const std::string &key)
{
	return hasKey(Variable, key);
}

bool VariableMgr::has(const std::string &key)
{
	return hasKey(Variable, key) || hasKey(Constant, key);
}

void VariableMgr::set(const std::string &key, CompType value)
{
	Variable[key] = value;
}

CompType VariableMgr::get(const std::string &key)
{
	auto found = Variable.find(key);
	if (found != Variable.end())
	{
		return (*found).second;
	}
	found = Constant.find(key);
	if (found != Constant.end())
	{
		return (*found).second;
	}
	return 0.0;
}

void VariableMgr::del(const std::string &key)
{
	auto found = Variable.find(key);
	if (found != Variable.end())
	{
		Variable.erase(found);
	}
}

void VariableMgr::clearAll()
{
	for (auto iter = Variable.begin(); iter != Variable.end(); ++iter)
	{
		(*iter).second = 0;
	}
}

void VariableMgr::setAns(CompType value)
{
	Variable["Ans"] = value;
}

bool VariableMgr::saveToFile(const std::wstring &fileName)
{
	std::ofstream fileStream;
	fileStream.open(fileName, std::ios::binary);
	if (!fileStream.is_open()) return false;
	// Magic Number
	fileStream.write(reinterpret_cast<const char *>(&FileMagicNumber), sizeof(FileMagicNumber));

	int length = Variable.size();
	fileStream.write(reinterpret_cast<const char *>(&length), sizeof(length));

	for (auto iter = Variable.cbegin(); iter != Variable.cend(); ++iter)
	{
		int strLength = (*iter).first.length();
		fileStream.write(reinterpret_cast<const char *>(&strLength), sizeof(strLength));
		fileStream.write(reinterpret_cast<const char *>((*iter).first.c_str()), strLength);
		fileStream.write(reinterpret_cast<const char *>((&(*iter).second)), sizeof((*iter).second));
	}
	fileStream.close();
	return true;
}

bool VariableMgr::loadFromFile(const std::wstring &fileName)
{
	std::ifstream fileStream;
	fileStream.open(fileName, std::ios::binary);
	if (!fileStream.is_open()) return false;

	// Magic Number
	int magic = 0;
	fileStream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
	if (magic != FileMagicNumber)
		return false;

	int length = 0;
	fileStream.read(reinterpret_cast<char *>(&length), sizeof(length));

	for (int i = 0; i < length; i++)
	{
		int strLength = 0;
		fileStream.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));

		char *varName = new char[strLength + 1];
		fileStream.read(reinterpret_cast<char *>(varName), strLength);
		varName[strLength] = '\0';

		CompType value = 0;
		fileStream.read(reinterpret_cast<char *>(&value), sizeof(value));

		Variable[std::string(varName)] = value;
		
		delete[] varName;
	}
	fileStream.close();
	return true;
}

bool VariableMgr::variableNameAvailable(const QString &input)
{
	QRegExp regex("^[0-9.()£¨£©]*$");
	QRegExpValidator validator(regex, 0);
	int pos = 0;
	QString s(input);
	QValidator::State result = validator.validate(s, pos);
	if (result == QValidator::State::Acceptable)
	{
		return false;
	}
	else
	{
		regex.setPattern("[\\+\\-*/£«¡Á¡Â=]+");
		return !s.contains(regex);
	}
}


VariableMgr::~VariableMgr()
{
}
