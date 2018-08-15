#pragma once
#include <QFrame>
#include <QFont>
#include <QWidget>
#include <QPropertyAnimation>
#include "Singleton.h"
#include "ComputeResult.h"

struct ResultPanelData
{
	char Text[256];
	bool Error = false;
};

class ResultPanel : public QFrame, public Singleton<ResultPanel>
{
	Q_OBJECT
	Q_PROPERTY(int ShowProgress READ getShowProgress WRITE setShowProgress);
	Q_PROPERTY(int ExchangeProgress READ getExchangeProgress WRITE setExchangeProgress);
private:
	static QFont Font;
	static QFont ErrorFont;
	static QColor BgColor;
	static QColor FontColor;
	static QColor ErrorColor;

	ResultPanelData *ResultA;
	ResultPanelData *ResultB;

	int ShowProgress = 0;
	int ExchangeProgress = 0;
	
	int getShowProgress();
	void setShowProgress(int);

	int getExchangeProgress();
	void setExchangeProgress(int);

	void resultExchange(ComputeResult, bool withAnim);

	QPropertyAnimation *ShowAnim;

	QPropertyAnimation *ExchangeAnim;

public:
	ResultPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void hide();
	void showResult(ComputeResult);
	~ResultPanel();

signals:
	void signalShowProgressUpdate();
	void signalExchangeProgressUpdate();
	
};

