#include "Const.h"
#include "ArithmeticPanel.h"
#include <QtWidgets/QFrame>
#include <QPainter>


ArithmeticPanel::ArithmeticPanel(QWidget *parent) : QFrame(parent)
{

}

void ArithmeticPanel::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QFont font(Const::FONT_ALPHA, 20);
	QRectF rect(0, 0, this->rect().width() - 1, this->rect().height() - 1);
	painter.setPen(QColor(Qt::black));
	painter.setFont(font);
	painter.drawText(rect, Qt::AlignBottom | Qt::AlignRight, "123456");
}


ArithmeticPanel::~ArithmeticPanel()
{
}
