#pragma once
#include <QFrame>
#include <QFont>
#include <QWidget>
#include <QPropertyAnimation>
#include "Singleton.h"

class ResultPanel : public QFrame, public Singleton<ResultPanel>
{
	Q_OBJECT
	Q_PROPERTY(int ShowProgress READ getShowProgress WRITE setShowProgress);
	Q_PROPERTY(int ExchangeProgress READ getExchangeProgress WRITE setExchangeProgress);
private:
	static QFont Font;
	static QColor BgColor;
	static QColor FontColor;

	char *ResultA;
	char *ResultB;

	int ShowProgress = 0;
	int ExchangeProgress = 0;
	
	int getShowProgress();
	void setShowProgress(int);

	int getExchangeProgress();
	void setExchangeProgress(int);

	void resultExchange(double, bool withAnim);

	QPropertyAnimation *ShowAnim;

	QPropertyAnimation *ExchangeAnim;

public:
	ResultPanel(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void hide();
	void showResult(double);
	~ResultPanel();

signals:
	void signalShowProgressUpdate();
	void signalExchangeProgressUpdate();
	
};

