#include "PatientShow.h"
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
//#include "ElaNavigationRouter.h"
#include "ElaPopularCard.h"
#include "ElaScrollArea.h"
#include "ElaText.h"

#include "HttpMgr.h"
#include "UserMgr.h"
#include "WebsocketMgr.h"
PatientShow::PatientShow(QWidget *parent)
	: T_BasePage(parent)
	, ui(new Ui::PatientShowClass())
{
	//ui->setupUi(this);
     // 预览窗口标题
    setWindowTitle("Home");

    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_getpatientdata_mod_finish, this,&PatientShow::slot_insert_patientdata);
    // 推荐卡片
    QJsonObject obj;


    obj["name"] = UserMgr::GetInstance()->GetName();
    HttpMgr::GetInstance().get()->PostHttpReq(QUrl("http://134.175.127.33:4000/getpatientdata"), obj, ReqId::GetPatientData, Modules::ReqPatientData);
    WebsocketMgr::GetInstance()->slot_websocket_connect();

    ElaText* titleText = new ElaText(QString("病人监控区域 "), this);
    titleText->setTextPixelSize(35);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(33, 0, 0, 0);
    flowTextLayout->addWidget(titleText);
    // ElaFlowLayout

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    _flowLayout = flowLayout;
    _flowLayout->setContentsMargins(30, 0, 0, 0);
    _flowLayout->setIsAnimation(true);

    // 菜单
    _homeMenu = new ElaMenu(this);
    ElaMenu* checkMenu = _homeMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu->addAction("查看1");
    checkMenu->addAction("查看2");
    checkMenu->addAction("查看3");
    checkMenu->addAction("查看4");

    ElaMenu* checkMenu1 = _homeMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu1->addAction("查看1");
    checkMenu1->addAction("查看2");
    checkMenu1->addAction("查看3");
    checkMenu1->addAction("查看4");

    ElaMenu* checkMenu2 = checkMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu2->addAction("查看1");
    checkMenu2->addAction("查看2");
    checkMenu2->addAction("查看3");
    checkMenu2->addAction("查看4");

    // QKeySequence key = QKeySequence(Qt::CTRL | Qt::Key_S);

    _homeMenu->addSeparator();
    _homeMenu->addElaIconAction(ElaIconType::BoxCheck, "排序方式", QKeySequence::Save);
    _homeMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新");
    QAction* action = _homeMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销");
    /*connect(action, &QAction::triggered, this, [=]() {
        ElaNavigationRouter::getInstance()->navigationRouteBack();
        });*/

    _homeMenu->addElaIconAction(ElaIconType::Copy, "复制");
    _homeMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "显示设置");

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Home");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(flowTextLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(_flowLayout);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget);

    // 初始化提示
    //ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "初始化成功!", 2000);
    //qDebug() << "初始化成功";
}

PatientShow::~PatientShow()
{
	delete ui;
}

void PatientShow::insertpatient(std::shared_ptr<PatientData> patientdata)
{
    ElaPopularCard* homeCard = new ElaPopularCard(this);
    connect(homeCard, &ElaPopularCard::popularCardButtonClicked, this, [=]() {
        /*QDesktopServices::openUrl(QUrl("https://github.com/Liniyous/ElaWidgetTools"));*/
            emit elaTabViewNavigation(patientdata);
        });
    homeCard->setCardPixmap(QPixmap(":/PC_software/image/coffee_candy.jpg"));
    homeCard->setTitle(patientdata->_name);
    int len = patientdata->_temperaturearray.size();
    homeCard->setSubTitle("温度: "+ QString::number(patientdata->_temperaturearray[len - 1].toDouble()));
    homeCard->setInteractiveTips("查看");
    homeCard->setDetailedText(patientdata->_introduce);
    homeCard->setCardFloatPixmap(QPixmap(":/PC_software/image/coffee_candy.jpg"));
    homeCard->setVisible(true);

    _flowLayout->addWidget(homeCard);
}

void PatientShow::slot_insert_patientdata(ReqId id, QString res, ErrorCodes err)
{
    qDebug() << "insert data";
    QJsonDocument doc = QJsonDocument::fromJson(res.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray array = obj["patientslist"].toArray();
    for (QJsonValue item : array)
    {
        QJsonObject aobj = item.toObject();
        std::shared_ptr<PatientData> patientPtr = std::make_shared<PatientData>(
            aobj["id"].toInt(),
            aobj["imageurl"].toString(),
            aobj["introduceurl"].toString(),
            aobj["introduce"].toString(),
            aobj["woundimageurl"].toString(),
            aobj["name"].toString(),
            aobj["temperaturearray"].toArray(),
            aobj["voltagearray"].toArray()
            );
        this->_patientdatemap[aobj["name"].toString()].append(patientPtr);
        this->insertpatient(patientPtr);
    }
}


void PatientShow::mouseReleaseEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::RightButton:
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        _homeMenu->popup(event->globalPosition().toPoint());
#else
        _homeMenu->popup(event->globalPos());
#endif
        break;
    }
    default:
    {
        break;
    }
    }
    ElaScrollPage::mouseReleaseEvent(event);
}
