#include "T_BasePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolButton.h"
#include "VideoPlayerWidget.h"
T_BasePage::T_BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent)
        {
            update();
        }
    });
}

T_BasePage::~T_BasePage()
{
}

void T_BasePage::addtopbutton(QWidget* abutton)
{
    this->_buttonLayout->addWidget(abutton);
    int count = this->_buttonLayout->count(); 
    // 遍历布局，找到最近添加的 Stretch 并删除它
    for (int i = count - 1; i >= 0; --i) {
        QLayoutItem* item = this->_buttonLayout->itemAt(i);
        if (item->spacerItem()) {  // 判断是否是一个 Stretch（即 Spacer）
            QLayoutItem* removedItem = this->_buttonLayout->takeAt(i);  // 移除 Stretch
            delete removedItem;  // 删除该布局项
            break;  // 找到并删除最近的 Stretch 后退出循环
        }
    }
    this->_buttonLayout->addStretch();
}

void T_BasePage::addimageview(ElaPromotionView* imageview)
{
    this->_imageviewLayout->addWidget(imageview);
    this->_imageviewLayout->update();


    ElaPromotionCard* exampleCard = new ElaPromotionCard(imageview);
    qDebug() << exampleCard->size();
    QPixmap pixmap(":/PC_software/image/yl.jpg");
    exampleCard->setMinimumSize(100, 100);
    exampleCard->setCardPixmap(pixmap);
    exampleCard->setCardTitle("");
    exampleCard->setPromotionTitle("SONG~");
    exampleCard->setTitle("STYX HELIX");
    exampleCard->setSubTitle("");
    exampleCard->setVisible(true);
    QMetaObject::invokeMethod(this, [=]() {
        imageview->appendPromotionCard(exampleCard);
        }, Qt::QueuedConnection);
    update();
}

void T_BasePage::adduserview(ElaPopularCard* userCard)
{
    this->_userLayout->addWidget(userCard);
    //this->_userLayout->addWidget(new VideoPlayerWidget(this));
    this->_userLayout->setContentsMargins(20, 0, 0, 0);
}

void T_BasePage::addintroduce(PatientInfoWidget *patientinfowidget)
{
    //QString imagepath = ":/PC_software/image/123.jpg";
    //ElaPromotionView* promotionView= new ElaPromotionView(this);
    //ElaPromotionCard* exampleCard = new ElaPromotionCard(promotionView);
    //QPixmap pixmap(imagepath);
    //exampleCard->setCardPixmap(pixmap);
    //exampleCard->setCardTitle("Beach");
    //exampleCard->setPromotionTitle("SONG~");
    //exampleCard->setTitle("STYX HELIX");
    //exampleCard->setSubTitle("Never close your eyes, Searching for a true fate");
    //exampleCard->setVisible(true);
    this->_introduceLayout->addWidget(patientinfowidget);
}

void T_BasePage::createCustomWidget(QString desText)
{
    // 顶部元素
    QWidget* customWidget = new QWidget(this);
    ElaText* subTitleText = new ElaText(this);
    subTitleText->setText("");
    subTitleText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    subTitleText->setTextPixelSize(11);

    //ElaToolButton* documentationButton = new ElaToolButton(this);
    //documentationButton->setFixedHeight(35);
    //documentationButton->setIsTransparent(false);
    //documentationButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ////_toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    //documentationButton->setText("Documentation");
    //documentationButton->setElaIcon(ElaIconType::FileDoc);
    //ElaMenu* documentationMenu = new ElaMenu(this);
    //documentationMenu->addElaIconAction(ElaIconType::CardsBlank, "CardsBlank");
    //documentationMenu->addElaIconAction(ElaIconType::EarthAmericas, "EarthAmericas");
    //documentationButton->setMenu(documentationMenu);

    //ElaToolButton* sourceButton = new ElaToolButton(this);
    //sourceButton->setFixedHeight(35);
    //sourceButton->setIsTransparent(false);
    //sourceButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //sourceButton->setText("Source");
    //sourceButton->setElaIcon(ElaIconType::NfcSymbol);
    //ElaMenu* sourceMenu = new ElaMenu(this);
    //sourceMenu->addElaIconAction(ElaIconType::FireBurner, "FireBurner");
    //sourceMenu->addElaIconAction(ElaIconType::Galaxy, "Galaxy~~~~");
    //sourceButton->setMenu(sourceMenu);

  /*  ElaToolButton* themeButton = new ElaToolButton(this);
    themeButton->setFixedSize(35, 35);
    themeButton->setIsTransparent(false);
    themeButton->setElaIcon(ElaIconType::MoonStars);
    connect(themeButton, &ElaToolButton::clicked, this, [=]() {
        eTheme->setThemeMode(eTheme->getThemeMode() == ElaThemeType::Light ? ElaThemeType::Dark : ElaThemeType::Light);
    });*/

    QHBoxLayout* imageviewlayout = new QHBoxLayout();
    this->_imageviewLayout = imageviewlayout;
   /* ElaPromotionView* _promotionView = new ElaPromotionView(this);
    ElaPromotionCard* exampleCard1 = new ElaPromotionCard(this);
    exampleCard1->setCardPixmap(QPixmap("E:/socketcpp/PC_software/PC_software/image/coffee_candy.jpg"));
    exampleCard1->setCardTitle("MiKu");
    exampleCard1->setPromotionTitle("SONG~");
    exampleCard1->setTitle("STYX HELIX");
    exampleCard1->setSubTitle("Never close your eyes, Searching for a true fate");
    _promotionView->appendPromotionCard(exampleCard1);
    imageviewlayout->addWidget(_promotionView);*/


    QHBoxLayout* buttonLayout = new QHBoxLayout();
    //buttonLayout->addWidget(documentationButton);
    //buttonLayout->addSpacing(5);
    //buttonLayout->addWidget(sourceButton);

    //buttonLayout->addWidget(themeButton);
    //buttonLayout->addStretch();
    //buttonLayout->addSpacing(15);
    this->_buttonLayout = buttonLayout;

    ElaText* descText = new ElaText(this);
    descText->setText(desText);
    descText->setTextPixelSize(13);

    ElaFlowLayout* userLayout = new ElaFlowLayout(10, 10, 10);
    this->_userLayout = userLayout;

    QVBoxLayout* userandimageLayout = new QVBoxLayout();
    userandimageLayout->addLayout(_userLayout);
    userandimageLayout->addLayout(_imageviewLayout);

    QHBoxLayout* userandimage_introduceLayout = new QHBoxLayout();
    userandimage_introduceLayout->addLayout(userandimageLayout,6);
    QHBoxLayout* introduceLayout = new QHBoxLayout();
    this->_introduceLayout = introduceLayout;
    userandimage_introduceLayout->addLayout(introduceLayout,4);

    QVBoxLayout* topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    //topLayout->addWidget(subTitleText);
    //topLayout->addSpacing(5);
    topLayout->addLayout(buttonLayout);
    //topLayout->addSpacing(5);
    /*topLayout->addLayout(userLayout);
    topLayout->addLayout(imageviewlayout);*/
    //topLayout->addLayout(userandimageLayout);
    topLayout->addLayout(userandimage_introduceLayout);

    //topLayout->addWidget(descText);
    setCustomWidget(customWidget);
}
