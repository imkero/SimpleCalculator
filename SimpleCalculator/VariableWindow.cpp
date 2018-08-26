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
		std::string varName = getVariableName(selected);
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
			QMessageBox::warning(this, "����ʧ��", "�������ܱ��޸ġ�");
		}
	}
}

void VariableWindow::refreshItem(QListWidgetItem *item)
{
	std::string varName = getVariableName(item);
	item->setText(QString::asprintf("%s\n= %g", varName.c_str(), g_Data->Variable.get(varName)));
}

std::string VariableWindow::getVariableName(QListWidgetItem *item)
{
	return item->data(ListItemVarNameRole).toString().toStdString();
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
		eventVariableDblClick(selected);
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
		std::string varName = getVariableName(selected);
		if (g_Data->Variable.modifiable(varName))
		{
			g_Data->Variable.set(varName, 0.0);
			refreshItem(selected);
		}
		else
		{
			QMessageBox::warning(this, "����ʧ��","�������ܱ��޸ġ�");
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
	QString newVarName = QInputDialog::getText(this, "��������", "������Ҫ�����ı�����", QLineEdit::Normal, QString(), &ok);
	if (ok)
	{
		std::string newVarNameStd = newVarName.toStdString();
		if (g_Data->Variable.has(newVarNameStd))
		{
			QMessageBox::warning(this, "�������ظ�", "Ҫ�����ı������Ѵ��ڡ�");
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
		std::string varName = getVariableName(selected);
		if (g_Data->Variable.modifiable(varName))
		{
			g_Data->Variable.del(varName);
			VariableList->removeItemWidget(selected);
			delete selected;
		}
		else
		{
			QMessageBox::warning(this, "ɾ��ʧ��", "�������ܱ�ɾ����");
		}
	}
}

void VariableWindow::eventVariableDblClick(QListWidgetItem *item)
{
	std::string varName = getVariableName(item);
	const Cursor &cursor = g_Data->Cursor.get();
	g_Data->Cursor.get().FocusdExpr->insertVariable(cursor.Pos, varName);
	MainWindow::getInstance()->afterInput(true);
	close();
}

VariableWindow::VariableWindow(QWidget *parent)
	: QDialog(parent), Singleton<VariableWindow>()
{
	this->setWindowTitle("���� & ����");
	this->resize(550, 400);

	LayoutY = new QVBoxLayout(this);
	LayoutButtons = new QHBoxLayout();
	LayoutButtonsSecond = new QHBoxLayout();

	VariableList = new QListWidget(this);
	LayoutY->addWidget(VariableList);

	ButtonMemorize = new QPushButton("����", this);
	ButtonGetVariable = new QPushButton("ȡ����", this);
	//ButtonGetValue = new QPushButton("ȡֵ", this);
	ButtonClear = new QPushButton("����", this);
	ButtonClearAll = new QPushButton("��������", this);

	ButtonAddVariable = new QPushButton("���ӱ���...", this);
	ButtonDeleteVariable = new QPushButton("ɾ������", this);

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

	connect(VariableList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(eventVariableDblClick(QListWidgetItem *)));
}


VariableWindow::~VariableWindow()
{
}