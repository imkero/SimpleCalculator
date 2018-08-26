#include <cstring>
#include <sstream>
#include <iomanip>
#include <QApplication>
#include <QClipboard>
#include <QPainter>
#include <QPropertyAnimation>
#include <QInputDialog>
#include "ResultPanel.h"
#include "MainWindow.h"
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

	QAction *actionCopy = ContextMenu->addAction("复制 (&C)");
	ContextMenu->addSeparator();

	ActionDefault = ContextMenu->addAction("默认显示 (&D)");
	ActionScientificAuto = ContextMenu->addAction("科学计数法 (&S)");
	ActionNumberic = ContextMenu->addAction("保留小数 (&F)");
	ActionScientific = ContextMenu->addAction("保留有效数字 (&E)");
	ContextMenu->addSeparator();

	ActionConfigPinned = ContextMenu->addAction("显示设置保留 (&R)");

	QActionGroup *group = new QActionGroup(ContextMenu);
	group->addAction(ActionDefault);
	group->addAction(ActionScientificAuto);
	group->addAction(ActionNumberic);
	group->addAction(ActionScientific);
	
	ActionDefault->setCheckable(true);
	ActionScientificAuto->setCheckable(true);
	ActionNumberic->setCheckable(true);
	ActionScientific->setCheckable(true);
	ActionConfigPinned->setCheckable(true);

	ActionDefault->setChecked(true);

	connect(actionCopy, SIGNAL(triggered(bool)), this, SLOT(eventCopyContent()));
	connect(ActionDefault, SIGNAL(triggered(bool)), this, SLOT(eventSwitchDefaultOutput()));
	connect(ActionScientificAuto, SIGNAL(triggered(bool)), this, SLOT(eventSwitchScientificAutoOutput()));
	connect(ActionNumberic, SIGNAL(triggered(bool)), this, SLOT(eventSwitchNumbericOutput()));
	connect(ActionScientific, SIGNAL(triggered(bool)), this, SLOT(eventSwitchScientificOutput()));
}

void ResultPanel::resultExchange(bool withAnim)
{
	if (ActionConfigPinned->isChecked())
	{
		resultExchange(withAnim, ConfigCache);
	}
	else
	{
		resultExchange(withAnim, ResultConfig());
	}
}

void ResultPanel::resultExchange(bool withAnim, ResultConfig cfg)
{
	ConfigCache = cfg;
	if (cfg.UserDecided)
	{
		if (cfg.IsSci)
		{
			if (cfg.Param == 0)
				ActionScientificAuto->setChecked(true);
			else
				ActionScientific->setChecked(true);
		}
		else
			ActionNumberic->setChecked(true);
	}
	else
	{
		ActionDefault->setChecked(true);
	}

	ResultPanelData *resultData = getBackgroundData();
	if (!withAnim)
	{
		ExchangeProgress = 0;
		resultData = ResultA;
		ExchangeAnim->stop();
	}
	if (ResultCache.good())
	{
		CompType absValue = abs(ResultCache.Value);
		if (absValue >= AutoSwitchSciMinimum)
		{
			if (!cfg.UserDecided || !cfg.IsSci)
			{
				cfg.IsSci = true;
				cfg.Param = DigitWidth;
			}
		}
		else if (!cfg.UserDecided)
		{
			cfg.IsSci = absValue <= 0.01 && absValue != 0;
			cfg.Param = DigitWidth;
		}
		
		std::stringstream buffer;
		std::string bufferStr = "";

		if (cfg.IsSci)
		{
			if (cfg.UserDecided && cfg.Param == 0)
			{
				cfg.UserDecided = false;
				cfg.Param = DigitWidth;
			}
			buffer << std::scientific;
			buffer << std::setprecision(cfg.Param - 1);
			buffer << ResultCache.Value;

			resultData->Type = Scientific;
			buffer >> bufferStr;
		
			std::size_t ePos = bufferStr.rfind("e");

			std::string base = bufferStr.substr(0, ePos);
			std::string pow = bufferStr.substr(ePos + 1);

			if (!cfg.UserDecided)
			{
				std::size_t edge = base.find_last_not_of("0");
				edge = base.find_last_not_of(".", edge);
				strncpy(resultData->Base, base.c_str(), edge + 1);
				resultData->Base[edge + 1] = '\0';
			}
			else
			{
				strcpy(resultData->Base, base.c_str());
			}

			char *p = resultData->Pow;
			if (pow[0] == '-')
			{
				*p = '-';
				p++;
			}
			strcpy(p, pow[1] == '0' ? pow.c_str() + 2 : pow.c_str() + 1);
			
		}
		else
		{
			buffer.precision(DigitWidth);
			buffer << std::showpoint << ResultCache.Value;

			resultData->Type = Numberic;
			buffer >> bufferStr;
			if (!cfg.UserDecided)
			{
				std::size_t edge = bufferStr.find_last_not_of('0');
				edge = bufferStr.find_last_not_of('.', edge);
				strncpy(resultData->Text, bufferStr.c_str(), edge + 1);
				resultData->Base[edge + 1] = '\0';
			}
			else
			{
				std::size_t pointPos = bufferStr.rfind('.');
				int width = bufferStr.length() - pointPos - 1;
				if (absValue < NumbericMinimum || width > cfg.Param)
				{
					buffer.clear();
					bufferStr.clear();
					buffer.precision(cfg.Param);
					buffer << std::showpoint << std::fixed << ResultCache.Value;
					buffer >> bufferStr;
				}
				strcpy(resultData->Text, bufferStr.c_str());
			}
		}
	}
	else
	{
		resultData->Type = ErrorText;
		sprintf(resultData->Text, "错误提示\n%s", EnumConvert::error2string(ResultCache.Error));
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
			painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, result->TextWithPrefix());
			break;
		case Scientific:
			painter.setPen(QColor(FontColor.red(), FontColor.green(), FontColor.blue(), alpha));
			{
				painter.setFont(PowFont);
				painter.drawText(QRect(15, 5, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignTop, result->Pow);

				QRect r2(15, 0, r.width() - 41 - painter.fontMetrics().width(result->Pow), r.height() - 1);
				painter.setFont(Font);
				painter.drawText(r2, Qt::AlignRight | Qt::AlignCenter, "×10");

				r2.setRight(r2.right() - painter.fontMetrics().width("×10"));
				painter.drawText(r2, Qt::AlignRight | Qt::AlignCenter, result->TextWithPrefix());
			}
			break;
		case ErrorText:
			painter.setFont(ErrorFont);
			
			painter.setPen(QColor(ErrorColor.red(), ErrorColor.green(), ErrorColor.blue(), alpha));
			painter.drawText(QRect(15, 0, r.width() - 41, r.height() - 1), Qt::AlignRight | Qt::AlignCenter, result->Text);
			break;
		}
		
	}
}

