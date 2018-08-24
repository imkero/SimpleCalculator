#include "VariableWindow.h"
#include "GlobalMgr.h"
#include "ArithmeticPanel.h"
#include "MainWindow.h"
#include <QInputDialog>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

void VariableWindow::eventMemorize()
{
	QListWidgetItem *selected = VariableList->currentItem();
	if (selected != nullptr)
	{
		std::string varName = selected->data(ListItemVarNameRole).toString().toStdString();
		if (g_Data->Variable.modifiable(varName))
		{
			if (g_Data->ExprResult.good())
			{
				g_Data->Variable.set(varName, g_Data->ExprResult.Value);
				refreshItem(selected);
			}
		}
		else
		{
			QMessageBox::warning(this, "存入失败", "常量不能被修改。");
		}
	}
}

void VariableWindow::refreshItem(QListWidgetItem *item)
{
	std::string varName = item->data(ListItemVarNameRole).toString().toStdString();
	item->setText(QString::asprintf("%s\n= %g", varName.c_str(), g_Data->Variable.get(varName)));
}

void VariableWindow::showItems()
{
	VariableList->clear();
	for (auto iter = g_Data->Variable.Constant.cbegin(); iter != g_Data->Variable.Constant.cend(); iter++)
	{
		addVariableItem((*iter).first, (*iter).second);
	}
	for (auto iter = g_Data->Variable.Variable.cbegin(); iter != g_Data->Variable.Variable.cend(); iter++)
	{
		addVariableItem((*iter).first, (*iter).second);
	}
}

void VariableWindow::addVariableItem(const std::string &str, double value)
{
	QListWidgetItem *item = new QListWidgetItem(QString::asprintf("%s\n= %g", str.c_str(), value));
	item->setData(ListItemVarNameRole, str.c_str());
	VariableList->addItem(item);
}

void VariableWindow::eventGetVariable()
{
	QListWidgetItem *selected = VariableList->currentItem();
	if (selected != nullptr)
	{
		std::string varName = selected->data(ListItemVarNameRole).toString().toStdString();
		const Cursor &cursor = g_Data->Cursor.get();
		g_Data->Cursor.get().FocusdExpr->insertVariable(cursor.Pos, varName);
		MainWindow::getInstance()->afterInput(true);
		close();
	}
}

void VariableWindow::eventGetValue()
{
}

void VariableWindow::eventClear()
{
	QListWidgetItem *selected = VariableList->currentItem();
	if (selected != nullptr)
	{
		std::string varName = selected->data(ListItemVarNameRole).toString().toStdString();
		if (g_Data->Variable.modifiable(varName))
		{
			g_Data->Variable.set(varName, 0.0);
			refreshItem(selected);
		}
		else
		{
			QMessageBox::warning(this, "置零失败","常量不能被修改。");
		}
		
	}
}

void VariableWindow::eventClearAll()
{
	g_Data->Variable.clearAll();
	showItems();
}

void VariableWindow::eventAddVariable()
{
	bool ok;
	QString newVarName = QInputDialog::getText(this, "新增变量", "请输入要新增的变量名", QLineEdit::Normal, QString(), &ok);
	if (ok)
	{
		std::string newVarNameStd = newVarName.toStdString();
		if (g_Data->Variable.has(newVarNameStd))
		{
			QMessageBox::warning(this, "变量名重复", "要新增的变量名已存在。");
		}
		else
		{
			g_Data->Variable.set(newVarNameStd, 0.0);
			addVariableItem(newVarNameStd, 0.0);
		}
	}
}

void VariableWindow::eventDeleteVariable()
{
	QListWidgetItem *selected = VariableList->currentItem();
	if (selected != nullptr)
	{
		std::string varName = selected->data(ListItemVarNameRole).toString().toStdString();
		if (g_Data->Variable.modifiable(varName))
		{
			g_Data->Variable.del(varName);
			VariableList->removeItemWidget(selected);
			delete selected;
		}
		else
		{
			QMessageBox::warning(this, "删除失败", "常量不能被删除。");
		}
	}
}

VariableWindow::VariableWindow(QWidget *parent)
	: QMainWindow(parent), Singleton<VariableWindow>()
{
	this->setWindowTitle("变量 & 常量");
	this->resize(550, 400);

	CentralWidget = new QWidget(this);
	this->setCentralWidget(CentralWidget);

	LayoutY = new QVBoxLayout(CentralWidget);
	LayoutButtons = new QHBoxLayout();
	LayoutButtonsSecond = new QHBoxLayout();

	VariableList = new QListWidget(CentralWidget);
	LayoutY->addWidget(VariableList);

	ButtonMemorize = new QPushButton("存入", CentralWidget);
	ButtonGetVariable = new QPushButton("取变量", CentralWidget);
	//ButtonGetValue = new QPushButton("取值", CentralWidget);
	ButtonClear = new QPushButton("置零", CentralWidget);
	ButtonClearAll = new QPushButton("置零所有", CentralWidget);

	ButtonAddVariable = new QPushButton("添加变量", CentralWidget);
	ButtonDeleteVariable = new QPushButton("删除变量", CentralWidget);

	LayoutButtonsSecond->addStretch();
	LayoutButtonsSecond->addWidget(ButtonAddVariable);
	LayoutButtonsSecond->addWidget(ButtonDeleteVariable);

	LayoutButtons->addWidget(ButtonClearAll);
	LayoutButtons->addStretch();
	LayoutButtons->addWidget(ButtonMemorize);
	LayoutButtons->addWidget(ButtonClear);
	LayoutButtons->addWidget(ButtonGetVariable);
	//LayoutButtons->addWidget(ButtonGetValue);

	LayoutY->addLayout(LayoutButtonsSecond);
	LayoutY->addLayout(LayoutButtons);

	VariableList->setStyleSheet("QListWidget{outline:0px; border:1px solid gray; color:black; font-family:\"Microsoft YaHei UI\"; font-size:18px;}"
		"QListWidget::Item{border:none; padding-top:5px; padding-bottom:5px;}"
		"QListWidget::Item:hover{background:#c2c2c2;}"
		"QListWidget::item:selected{background:#a6d8ff;}"
		"QListWidget::item:selected:!active{color:black;}"
		"QListWidget::item:selected:active{color:black;}"
	);
	this->setStyleSheet("QPushButton {font-family:\"Microsoft YaHei UI\";}");
	showItems();

	connect(ButtonAddVariable, SIGNAL(clicked()), this, SLOT(eventAddVariable()));
	connect(ButtonDeleteVariable, SIGNAL(clicked()), this, SLOT(eventDeleteVariable()));
	connect(ButtonMemorize, SIGNAL(clicked()), this, SLOT(eventMemorize()));
	connect(ButtonGetVariable, SIGNAL(clicked()), this, SLOT(eventGetVariable()));
	//connect(ButtonGetValue, SIGNAL(clicked()), this, SLOT(eventGetValue()));
	connect(ButtonClear, SIGNAL(clicked()), this, SLOT(eventClear()));
	connect(ButtonClearAll, SIGNAL(clicked()), this, SLOT(eventClearAll()));
}


VariableWindow::~VariableWindow()
{
}
