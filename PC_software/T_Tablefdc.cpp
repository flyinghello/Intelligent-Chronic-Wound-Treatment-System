#include "T_Tablefdc.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

#include "ElaTableView.h"
#include "ElaText.h"
#include "T_TableViewModel.h"


T_Tablefdc::T_Tablefdc(QWidget *parent)
	: T_BasePage(parent)
	, ui(new Ui::T_TablefdcClass())
{
    _tableView = new ElaTableView(this);
    // ElaScrollBar* tableViewFloatScrollBar = new ElaScrollBar(_tableView->verticalScrollBar(), _tableView);
    // tableViewFloatScrollBar->setIsAnimation(true);
    model = new T_TableViewModel(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(model);
    _tableView->setAlternatingRowColors(true);
    _tableView->setIconSize(QSize(38, 38));
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 60);
        _tableView->setColumnWidth(1, 205);
        _tableView->setColumnWidth(2, 170);
        _tableView->setColumnWidth(3, 150);
        _tableView->setColumnWidth(4, 60);
        });
    QHBoxLayout* tableViewLayout = new QHBoxLayout();
    tableViewLayout->setContentsMargins(0, 0, 10, 0);
    tableViewLayout->addWidget(_tableView);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle(QString::fromLocal8Bit("数据库数据 "));
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addSpacing(0);
    centerVLayout->addLayout(tableViewLayout);
    addCentralWidget(centralWidget, true, false, 0);
}

T_Tablefdc::~T_Tablefdc()
{
	delete ui;
}

void T_Tablefdc::addtablesqldata()
{
    qDebug() << "addsqldata";
}
