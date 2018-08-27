#include "DefaultTranslator.h"
#include <cstring>

#pragma execution_character_set("utf-8")

DefaultTranslator::DefaultTranslator() : QTranslator(nullptr)
{

}

QString DefaultTranslator::translate(const char * context, const char * sourceText, const char * disambiguation, int n) const
{
	if (strcmp(context, "QPlatformTheme") == 0)
	{
		if (strcmp(sourceText, "OK") == 0)
		{
			return QString("确定");
		}
		else if (strcmp(sourceText, "Cancel") == 0)
		{
			return QString("取消");
		}
	}
	return QString();
}

DefaultTranslator::~DefaultTranslator()
{
}
