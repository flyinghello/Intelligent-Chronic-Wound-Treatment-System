#include "Appshow.h"
#include <QDebug>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include "ElaContentDialog.h"
#include "ElaDockWidget.h"
#include "ElaEventBus.h"
#include "ElaLog.h"
#include "ElaMenu.h"
#include "ElaMenuBar.h"
#include "ElaProgressBar.h"
#include "ElaStatusBar.h"
#include "ElaText.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"
#include "T_About.h"
#include "T_BaseComponents.h"
#include "T_Card.h"
#include "T_Graphics.h"
#include "T_ListView.h"
#include "T_Setting.h"
#include "T_TableView.h"
#include "T_TreeView.h"
#ifdef Q_OS_WIN
#include "T_ElaScreen.h"
#endif
#include "T_Home.h"
#include "T_Icon.h"
#include "T_LogWidget.h"
#include "T_Navigation.h"
#include "T_Popup.h"
#include "T_UpdateWidget.h"

#include "PatientShow.h"
#include "PatientTabView.h"


Appshow::Appshow(QWidget *parent)
	: ElaWindow(parent)
	, ui(new Ui::AppshowClass())
{
	ui->setupUi(this);
    initWindow();

    ////���Ⲽ��
    //initEdgeLayout();

    ////���Ĵ���
    initContent();

    //// ����Ĭ�Ϲر��¼�
    _closeDialog = new ElaContentDialog(this);
    connect(_closeDialog, &ElaContentDialog::rightButtonClicked, this, &ElaWindow::closeWindow);
    connect(_closeDialog, &ElaContentDialog::middleButtonClicked, this, &ElaWindow::showMinimized);
    this->setIsDefaultClosed(false);
    connect(this, &ElaWindow::closeButtonClicked, this, [=]() {
        _closeDialog->exec();
        });

    ////�ƶ�������
    moveToCenter();
}

Appshow::~Appshow()
{
	delete ui;
}

void Appshow::initWindow()
{
    // setIsEnableMica(true);
// setIsCentralStackedWidgetTransparent(true);
    setWindowIcon(QIcon(":/PC_software/image/yl.png"));
    resize(1200, 740);
    //eTheme->setThemeMode(ElaThemeType::Dark);
    // ElaLog::getInstance()->initMessageLog(true);
     //eApp->setThemeMode(ElaThemeType::Dark);
    // setIsNavigationBarEnable(false);
    // setNavigationBarDisplayMode(ElaNavigationType::Compact);
    // setWindowButtonFlag(ElaAppBarType::MinimizeButtonHint, false);
    setUserInfoCardPixmap(QPixmap(":/PC_software/image/coffee_candy.jpg"));
    setUserInfoCardTitle("coffee_candy");
    setUserInfoCardSubTitle("3272987107@qq.com");
    setWindowTitle(QString::fromLocal8Bit("΢������"));
    // setIsStayTop(true);
    // setUserInfoCardVisible(false);
}

