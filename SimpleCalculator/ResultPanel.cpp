#include "ResultPanel.h"
#include <QPainter>
#include <QDebug>
#include "GlobalMgr.h"
#include "EnumConvert.h"
#include <QPropertyAnimation>

#pragma execution_character_set("utf-8")

QFont ResultPanel::Font("Microsoft YaHei UI", 16);
QFont ResultPanel::ErrorFont("Microsoft YaHei UI", 10);
QColor ResultPanel::BgColor(207, 207, 207);
QColor ResultPanel::FontColor(0, 0, 0);
QColor ResultPanel::ErrorColor(200, 0, 0);

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

void ResultPanel::resultExchange(ComputeResult result, bool withAnim)
{
	ResultPanelData *resultData = ExchangeProgress > 255 ? ResultA : ResultB;
	if (!withAnim)
	{
		ExchangeProgress = 0;
		resultData = ResultA;
		ExchangeAnim->stop();
	}
	if (result.good())
	{
		resultData->Error = false;
		sprintf(resultData->Text, "= %f", result.Value);
	}
	else 
	{
		resultData->Error = true;
		sprintf(resultData->Text, "´íÎóÌáÊ¾\n%s", EnumConvert::error2string(result.Error));
	}
	if (withAnim)
	{
		if (ExchangeAnim->state() != QAbstractAnimation::Running)
		{
			if (ExchangeProgress > 255)
			{
				ResultPanelData *temp = ResultA;
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
				
				ResultPanelData *temp = ResultA;
				ResultA = ResultB;
				ResultB = temp;

				ExchangeAnim->resume();
			}
		}
	}
}


ResultPanel::ResultPanel(QWidget * parent) : QFrame(parent), Singleton<ResultPanel>()
{
	ResultA = new ResultPanelData;
	ResultB = new ResultPanelData;

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
		int alpha = ShowProgress;
		alpha *= ExchangeProgress > 255 ? ExchangeProgress - 256 : 255 - ExchangeProgress;
		if (alpha > 0)
			alpha = sqrt(alpha);
		ResultPanelData *result = (ExchangeProgress > 255 ? ResultB : ResultA);

		if (result->Error)
		{
			painter.setFont(ErrorFont);
			painter.setPen(QColor(ErrorColor.red(), ErrorColor.green(), ErrorColor.blue(), alpha));
		}
		else
		{
			painter.setFont(Font);
			painter.setPen(QColor(FontColor.red(), FontColor.green(), FontColor.blue(), alpha));
		}
		painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, result->Text);
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

void ResultPanel::showResult(ComputeResult value)
{
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
		resultExchange(value, false);
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
		delete ResultA;
		ResultA = nullptr;
	}
	if (ResultB != nullptr)
	{
		delete ResultB;
		ResultB = nullptr;
	}
}
