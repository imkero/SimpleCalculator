#include "VariableExpression.h"
#include "ExpressionPaintUtil.h"
#include "GlobalMgr.h"

VariableExpression::VariableExpression(ExpressionBase * parent, const std::string &varName)
	: ExpressionBase(Variable, parent), VarName(varName)
{

}

ComputeResult VariableExpression::computeValue()
{
	if (g_Data->Variable.has(VarName))
	{
		return ComputeResult(g_Data->Variable.get(VarName));
	}
	else
	{
		return ComputeResult(VariableNotExist, Parent->as<HorizontalExpression>(), Parent->findChildPosition(this));
	}
}

void VariableExpression::computeSize()
{
	HorizontalExpression *parent = Parent->as<HorizontalExpression>();
	auto found = WidthCache.find(VarName);
	std::pair<int, int> widthData;
	if (found == WidthCache.end())
	{
		 WidthCache[VarName] = widthData = g_Data->Visual.getWidth(VarName.c_str());
	}
	else
	{
		widthData = (*found).second;
	}

	Rect.Width = parent->getIsSubExpr() ? widthData.second : widthData.first;
	Rect.Height = parent->getBasicHeight();
}

void VariableExpression::computePosition(AnchoredPoint anchoredPos)
{
	Rect.setPosWithAnchor(anchoredPos);
}

void VariableExpression::draw(QPainter *painter)
{
	HorizontalExpression *parent = Parent->as<HorizontalExpression>();
	painter->save();
	painter->setPen(g_Data->Visual.PanelMainColor);
	painter->setFont(parent->getIsSubExpr() ? g_Data->Visual.PanelSubExprFont : g_Data->Visual.PanelExprFont);
	painter->drawText(ExpressionPaintUtil::calcDrawTextPrefix(Rect.Pos, parent->getIsSubExpr()), VarName.c_str());
	painter->restore();
}

void VariableExpression::mouseClick(const QPoint &mousePoint)
{
}

int VariableExpression::getLength()
{
	return 0;
}

void VariableExpression::remove(ExpressionBase *, bool moveCursor)
{
}

ValidateResult VariableExpression::validate()
{
	if (!g_Data->Variable.has(VarName))
		return ValidateResult(VariableNotExist, Parent->as<HorizontalExpression>(), Parent->findChildPosition(this));
	return ValidateResult(nullptr);
}

int VariableExpression::findChildPosition(ExpressionBase *)
{
	return -1;
}

VariableExpression::~VariableExpression()
{
}

ExpressionBase * VariableExpression::clone() const
{
	return new VariableExpression(*this);
}
