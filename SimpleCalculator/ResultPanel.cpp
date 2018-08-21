#include <cstring>
#include <QDebug>
#include <QPainter>
#include <QPropertyAnimation>
#include "ResultPanel.h"
#include "GlobalMgr.h"
#include "EnumConvert.h"
#include "Util.h"

#pragma execution_character_set("utf-8")

QFont ResultPanel::Font("Microsoft YaHei UI", 16);
QFont ResultPanel::PowFont("Microsoft YaHei UI", 12);
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

	ContextMenu = new QMenu(this);

	QAction *actionCopy = ContextMenu->addAction("复制");
	ContextMenu->addSeparator();
	QActionGroup *group = new QActionGroup(ContextMenu);
	ActionNumberic = group->addAction("小数");
	ActionScientific = group->addAction("科学计数法");
	ActionNumberic->setCheckable(true);
	ActionNumberic->setChecked(true);
	ActionScientific->setCheckable(true);
	ContextMenu->addAction(ActionNumberic);
	ContextMenu->addAction(ActionScientific);
	ContextMenu->addSeparator();
	QAction *actionFix = ContextMenu->addAction("保留小数");
	QAction *actionSci = ContextMenu->addAction("保留有效数字");
	
}

void ResultPanel::resultExchange(bool withAnim, ResultConfig cfg)
{
	ResultPanelData *resultData = ExchangeProgress > 255 ? ResultA : ResultB;
	if (!withAnim)
	{
		ExchangeProgress = 0;
		resultData = ResultA;
		ExchangeAnim->stop();
	}
	if (ResultCache.good())
	{
		if (cfg.UserDecided)
		{
			// To-Do
		}
		else
		{
			if ((abs(ResultCache.Value) < 1E10 && abs(ResultCache.Value) >= 0.01) || ResultCache.Value == 0)
			{
				resultData->Type = Numberic;
				sprintf(resultData->Data.Text, "= %.14g", ResultCache.Value);
			}
			else
			{
				char buffer[128];
				resultData->Type = Scientific;
				sprintf(buffer, "%.14e", ResultCache.Value);
				char *pPow = strchr(buffer, 'e');
				if (pPow != nullptr)
				{
					int baseCount = pPow - buffer;
					resultData->Data.Scientific.Base[0] = '=';
					resultData->Data.Scientific.Base[1] = ' ';
					strncpy(resultData->Data.Scientific.Base + 2, buffer, baseCount);
					resultData->Data.Scientific.Base[baseCount + 2] = '\0';
					eatExtraZero(resultData->Data.Scientific.Base);
					pPow++;
					if (*(pPow + 1) == '0') {
						pPow[1] = pPow[0];
						pPow++;
					}
					if (*pPow == '+') pPow++;
					strcpy(resultData->Data.Scientific.Pow, pPow);
				}
				else
				{
					resultData->Type = ErrorText;
					sprintf(resultData->Data.Text, "错误提示\n%s", EnumConvert::error2string(ValidateErrorType::InternalError));
				}
			}
		}
	}
	else
	{
		resultData->Type = ErrorText;
		sprintf(resultData->Data.Text, "错误提示\n%s", EnumConvert::error2string(ResultCache.Error));
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

		switch (result->Type)
		{
		case Numberic:
			painter.setFont(Font);
			painter.setPen(QColor(FontColor.red(), FontColor.green(), FontColor.blue(), alpha));
			painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, result->Data.Text);
			break;
		case Scientific:
			painter.setPen(QColor(FontColor.red(), FontColor.green(), FontColor.blue(), alpha));
			{
				painter.setFont(PowFont);
				painter.drawText(QRect(15, 5, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignTop, result->Data.Scientific.Pow);

				QRect r2(15, 0, r.width() - 41 - painter.fontMetrics().width(result->Data.Scientific.Pow), r.height() - 1);
				painter.setFont(Font);
				painter.drawText(r2, Qt::AlignRight | Qt::AlignCenter, "×10");

				r2.setRight(r2.right() - painter.fontMetrics().width("×10"));
				painter.drawText(r2, Qt::AlignRight | Qt::AlignCenter, result->Data.Scientific.Base);
			}
			break;
		case ErrorText:
			painter.setFont(ErrorFont);
			
			painter.setPen(QColor(ErrorColor.red(), ErrorColor.green(), ErrorColor.blue(), alpha));
			painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, result->Data.Text);
			break;
		}
		
	}
}

void ResultPanel::hideResult()
{
	Showing = false;
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
	Showing = true;
	ResultCache = value;
	if (ShowAnim->state() != QAbstractAnimation::Running)
	{
		if (ShowAnim->currentTime() != ShowAnim->duration())
		{
			if (ShowAnim->currentTime() == 0)
			{
				resultExchange(false);
			}
			else
			{
				resultExchange(true);
			}
			ShowAnim->setDirection(QAbstractAnimation::Forward);
			ShowAnim->start();
		}
		else
		{
			resultExchange(true);
		}
	}
	else if (ShowAnim->direction() == QAbstractAnimation::Backward)
	{
		resultExchange(false);
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

void ResultPanel::contextMenuEvent(QContextMenuEvent * e)
{
	if (Showing)
		ContextMenu->exec(e->globalPos());
}
