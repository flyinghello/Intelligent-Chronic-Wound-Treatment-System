#include "CardWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QDebug>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// ��ָ���֧��VS����
#endif

CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CardWidgetClass())
{
    // �����֣�ˮƽ����
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    _mainLayout = mainLayout;
    // �ı�����Ĵ�ֱ����
    QVBoxLayout* textLayout = new QVBoxLayout();
    _textLayout = textLayout;
    // ͼƬ��ǩ
    QLabel* imageLabel = new QLabel(this);
    _imageLabel = imageLabel;
    imageLabel->setFixedSize(100, 100);
    imageLabel->setStyleSheet(
        "QLabel {"
        "   border-radius: 10px;"  // ����Բ�ǰ뾶
        "   background-color: white;"  // ������ɫ����֤Բ��Ч���ɼ�
        "}"
    );


    // �����ǩ
    QLabel* titleLabel = new QLabel(QString::fromLocal8Bit("�������� "), this);
    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    titleLabel->setFont(titleFont);
    _maxtempLabel = titleLabel;

    // �¶ȱ�ǩ
    QLabel* tempLabel = new QLabel(QString::fromLocal8Bit(""), this);
    _tempLabel = tempLabel;
    // ��ť
    QPushButton* button = new QPushButton(QString::fromLocal8Bit("�鿴 "), this);
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

        // ��鶯���Ƿ���������
        if (button->property("animating").toBool()) {
            return; // ��������������У����Ե���¼�
        }

        // ��ǰ�ť����ִ�ж���
        button->setProperty("animating", true);

        // �������ã���ť���м�Ŵ�1.2��������С��0.8�������ָ�ԭʼ��С
        QPropertyAnimation* animation = new QPropertyAnimation(button, "geometry");
        animation->setDuration(600); // ����ʱ��

        QRect startRect = button->geometry();
        QRect endRect = startRect;

        // ���ð�ť�Ŵ�1.2��
        endRect.setSize(startRect.size() * 1.2);
        QPoint center = startRect.center(); // ��ȡ��ť���ĵ�

        // ���ùؼ�֡�������ķŴ�1.2��
        animation->setStartValue(startRect);
        animation->setEndValue(QRect(center - QPoint(endRect.width() / 2, endRect.height() / 2), endRect.size()));

        // ��0.33���Ŵ�1.2��
        animation->setKeyValueAt(0.33, QRect(center - QPoint(endRect.width() / 2, endRect.height() / 2), endRect.size()));

        // ��0.66����С��0.8��
        QRect smallRect = startRect;
        smallRect.setSize(startRect.size() * 0.8);
        animation->setKeyValueAt(0.66, QRect(center - QPoint(smallRect.width() / 2, smallRect.height() / 2), smallRect.size()));

        // ���ջָ���ԭʼ��С
        animation->setEndValue(startRect);

        connect(animation, &QPropertyAnimation::finished, [=]() {
            button->setProperty("animating", false); // ������ɣ������µĶ�����ʼ
            });

        // ʹ�ûص�Ч��
        //animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

        qDebug() << "��ť�������������";
        });
    _button->setVisible(false);
    _button->setEnabled(false);


    // ��Ƭ��ӰЧ��
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(3, 3);
    shadowEffect->setColor(Qt::gray);
    this->setGraphicsEffect(shadowEffect);

    // �ı�������ӿؼ�
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(tempLabel);
    textLayout->addStretch(); // �ƶ��ı�����

    // ��������ӿؼ�
    mainLayout->addWidget(imageLabel);    // ���ͼƬ
    mainLayout->addLayout(textLayout);    // ����ı�����
    mainLayout->addStretch();             // ���Կռ�
    mainLayout->addWidget(button, 0, Qt::AlignRight | Qt::AlignBottom); // ��ť�����½�

    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ���ÿ�Ƭ��ʽ
    this->setStyleSheet(
        "background-color: white;"
        "border-radius: 10px;"
    );

    //"border: 1px solid lightgray;"
    // ���ÿ�Ƭ�̶���С
    setFixedSize(250, 120);
}

void CardWidget::AddButton() 
{
    _button->setVisible(true);
    _button->setEnabled(true);
}

void CardWidget::AddImage(QString path)
{
    QPixmap pixmap(path); // �滻Ϊʵ��ͼƬ·��
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
        _maxtempLabel->setText(QString::fromLocal8Bit("��ֵ: " )+ QString::number(maxt));
    }
}


CardWidget::~CardWidget()
{
    delete ui;
}