void Appshow::initEdgeLayout()
{
    //�˵���
    ElaMenuBar* menuBar = new ElaMenuBar(this);
    menuBar->setFixedHeight(30);
    QWidget* customWidget = new QWidget(this);
    QVBoxLayout* customLayout = new QVBoxLayout(customWidget);
    customLayout->setContentsMargins(0, 0, 0, 0);
    customLayout->addWidget(menuBar);
    customLayout->addStretch();
    // this->setMenuBar(menuBar);
    this->setCustomWidget(ElaAppBarType::MiddleArea, customWidget);
    this->setCustomWidgetMaximumWidth(500);

    menuBar->addElaIconAction(ElaIconType::AtomSimple, "�����˵�");
    ElaMenu* iconMenu = menuBar->addMenu(ElaIconType::Aperture, "ͼ��˵�");
    iconMenu->setMenuItemHeight(27);
    iconMenu->addElaIconAction(ElaIconType::BoxCheck, "����ʽ", QKeySequence::SelectAll);
    iconMenu->addElaIconAction(ElaIconType::Copy, "����");
    iconMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "��ʾ����");
    iconMenu->addSeparator();
    iconMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "ˢ��");
    iconMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "����");
    menuBar->addSeparator();
    ElaMenu* shortCutMenu = new ElaMenu("��ݲ˵�(&A)", this);
    shortCutMenu->setMenuItemHeight(27);
    shortCutMenu->addElaIconAction(ElaIconType::BoxCheck, "����ʽ", QKeySequence::Find);
    shortCutMenu->addElaIconAction(ElaIconType::Copy, "����");
    shortCutMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "��ʾ����");
    shortCutMenu->addSeparator();
    shortCutMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "ˢ��");
    shortCutMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "����");
    menuBar->addMenu(shortCutMenu);

    menuBar->addMenu("�����˵�(&B)")->addElaIconAction(ElaIconType::ArrowRotateRight, "����ѡ��");
    menuBar->addMenu("�����˵�(&C)")->addElaIconAction(ElaIconType::ArrowRotateRight, "����ѡ��");
    menuBar->addMenu("�����˵�(&E)")->addElaIconAction(ElaIconType::ArrowRotateRight, "����ѡ��");
    menuBar->addMenu("�����˵�(&F)")->addElaIconAction(ElaIconType::ArrowRotateRight, "����ѡ��");
    menuBar->addMenu("�����˵�(&G)")->addElaIconAction(ElaIconType::ArrowRotateRight, "����ѡ��");

    //������
    ElaToolBar* toolBar = new ElaToolBar("������", this);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    toolBar->setToolBarSpacing(3);
    toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolBar->setIconSize(QSize(25, 25));
    // toolBar->setFloatable(false);
    // toolBar->setMovable(false);
    ElaToolButton* toolButton1 = new ElaToolButton(this);
    toolButton1->setElaIcon(ElaIconType::BadgeCheck);
    toolBar->addWidget(toolButton1);
    ElaToolButton* toolButton2 = new ElaToolButton(this);
    toolButton2->setElaIcon(ElaIconType::ChartUser);
    toolBar->addWidget(toolButton2);
    toolBar->addSeparator();
    ElaToolButton* toolButton3 = new ElaToolButton(this);
    toolButton3->setElaIcon(ElaIconType::Bluetooth);
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton3->setText("Bluetooth");
    toolBar->addWidget(toolButton3);
    ElaToolButton* toolButton4 = new ElaToolButton(this);
    toolButton4->setElaIcon(ElaIconType::BringFront);
    toolBar->addWidget(toolButton4);
    toolBar->addSeparator();
    ElaToolButton* toolButton5 = new ElaToolButton(this);
    toolButton5->setElaIcon(ElaIconType::ChartSimple);
    toolBar->addWidget(toolButton5);
    ElaToolButton* toolButton6 = new ElaToolButton(this);
    toolButton6->setElaIcon(ElaIconType::FaceClouds);
    toolBar->addWidget(toolButton6);
    ElaToolButton* toolButton8 = new ElaToolButton(this);
    toolButton8->setElaIcon(ElaIconType::Aperture);
    toolBar->addWidget(toolButton8);
    ElaToolButton* toolButton9 = new ElaToolButton(this);
    toolButton9->setElaIcon(ElaIconType::ChartMixed);
    toolBar->addWidget(toolButton9);
    ElaToolButton* toolButton10 = new ElaToolButton(this);
    toolButton10->setElaIcon(ElaIconType::Coins);
    toolBar->addWidget(toolButton10);
    ElaToolButton* toolButton11 = new ElaToolButton(this);
    toolButton11->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton11->setElaIcon(ElaIconType::AlarmPlus);
    toolButton11->setText("AlarmPlus");
    toolBar->addWidget(toolButton11);
    ElaToolButton* toolButton12 = new ElaToolButton(this);
    toolButton12->setElaIcon(ElaIconType::Crown);
    toolBar->addWidget(toolButton12);
    QAction* test = new QAction(this);
    test->setMenu(new QMenu(this));

    ElaProgressBar* progressBar = new ElaProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setFixedWidth(350);
    toolBar->addWidget(progressBar);

    this->addToolBar(Qt::TopToolBarArea, toolBar);

    //ͣ������
    ElaDockWidget* logDockWidget = new ElaDockWidget("��־��Ϣ", this);
    logDockWidget->setWidget(new T_LogWidget(this));
    this->addDockWidget(Qt::RightDockWidgetArea, logDockWidget);
    resizeDocks({ logDockWidget }, { 200 }, Qt::Horizontal);

    ElaDockWidget* updateDockWidget = new ElaDockWidget("��������", this);
    updateDockWidget->setWidget(new T_UpdateWidget(this));
    this->addDockWidget(Qt::RightDockWidgetArea, updateDockWidget);
    resizeDocks({ updateDockWidget }, { 200 }, Qt::Horizontal);

    //״̬��
    ElaStatusBar* statusBar = new ElaStatusBar(this);
    ElaText* statusText = new ElaText("��ʼ���ɹ���", this);
    statusText->setTextPixelSize(14);
    statusBar->addWidget(statusText);
    this->setStatusBar(statusBar);
}

