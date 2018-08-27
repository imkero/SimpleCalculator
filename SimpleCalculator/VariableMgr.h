#pragma once
#include <unordered_map>
#include <string>
#include <QString>

class VariableMgr
{
protected:
	static bool hasKey(std::unordered_map<std::string, double> &, const std::string &);
public:
	std::unordered_map<std::string, double> Constant;
	std::unordered_map<std::string, double> Variable;
	
	VariableMgr();
	bool modifiable(const std::string &);
	bool has(const std::string &);
	void set(const std::string &, double);
	double get(const std::string &);
	void del(const std::string &);
	void clearAll();

	static bool variableNameAvailable(const QString &);

	~VariableMgr();
};

