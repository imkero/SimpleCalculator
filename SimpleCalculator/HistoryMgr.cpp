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


HistoryMgr::~HistoryMgr()
{
	for (auto iter = HistoryItem.begin(); iter != HistoryItem.end(); ++iter)
	{
		delete (*iter).Expr;
	}
}
