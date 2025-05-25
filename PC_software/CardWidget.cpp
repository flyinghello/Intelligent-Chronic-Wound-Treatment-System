#include "CardWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QDebug>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CardWidgetClass())
{
    // 主布局：水平布局
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    _mainLayout = mainLayout;
    // 文本区域的垂直布局
    QVBoxLayout* textLayout = new QVBoxLayout();
    _textLayout = textLayout;
    // 图片标签
    QLabel* imageLabel = new QLabel(this);
    _imageLabel = imageLabel;
    imageLabel->setFixedSize(100, 100);
    imageLabel->setStyleSheet(
        "QLabel {"
        "   border-radius: 10px;"  // 设置圆角半径
        "   background-color: white;"  // 背景颜色，保证圆角效果可见
        "}"
    );


    // 标题标签
    QLabel* titleLabel = new QLabel(QString::fromLocal8Bit("过往数据 "), this);
    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    titleLabel->setFont(titleFont);
    _maxtempLabel = titleLabel;

    // 温度标签
    QLabel* tempLabel = new QLabel(QString::fromLocal8Bit(""), this);
    _tempLabel = tempLabel;
    // 按钮
    QPushButton* button = new QPushButton(QString::fromLocal8Bit("查看 "), this);
    button->setBaseSize(70, 30);
    button->setMinimumSize(56,24);
    button->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border-radius: 5px;"
        "   font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3e8e41;"
        "}"
    );
    _button = button;

    connect(button, &QPushButton::clicked, this, [=]() {

        // 检查动画是否正在运行
        if (button->property("animating").toBool()) {
            return; // 如果动画正在运行，忽略点击事件
        }

        // 标记按钮正在执行动画
        button->setProperty("animating", true);

        // 动画设置：按钮从中间放大到1.2倍，再缩小到0.8倍，最后恢复原始大小
        QPropertyAnimation* animation = new QPropertyAnimation(button, "geometry");
        animation->setDuration(600); // 动画时长

        QRect startRect = button->geometry();
        QRect endRect = startRect;

        // 设置按钮放大到1.2倍
        endRect.setSize(startRect.size() * 1.2);
        QPoint center = startRect.center(); // 获取按钮中心点

        // 设置关键帧：从中心放大到1.2倍
        animation->setStartValue(startRect);
        animation->setEndValue(QRect(center - QPoint(endRect.width() / 2, endRect.height() / 2), endRect.size()));

        // 在0.33处放大到1.2倍
        animation->setKeyValueAt(0.33, QRect(center - QPoint(endRect.width() / 2, endRect.height() / 2), endRect.size()));

        // 在0.66处缩小到0.8倍
        QRect smallRect = startRect;
        smallRect.setSize(startRect.size() * 0.8);
        animation->setKeyValueAt(0.66, QRect(center - QPoint(smallRect.width() / 2, smallRect.height() / 2), smallRect.size()));

        // 最终恢复到原始大小
        animation->setEndValue(startRect);

        connect(animation, &QPropertyAnimation::finished, [=]() {
            button->setProperty("animating", false); // 动画完成，允许新的动画开始
            });

        // 使用回弹效果
        //animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

        qDebug() << "按钮点击动画触发！";
        });
    _button->setVisible(false);
    _button->setEnabled(false);


    // 卡片阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(3, 3);
    shadowEffect->setColor(Qt::gray);
    this->setGraphicsEffect(shadowEffect);

    // 文本布局添加控件
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(tempLabel);
    textLayout->addStretch(); // 推动文本靠上

    // 主布局添加控件
    mainLayout->addWidget(imageLabel);    // 添加图片
    mainLayout->addLayout(textLayout);    // 添加文本区域
    mainLayout->addStretch();             // 弹性空间
    mainLayout->addWidget(button, 0, Qt::AlignRight | Qt::AlignBottom); // 按钮靠右下角

    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // 设置卡片样式
    this->setStyleSheet(
        "background-color: white;"
        "border-radius: 10px;"
    );

    //"border: 1px solid lightgray;"
    // 设置卡片固定大小
    setFixedSize(250, 120);
}

void CardWidget::AddButton() 
{
    _button->setVisible(true);
    _button->setEnabled(true);
}

void CardWidget::AddImage(QString path)
{
    QPixmap pixmap(path); // 替换为实际图片路径
    _imageLabel->setPixmap(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    _imageLabel->setVisible(true);
    qDebug() << _imageLabel->isVisible();
    update();
}

void CardWidget::ChangetempLabel(double text,QString title)
{

    _tempLabel->setText(title + QString::number(text));
    if (text > maxt)
    {
        maxt = text;
        _maxtempLabel->setText(QString::fromLocal8Bit("峰值: " )+ QString::number(maxt));
    }
}


CardWidget::~CardWidget()
{
    delete ui;
}
