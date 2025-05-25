#include "PatientView.h"
#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "ElaAcrylicUrlCard.h"
#include "ElaFlowLayout.h"
#include "ElaImageCard.h"
#include "ElaMenu.h"
#include "ElaMessageBar.h"
#include "ElaPopularCard.h"
#include "ElaScrollArea.h"
#include "ElaText.h"
#include <ElaScrollPageArea.h>

#include "HttpMgr.h"
#include <QThreadPool>
#include "WebsocketMgr.h"

PatientView::PatientView(std::shared_ptr<PatientData>patientdata,QWidget *parent)
	: T_BasePage(parent),_patientdata(patientdata)
	, ui(new Ui::PatientViewClass())
{
    connect(WebsocketMgr::GetInstance().get(), &WebsocketMgr::sig_change_patient_data, this, &PatientView::slot_change_patient_data);
    //ui->setupUi(this);

    createCustomWidget(QString::fromLocal8Bit(" "));

    setTitleVisible(false);
    setContentsMargins(2, 0, 0, 0);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    // ElaFlowLayout

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setContentsMargins(30, 0, 0, 0);
    flowLayout->setIsAnimation(true);
    //flowLayout->addWidget(new ChartWithHover(this));

    _promotionView = new ElaPromotionView(this);
    _userview = new ElaPopularCard(this);
    qDebug() <<"userviewsize:" << _userview->size();
    connect(_userview, &ElaPopularCard::popularCardButtonClicked, this, [=]() {
        /*QDesktopServices::openUrl(QUrl("https://github.com/Liniyous/ElaWidgetTools"));*/
        //emit elaTabViewNavigation(patientdata);
        });
    _userview->setCardPixmap(QPixmap(":/PC_software/image/coffee_candy.jpg"));
    _userview->setTitle(patientdata->_name);
    int len = patientdata->_temperaturearray.size();
    _userview->setSubTitle("温度: " + QString::number(patientdata->_temperaturearray[len - 1].toDouble()));
    _userview->setInteractiveTips(QString::fromLocal8Bit("提交医嘱 "));
    _userview->setDetailedText(patientdata->_introduce);
    _userview->setCardButtontext(QString::fromLocal8Bit("提交医嘱 "));
    _userview->setCardFloatPixmap(QPixmap(":/PC_software/image/coffee_candy.jpg"));
    _userview->setVisible(true);

    addimageview(_promotionView);
    adduserview(_userview);
    addintroduce(new PatientInfoWidget(this));

    ElaScrollPageArea* chartsArea = new ElaScrollPageArea(this);
    chartsArea->setFixedHeight(500);
    QHBoxLayout* chartsLayout = new QHBoxLayout(chartsArea);

    _charwithhover = new ChartWithHover(this);
    _charwithhover->createLineSeries(patientdata);

    chartsLayout->addWidget(_charwithhover);

    QVBoxLayout* cardsLayout = new QVBoxLayout(chartsArea);

    CardWidget *c1 = new CardWidget(this);
    _c1 = c1;
    c1->AddImage(":/PC_software/image/t.png");
    c1->ChangetempLabel(0.0, QString::fromLocal8Bit("温度:"));
    CardWidget *c2 = new CardWidget(this);
    _c2 = c2;
    c2->AddImage(":/PC_software/image/v.png");
    c2->ChangetempLabel(0.0, QString::fromLocal8Bit("电压:"));
    CardWidget *c3 = new CardWidget(this);
    c3->AddImage(":/PC_software/image/g.png");
    c3->AddButton();
    cardsLayout->addWidget(c1);
    cardsLayout->addWidget(c2);
    cardsLayout->addWidget(c3);
    //cardsLayout->addStretch();
    chartsLayout->addLayout(cardsLayout);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle(patientdata->_name);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(flowTextLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(flowLayout);
    centerVLayout->addWidget(chartsArea);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget);

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_getPatientViewWoundImage_mod_finish, this, &PatientView::slot_getPatientViewWoundImage_mod_finish);

    HttpMgr::GetInstance().get()->AddQueGetImageHttpReq(QUrl("http://134.175.127.33:80/111.jpg"), ReqId::GetPatientViewWoundImage, Modules::ReqPatientViewWoundImage);
    HttpMgr::GetInstance().get()->AddQueGetImageHttpReq(QUrl("http://134.175.127.33:80/222.png"), ReqId::GetPatientViewWoundImage, Modules::ReqPatientViewWoundImage);

    /*HttpMgr::GetInstance().get()->GetImageHttpReq(QUrl("http://134.175.127.33:80/111.jpg"),ReqId::GetPatientViewWoundImage,Modules::ReqPatientViewWoundImage);
    HttpMgr::GetInstance().get()->GetImageHttpReq(QUrl("http://134.175.127.33:80/222.png"), ReqId::GetPatientViewWoundImage, Modules::ReqPatientViewWoundImage);*/
}

void PatientView::slot_getPatientViewWoundImage_mod_finish(ReqId id, QByteArray res, ErrorCodes err)
{
    if (this->_cardnum >= 2)
    {
        return;
    }

    for (int i = 0; i < 1; i++)
    {
        if (this->_cardnum == 0)
        {
            addimage(res, QString::fromLocal8Bit("伤口图片 "), QString::fromLocal8Bit(" "));
        }
        else
        {
            addimage(res, QString::fromLocal8Bit("伤口判定 "), QString::fromLocal8Bit("算法结果: "));
        }
    }
}

PatientView::~PatientView()
{
	delete ui;
}

void PatientView::slot_change_patient_data(QJsonObject obj)
{
    // 获取 temperature 和 voltage 字段，并去除空格
    QString tempStr = obj["temperature"].toVariant().toString().trimmed();
    QString voltStr = obj["voltage"].toVariant().toString().trimmed();

    // 转换为 double
    double t = tempStr.toDouble();
    double v = voltStr.toDouble();

    _c1->ChangetempLabel(t, QString::fromLocal8Bit("温度:"));
    _c2->ChangetempLabel(v, QString::fromLocal8Bit("电压:"));
    // 调用 changeLineSeries() 方法
    _charwithhover->changeLineSeries(QPointF(9, t), QPointF(9, v));
}

