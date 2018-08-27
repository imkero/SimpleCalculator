#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <string>
#include "Singleton.h"

#pragma execution_character_set("utf-8")

class VariableWindow : public QDialog, public Singleton<VariableWindow>
{
	Q_OBJECT
protected:
	constexpr static char *VariableFileFilter = "SCAL 变量文件 (*.svar)";

	QVBoxLayout *LayoutY;
	QHBoxLayout *LayoutButtons;
	QHBoxLayout *LayoutButtonsSecond;

	QListWidget *VariableList;

	QPushButton *ButtonMemorize;
	QPushButton *ButtonGetVariable;
	QPushButton *ButtonSetValue;
	QPushButton *ButtonClear;
	QPushButton *ButtonClearAll;

	QPushButton *ButtonAddVariable;
	QPushButton *ButtonDeleteVariable;

	QPushButton *ButtonOpenFile;
	QPushButton *ButtonSaveFile;

	static void refreshItem(QListWidgetItem *);
	static std::string getVariableName(QListWidgetItem *);
	void showItems();
	void addVariableItem(const std::string &, double);
	void beforeClose();
	void reject();
	void closeEvent(QCloseEvent *event);

	const static int ListItemVarNameRole = Qt::ItemDataRole::UserRole;

protected slots:
	void eventMemorize();
	void eventGetVariable();
	void eventSetValue();
	void eventClear();
	void eventClearAll();
	void eventAddVariable();
	void eventDeleteVariable();
	void eventVariableDblClick(QListWidgetItem *);
	void eventOpenFile();
	void eventSaveFile();

public:
	VariableWindow(QWidget *parent = Q_NULLPTR);
	~VariableWindow();
};