void Appshow::initContent()
{
    _addfdc = new T_Addfdc(this);
    _tablefdc = new T_Tablefdc(this);

    _homePage = new T_Home(this);
#ifdef Q_OS_WIN
    _elaScreenPage = new T_ElaScreen(this);
#endif
    _iconPage = new T_Icon(this);
    _baseComponentsPage = new T_BaseComponents(this);
    _graphicsPage = new T_Graphics(this);
    _navigationPage = new T_Navigation(this);
    _popupPage = new T_Popup(this);
    _cardPage = new T_Card(this);
    _listViewPage = new T_ListView(this);
    _tableViewPage = new T_TableView(this);
    _treeViewPage = new T_TreeView(this);
    _settingPage = new T_Setting(this);
    _patientshow = new PatientShow(this);
    _patienttabview = new PatientTabView(this);
    QString testKey_1;
    QString testKey_2;
    addPageNode(QString::fromLocal8Bit("���˲�ѯ  "), _patientshow, ElaIconType::House);
    addPageNode(QString::fromLocal8Bit("��������  "), _patienttabview, ElaIconType::House);
    addPageNode(QString::fromLocal8Bit("������ݿ����� "), _addfdc, ElaIconType::House);
    addPageNode(QString::fromLocal8Bit("���ݿ�ҳ��  "), _tablefdc, ElaIconType::House);

    addPageNode("HOME", _homePage, ElaIconType::House);
#ifdef Q_OS_WIN
    addExpanderNode("ElaDxgi", _elaDxgiKey, ElaIconType::TvMusic);
    addPageNode("ElaScreen", _elaScreenPage, _elaDxgiKey, 3, ElaIconType::ObjectGroup);
#endif
    // navigation(elaScreenWidget->property("ElaPageKey").toString());
    addPageNode("ElaBaseComponents", _baseComponentsPage, ElaIconType::CabinetFiling);

    addExpanderNode("ElaView", _viewKey, ElaIconType::CameraViewfinder);
    addPageNode("ElaListView", _listViewPage, _viewKey, 9, ElaIconType::List);
    addPageNode("ElaTableView", _tableViewPage, _viewKey, ElaIconType::Table);
    addPageNode("ElaTreeView", _treeViewPage, _viewKey, ElaIconType::ListTree);

    addPageNode("ElaGraphics", _graphicsPage, 9, ElaIconType::Paintbrush);
    addPageNode("ElaCard", _cardPage, ElaIconType::Cards);
    addPageNode("ElaNavigation", _navigationPage, ElaIconType::LocationArrow);
    addPageNode("ElaPopup", _popupPage, ElaIconType::Envelope);
    addPageNode("ElaIcon", _iconPage, 99, ElaIconType::FontCase);
    addExpanderNode("TEST4", testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST5", testKey_1, testKey_2, ElaIconType::Acorn);
    addPageNode("Third Level", new QWidget(this), testKey_1, ElaIconType::Acorn);
    addExpanderNode("TEST6", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST7", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST8", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST9", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST10", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST11", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST12", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST13", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST14", testKey_1, testKey_2, ElaIconType::Acorn);
    addExpanderNode("TEST15", testKey_1, ElaIconType::Acorn);
    addExpanderNode("TEST16", testKey_1, ElaIconType::Acorn);
    addExpanderNode("TEST17", testKey_1, ElaIconType::Acorn);

    addFooterNode("About", nullptr, _aboutKey, 0, ElaIconType::User);
    _aboutPage = new T_About();

    _aboutPage->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (_aboutKey == nodeKey)
        {
            _aboutPage->setFixedSize(400, 400);
            _aboutPage->moveToCenter();
            _aboutPage->show();
        }
        });
    addFooterNode("Setting", _settingPage, _settingKey, 0, ElaIconType::GearComplex);

    connect(_addfdc, &T_Addfdc::addtablesqldata, _tablefdc, &T_Tablefdc::addtablesqldata);

    connect(_patientshow, &PatientShow::elaTabViewNavigation, this, [=](std::shared_ptr<PatientData> patientdata) {
        this->navigation(_patienttabview->property("ElaPageKey").toString());
        _patienttabview->AddPatientTabView(patientdata);
    });

    connect(this, &Appshow::userInfoCardClicked, this, [=]() { this->navigation(_homePage->property("ElaPageKey").toString()); });
#ifdef Q_OS_WIN
    connect(_homePage, &T_Home::elaScreenNavigation, this, [=]() { this->navigation(_elaScreenPage->property("ElaPageKey").toString()); });
#endif
    connect(_homePage, &T_Home::elaBaseComponentNavigation, this, [=]() { this->navigation(_baseComponentsPage->property("ElaPageKey").toString()); });
    connect(_homePage, &T_Home::elaSceneNavigation, this, [=]() { this->navigation(_graphicsPage->property("ElaPageKey").toString()); });
    connect(_homePage, &T_Home::elaIconNavigation, this, [=]() { this->navigation(_iconPage->property("ElaPageKey").toString()); });
    connect(_homePage, &T_Home::elaCardNavigation, this, [=]() { this->navigation(_cardPage->property("ElaPageKey").toString()); });
    qDebug() << ElaEventBus::getInstance()->getRegisteredEventsName();
}
