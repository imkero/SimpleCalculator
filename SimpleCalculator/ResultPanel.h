#pragma once
#include <QFrame>
#include <QFont>
#include <QAction>
#include <QMenu>
#include <QWidget>
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

struct ResultPanelData
{
	ResultPanelDataType Type;
	union {
		char Text[256];
		ResultPanelScientificData Scientific;
	} Data;
};

struct ResultConfig
{
	bool UserDecided = false;
	bool IsSci = false;
	int Param = -1;
	ResultConfig()
	{
	}
	ResultConfig(bool sci, int param) : IsSci(sci), Param(param)
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

	void resultExchange(bool withAnim, ResultConfig = ResultConfig());

	QPropertyAnimation *ShowAnim;
	QPropertyAnimation *ExchangeAnim;
	QMenu *ContextMenu;
	QAction *ActionNumberic;
	QAction *ActionScientific;

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
};

