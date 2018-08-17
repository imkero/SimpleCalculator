#include "ExpressionPaintUtil.h"
#include "GlobalMgr.h"

int ExpressionPaintUtil::computeBracketWidth(int height, bool isSub)
{
	return 6 + (isSub ? g_Data->Visual.PanelSubTokenWidth[RightBracket] : g_Data->Visual.PanelTokenWidth[RightBracket])
		* sqrt(static_cast<double>(height) / (isSub ? g_Data->Visual.PanelSubExprHeight.total() : g_Data->Visual.PanelExprHeight.total()));
}

void ExpressionPaintUtil::drawLeftBracket(QPainter *painter, QPoint anchorPoint, const ExpressionElement *element)
{
	QPainterPath path;

	QPoint start(anchorPoint);
	QPoint control(anchorPoint);
	QPoint end(anchorPoint);

	start.rx() += element->RealWidth - 3;
	end.rx() += element->RealWidth - 3;
	//control.rx() -= element->RealWidth / 4;

	start.ry() -= element->RealHeight.Ascent - 2;
	end.ry() += element->RealHeight.Descent - 2;
	control.ry() += (-element->RealHeight.Ascent + element->RealHeight.Descent) / 2;

	path.moveTo(start);
	path.quadTo(control, end);

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	pen.setColor(g_Data->Visual.PanelSubColor);
	pen.setWidth(2);
	painter->setPen(pen);

	painter->drawPath(path);
	painter->restore();
}

void ExpressionPaintUtil::drawRightBracket(QPainter *painter, QPoint anchorPoint, const ExpressionElement *element)
{
	QPainterPath path;

	QPoint start(anchorPoint);
	QPoint control(anchorPoint);
	QPoint end(anchorPoint);

	control.rx() += element->RealWidth;
	start.rx() += 3;
	end.rx() += 3;
	start.ry() -= element->RealHeight.Ascent - 2;
	end.ry() += element->RealHeight.Descent - 2;
	control.ry() += (-element->RealHeight.Ascent + element->RealHeight.Descent) / 2;

	path.moveTo(start);
	path.quadTo(control, end);

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	pen.setColor(g_Data->Visual.PanelSubColor);
	pen.setWidth(2);
	painter->setPen(pen);

	painter->drawPath(path);
	painter->restore();
}

QPoint ExpressionPaintUtil::calcDrawTextPrefix(QPoint point, bool isSub)
{
	return point + QPoint(0, isSub ? g_Data->Visual.SubBasicCharHeightDelta : g_Data->Visual.BasicCharHeightDelta);
}
