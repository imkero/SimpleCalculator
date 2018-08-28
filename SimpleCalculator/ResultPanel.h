#pragma once
#include <QFrame>
#include <QFont>
#include <QAction>
#include <QMenu>
#include <QWidget>
#include <string>
#include <QPropertyAnimation>
#include "Singleton.h"
#include "ComputeResult.h"

enum ResultPanelDataType
{
	Numberic,
	ErrorText,
	Scientific
};

struct ResultPanelScientificData
{
	char Base[32];
	char Pow[16];
};

class ResultPanelData
{
private:
	char InternalText[256];
public:
	ResultPanelDataType Type;
	char *TextA;
	char *TextB;
	ResultPanelData()
	{
		InternalText[0] = '=';
		InternalText[1] = ' ';
		TextA = InternalText + 2;
		TextB = InternalText + 2 + 128;
	}
	void getCopyContent(std::string &);
	const char *TextWithPrefix()
	{
		return InternalText;
	}
};

struct ResultConfig
{
	bool UserDecided = false;
	bool IsSci = false;
	int Param = -1;
	ResultConfig()
	{
	}
	ResultConfig(bool sci, int param) : IsSci(sci), Param(param), UserDecided(true)
	{
	}
};

class ResultPanel : public QFrame, public Singleton<ResultPanel>
{
	Q_OBJECT
	Q_PROPERTY(int ShowProgress READ getShowProgress WRITE setShowProgress);
	Q_PROPERTY(int ExchangeProgress READ getExchangeProgress WRITE setExchangeProgress);
private:
	static QFont Font;
	static QFont ErrorFont;
	static QFont PowFont;
	static QColor BgColor;
	static QColor FontColor;
	static QColor ErrorColor;

	ResultPanelData *ResultA;
	ResultPanelData *ResultB;

	ComputeResult ResultCache;
	bool Showing = false;

	int ShowProgress = 0;
	int ExchangeProgress = 0;
	
	int getShowProgress();
	void setShowProgress(int);

	int getExchangeProgress();
	void setExchangeProgress(int);

	inline ResultPanelData *getForegroundData()
	{
		return ExchangeProgress > 255 ? ResultB : ResultA;
	}

	inline ResultPanelData *getBackgroundData()
	{
		return ExchangeProgress > 255 ? ResultA : ResultB;
	}

	void resultExchange(bool withAnim);
	void resultExchange(bool withAnim, ResultConfig);

	QPropertyAnimation *ShowAnim;
	QPropertyAnimation *ExchangeAnim;
	QMenu *ContextMenu;
	QAction *ActionDefault;
	QAction *ActionScientificAuto;
	QAction *ActionNumberic;
	QAction *ActionScientific;
	QAction *ActionConfigPinned;

	ResultConfig ConfigCache;

	const static int DigitWidth = 15;
	constexpr static double AutoSwitchSciMinimum = 1E15;
	constexpr static double NumbericMinimum = 1E-15;
public:
	ResultPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void hideResult();
	void showResult(ComputeResult);
	~ResultPanel();

signals:
	void signalShowProgressUpdate();
	void signalExchangeProgressUpdate();
	
protected:
	void contextMenuEvent(QContextMenuEvent* e);

protected slots:
	void eventCopyContent();
	void eventSwitchDefaultOutput();
	void eventSwitchScientificAutoOutput();
	void eventSwitchNumbericOutput();
	void eventSwitchScientificOutput();
};

