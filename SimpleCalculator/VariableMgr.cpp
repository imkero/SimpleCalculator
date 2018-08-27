#include "VariableMgr.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QRegExp>
#include <QRegExpValidator>
#pragma execution_character_set("utf-8")


bool VariableMgr::hasKey(std::unordered_map<std::string, double> &map, const std::string &key)
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

void VariableMgr::set(const std::string &key, double value)
{
	Variable[key] = value;
}

double VariableMgr::get(const std::string &key)
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
