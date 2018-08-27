#pragma once
#include <QTranslator>
class DefaultTranslator : public QTranslator
{
public:
	DefaultTranslator();
	QString translate(const char *context, const char *sourceText, const char *disambiguation = nullptr, int n = -1) const;
	~DefaultTranslator();
};

