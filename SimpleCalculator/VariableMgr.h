#pragma once
#include <map>
#include <string>
#include "CalcTypes.h"
#include <QString>

class VariableMgr
{
protected:
	static bool hasKey(std::map<std::string, CompType> &, const std::string &);
	const static int FileMagicNumber = 0x52415653;

public:
	std::map<std::string, CompType> Constant;
	std::map<std::string, CompType> Variable;
	
	VariableMgr();
	bool modifiable(const std::string &);
	bool has(const std::string &);
	void set(const std::string &, CompType);
	CompType get(const std::string &);
	void del(const std::string &);
	void clearAll();
	void setAns(CompType);

	bool saveToFile(const std::wstring &);
	bool loadFromFile(const std::wstring &);

	static bool variableNameAvailable(const QString &);

	~VariableMgr();
};

