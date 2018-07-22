#pragma once
#include "ExpressionBase.h"
#include "Enums.h"
class ExpressionSymbol : public ExpressionBase
{
protected:
	SymbolType Symbol;
public:
	ExpressionSymbol(SymbolType);

	bool isOperator();
	SymbolType getSymbol();
	
	virtual void computeRect();
	virtual ExpressionBase *findSlibing(ExpressionBase *self, Direction dir);
	virtual int getLength();
	virtual bool insertAt(KbButtonName, int);
};

