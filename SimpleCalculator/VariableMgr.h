#pragma once
#include <map>
#include <string>
#include <QString>

class VariableMgr
{
protected:
	static bool hasKey(std::map<std::string, double> &, const std::string &);
	const static int FileMagicNumber = 0x52415653;

public:
	std::map<std::string, double> Constant;
	std::map<std::string, double> Variable;
	
	VariableMgr();
	bool modifiable(const std::string &);
	bool has(const std::string &);
	void set(const std::string &, double);
	double get(const std::string &);
	void del(const std::string &);
	void clearAll();

	bool saveToFile(const std::wstring &);
	bool loadFromFile(const std::wstring &);

	static bool variableNameAvailable(const QString &);

	~VariableMgr();
};

