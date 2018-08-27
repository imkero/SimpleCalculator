#include "HistoryMgr.h"


HistoryMgr::HistoryMgr()
{
}

void HistoryMgr::append(HorizontalExpression *expr, ComputeResult result)
{
	if (HistoryItem.size() >= ItemStackMaxLength)
	{
		delete HistoryItem[0].Expr;
		HistoryItem.erase(HistoryItem.begin());
	}
	HistoryItem.push_back(ComputeHistoryItem(expr, result));
}

int HistoryMgr::getIndex(HorizontalExpression *expr) const
{
	int index = 0;
	for (auto iter = HistoryItem.begin(); iter != HistoryItem.end(); ++iter, ++index)
	{
		if ((*iter).Expr == expr)
		{
			return index;
		}
	}
	return -1;
}

bool HistoryMgr::contains(HorizontalExpression *expr) const
{
	for (auto iter = HistoryItem.begin(); iter != HistoryItem.end(); ++iter)
	{
		if ((*iter).Expr == expr)
		{
			return true;
		}
	}
	return false;
}

int HistoryMgr::getLength() const
{
	return HistoryItem.size();
}

const ComputeHistoryItem & HistoryMgr::get(int index) const
{
	return HistoryItem[index];
}

HistoryMgr::~HistoryMgr()
{
	for (auto iter = HistoryItem.begin(); iter != HistoryItem.end(); ++iter)
	{
		delete (*iter).Expr;
	}
}
