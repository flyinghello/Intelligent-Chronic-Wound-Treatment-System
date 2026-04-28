#pragma once

#include "T_BasePage.h"
#include "ui_T_Tablefdc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class T_TablefdcClass; };
QT_END_NAMESPACE
class ElaTableView;
class T_TableViewModel;
class T_Tablefdc : public T_BasePage
{
	Q_OBJECT

public:
	T_Tablefdc(QWidget *parent = nullptr);
	~T_Tablefdc();
public slots:
	void addtablesqldata();
private:
	Ui::T_TablefdcClass *ui;
	ElaTableView* _tableView{ nullptr };
	T_TableViewModel* model;
};