void ResultPanel::hideResult()
{
	Showing = false;
	if (ShowAnim->state() != QAbstractAnimation::Running)
	{
		if (ShowAnim->currentTime() != 0)
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
	if (ShowAnim->state() == QAbstractAnimation::Running)
	{
		if (ShowAnim->direction() == QAbstractAnimation::Forward)
		{
			resultExchange(true);
		}
		else
		{
			ShowAnim->setDirection(QAbstractAnimation::Forward);
			ShowAnim->start();
		}
	}
	else
	{
		if (ShowAnim->currentTime() != ShowAnim->duration())
		{
			// not shown
			resultExchange(false);
			ShowAnim->setDirection(QAbstractAnimation::Forward);
			ShowAnim->start();
		}
		else
		{
			// showing
			resultExchange(true);
		}
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
	{
		ContextMenu->exec(e->globalPos());
	}
	e->accept();
}

void ResultPanel::eventCopyContent()
{
	if (Showing)
	{
		std::string copyContent;
		getForegroundData()->getCopyContent(copyContent);
		QApplication::clipboard()->setText(copyContent.c_str());
	}
}

void ResultPanel::eventSwitchDefaultOutput()
{
	if (Showing && ActionDefault->isChecked())
	{
		resultExchange(true, ResultConfig());
	}
}
void ResultPanel::eventSwitchScientificAutoOutput()
{
	if (Showing && ActionScientificAuto->isChecked())
	{
		resultExchange(true, ResultConfig(true, 0));
	}
}

void ResultPanel::eventSwitchNumbericOutput()
{
	if (Showing && ActionNumberic->isChecked())
	{
		bool ok = false;

		int param = QInputDialog::getInt(MainWindow::getInstance(), "保留小数", QString::asprintf("请输入要保留的小数位数 (0 - %d)", DigitWidth), 0, 0, DigitWidth, 1, &ok);
		if (ok)
			resultExchange(true, ResultConfig(false, param));
	}
}

void ResultPanel::eventSwitchScientificOutput()
{
	if (Showing && ActionScientific->isChecked())
	{
		bool ok = false;

		int param = QInputDialog::getInt(MainWindow::getInstance(), "保留有效数字", QString::asprintf("请输入要保留的有效数字位数 (2 - %d)", DigitWidth), 2, 2, DigitWidth, 1, &ok);
		if (ok)
			resultExchange(true, ResultConfig(true, param));
	}
}

void ResultPanelData::getCopyContent(std::string &out)
{
	switch (Type)
	{
	case Numberic:
		out = Text;
		break;
	case Scientific:
		out = Base;
		out += "*10^";
		out += Pow;
		break;
	case ErrorText:
		out = Text;
		break;
	}
}
