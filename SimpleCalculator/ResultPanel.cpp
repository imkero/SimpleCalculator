#include "ResultPanel.h"
#include <QPainter>
#include <QDebug>
#include "GlobalMgr.h"
#include <QPropertyAnimation>

QFont ResultPanel::Font("Microsoft YaHei UI", 16);
QColor ResultPanel::BgColor(207, 207, 207);
QColor ResultPanel::FontColor(0, 0, 0);

int ResultPanel::getShowProgress()
{
	return ShowProgress;
}

void ResultPanel::setShowProgress(int value)
{
	ShowProgress = value;
	emit signalShowProgressUpdate();
}

int ResultPanel::getExchangeProgress()
{
	return ExchangeProgress;
}

void ResultPanel::setExchangeProgress(int value)
{
	ExchangeProgress = value;
	emit signalExchangeProgressUpdate();
}

void ResultPanel::resultExchange(double value, bool withAnim)
{
	char *arr = ExchangeProgress > 255 ? ResultA : ResultB;
	if (!withAnim)
	{
		ExchangeProgress = 0;
		arr = ResultA;
	}
	sprintf(arr, "= %f", value);
	if (withAnim)
	{
		if (ExchangeAnim->state() != QAbstractAnimation::Running)
		{
			if (ExchangeProgress > 255)
			{
				char *temp = ResultA;
				ResultA = ResultB;
				ResultB = temp;
			}
			ExchangeAnim->start();
		}
		else
		{
			if (ExchangeProgress > 255)
			{
				ExchangeAnim->pause();
				ExchangeProgress = 511 - ExchangeProgress;
				ExchangeAnim->setCurrentTime(ExchangeAnim->duration() - ExchangeAnim->currentTime());
				
				char *temp = ResultA;
				ResultA = ResultB;
				ResultB = temp;

				ExchangeAnim->resume();
			}
		}
	}
}


ResultPanel::ResultPanel(QWidget * parent) : QFrame(parent), Singleton<ResultPanel>()
{
	ResultA = new char[64];
	ResultB = new char[64];

	connect(this, SIGNAL(signalShowProgressUpdate()), this, SLOT(update()));
	connect(this, SIGNAL(signalExchangeProgressUpdate()), this, SLOT(update()));

	setFixedHeight(55);

	ShowAnim = new QPropertyAnimation(this, "ShowProgress", this);
	ShowAnim->setDuration(150);
	ShowAnim->setStartValue(0);
	ShowAnim->setEndValue(255);
	ShowAnim->setEasingCurve(QEasingCurve::OutQuad);

	ExchangeAnim = new QPropertyAnimation(this, "ExchangeProgress", this);
	ExchangeAnim->setDuration(150);
	ExchangeAnim->setStartValue(0);
	ExchangeAnim->setEndValue(511);
}

void ResultPanel::paintEvent(QPaintEvent *)
{
	if (ShowProgress > 0)
	{
		QPainter painter(this);
		QRect r = rect();
		painter.fillRect(QRect(15, 0, r.width() - 31, r.height() - 1), QColor(BgColor.red(), BgColor.green(), BgColor.blue(), ShowProgress));
		painter.setFont(Font);
		int alpha = ShowProgress;
		alpha *= ExchangeProgress > 255 ? ExchangeProgress - 256 : 255 - ExchangeProgress;
		if (alpha > 0)
			alpha = sqrt(alpha);
		painter.setPen(QColor(FontColor.red(), FontColor.green(), FontColor.blue(), alpha));
		painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, ExchangeProgress > 255 ? ResultB : ResultA);
	}
}

void ResultPanel::hide()
{
	if (ShowAnim->state() != QAbstractAnimation::Running)
	{
		if (ShowAnim->currentValue() != ShowAnim->startValue())
		{
			ShowAnim->setDirection(QAbstractAnimation::Backward);
			ShowAnim->start();
		}
	}
	else if (ShowAnim->direction() == QAbstractAnimation::Forward)
	{
		ShowAnim->pause();
		ShowAnim->setDirection(QAbstractAnimation::Backward);
		ShowAnim->resume();
	}
}

void ResultPanel::showResult(double value)
{
	if (qIsNaN(value))
	{
		hide();
		return;
	}
	if (ShowAnim->state() != QAbstractAnimation::Running)
	{
		if (ShowAnim->currentTime() != ShowAnim->duration())
		{
			if (ShowAnim->currentTime() == 0)
			{
				resultExchange(value, false);
			}
			else
			{
				resultExchange(value, true);
			}
			ShowAnim->setDirection(QAbstractAnimation::Forward);
			ShowAnim->start();
		}
		else
		{
			resultExchange(value, true);
		}
	}
	else if (ShowAnim->direction() == QAbstractAnimation::Backward)
	{
		ShowAnim->pause();
		ShowAnim->setDirection(QAbstractAnimation::Forward);
		ShowAnim->resume();
	}
}

ResultPanel::~ResultPanel()
{
	if (ShowAnim != nullptr)
	{
		delete ShowAnim;
		ShowAnim = nullptr;
	}
	if (ResultA != nullptr)
	{
		delete[] ResultA;
		ResultA = nullptr;
	}
	if (ResultB != nullptr)
	{
		delete[] ResultB;
		ResultB = nullptr;
	}
}
