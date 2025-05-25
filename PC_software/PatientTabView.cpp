#include "PatientTabView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "ElaBreadcrumbBar.h"
#include "ElaPivot.h"
#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"
#include "ElaTabWidget.h"
#include "ElaText.h"
#include "PatientView.h"
#include "T_Addfdc.h"
PatientTabView::PatientTabView(QWidget *parent)
	: T_BasePage(parent)
	, ui(new Ui::PatientTabViewClass())
{

    // 预览窗口标题
    //setWindowTitle(QString::fromLocal8Bit("病人详情 "));
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
    //// ElaTabWidget
    ElaText* tabWidgetText = new ElaText(QString::fromLocal8Bit("病人详情 "), this);
    tabWidgetText->setTextPixelSize(35);
    _tabWidget = new ElaTabWidget(this);
    _tabWidget->setFixedHeight(600);


    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(33, 0, 0, 0);
    flowTextLayout->addWidget(tabWidgetText);

   /* QLabel* page1 = new QLabel(QString::fromLocal8Bit("空 "), this);
    page1->setAlignment(Qt::AlignCenter);
    QFont font = page1->font();
    font.setPixelSize(32);
    page1->setFont(font); 
    _tabWidget->addTab(page1, QIcon(":/PC_software/image/123.jpg"), QString::fromLocal8Bit("空 "));*/

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(flowTextLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addWidget(_tabWidget);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget, true, false, 0);
}

PatientTabView::~PatientTabView()
{
	delete ui;
}

void PatientTabView::AddPatientTabView(std::shared_ptr<PatientData> patientdata)
{
    PatientView *patientview = new PatientView(patientdata,this);
    _tabWidget->addTab(patientview, QIcon(":/PC_software/image/yl.png"), patientdata->_name);
    _tabWidget->setFixedHeight(1000);
}
