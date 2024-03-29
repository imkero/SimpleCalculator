#pragma once
#include "HorizontalExpression.h"
#include <vector>

struct ComputeHistoryItem
{
	HorizontalExpression *Expr;
	ComputeResult Result;
	ComputeHistoryItem(HorizontalExpression *expr, ComputeResult result)
	{
		Expr = expr;
		Result = result;
	}
};

class HistoryMgr
{
protected:
	std::vector<ComputeHistoryItem> HistoryItem;
	int ItemStackMaxLength = 10;

public:
	HistoryMgr();
	void append(HorizontalExpression *, ComputeResult);
	int getIndex(HorizontalExpression *) const;
	bool contains(HorizontalExpression *) const;
	int getLength() const;
	const ComputeHistoryItem &get(int index) const;
	~HistoryMgr();
};

