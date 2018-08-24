#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <string>
#include "Singleton.h"

class VariableWindow : public QMainWindow, public Singleton<VariableWindow>
{
	Q_OBJECT
protected:
	QWidget *CentralWidget;
	
	QVBoxLayout *LayoutY;
	QHBoxLayout *LayoutButtons;
	QHBoxLayout *LayoutButtonsSecond;

	QListWidget *VariableList;

	QPushButton *ButtonMemorize;
	QPushButton *ButtonGetVariable;
	QPushButton *ButtonGetValue;
	QPushButton *ButtonClear;
	QPushButton *ButtonClearAll;

	QPushButton *ButtonAddVariable;
	QPushButton *ButtonDeleteVariable;

	static void refreshItem(QListWidgetItem *);
	void showItems();
	void addVariableItem(const std::string &, double);

	const static int ListItemVarNameRole = Qt::ItemDataRole::UserRole;

protected slots:
	void eventMemorize();
	void eventGetVariable();
	void eventGetValue();
	void eventClear();
	void eventClearAll();
	void eventAddVariable();
	void eventDeleteVariable();

public:
	VariableWindow(QWidget *parent = Q_NULLPTR);
	~VariableWindow();
};

