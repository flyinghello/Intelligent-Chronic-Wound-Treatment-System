#include "PatientInfoWidget.h"
#include <QGraphicsDropShadowEffect>
PatientInfoWidget::PatientInfoWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PatientInfoWidgetClass())
{
    // ���ô��ڱ���ɫ������������ʽ
    setStyleSheet("background-color: #f8f9fa; font-family: 'Arial', sans-serif; font-size: 14px; color: #333;");

    // ������ֱ���֣��������и���
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // ����ÿһ�еĲ��֣����Ҳ���
    QHBoxLayout* rowLayout1 = new QHBoxLayout();
    QHBoxLayout* rowLayout2 = new QHBoxLayout();
    QHBoxLayout* rowLayout3 = new QHBoxLayout();
    QHBoxLayout* rowLayout4 = new QHBoxLayout();
    QHBoxLayout* rowLayout5 = new QHBoxLayout();
    QHBoxLayout* rowLayout6 = new QHBoxLayout();
    QHBoxLayout* rowLayout7 = new QHBoxLayout();
    QHBoxLayout* rowLayout8 = new QHBoxLayout();
    QHBoxLayout* rowLayout9 = new QHBoxLayout();
    QHBoxLayout* rowLayout10 = new QHBoxLayout();
    QHBoxLayout* rowLayout11 = new QHBoxLayout();
    QHBoxLayout* rowLayout12 = new QHBoxLayout();
    QHBoxLayout* rowLayout13 = new QHBoxLayout();

    // ��������ǩ���Ҳ�����
    QLabel* pathologyLabel = new QLabel(QString::fromLocal8Bit("�����:"));
    QLabel* pathologyData = new QLabel(QString::fromLocal8Bit("12345"));
    rowLayout1->addWidget(pathologyLabel);
    rowLayout1->addWidget(pathologyData);

    QLabel* patientIDLabel = new QLabel(QString::fromLocal8Bit("���˱��:"));
    QLabel* patientIDData = new QLabel(QString::fromLocal8Bit("P001"));
    rowLayout2->addWidget(patientIDLabel);
    rowLayout2->addWidget(patientIDData);

    QLabel* reportStatusLabel = new QLabel(QString::fromLocal8Bit("����״̬:"));
    QLabel* reportStatusData = new QLabel(QString::fromLocal8Bit("����� "));
    rowLayout3->addWidget(reportStatusLabel);
    rowLayout3->addWidget(reportStatusData);

    QLabel* nameLabel = new QLabel(QString::fromLocal8Bit("����:"));
    QLabel* nameData = new QLabel(QString::fromLocal8Bit("����"));
    rowLayout4->addWidget(nameLabel);
    rowLayout4->addWidget(nameData);

    QLabel* genderLabel = new QLabel(QString::fromLocal8Bit("�Ա�:  "));
    QLabel* genderData = new QLabel(QString::fromLocal8Bit("��  "));
    rowLayout5->addWidget(genderLabel);
    rowLayout5->addWidget(genderData);

    QLabel* ageLabel = new QLabel(QString::fromLocal8Bit("����:"));
    QLabel* ageData = new QLabel(QString::fromLocal8Bit("45"));
    rowLayout6->addWidget(ageLabel);
    rowLayout6->addWidget(ageData);

    QLabel* departmentLabel = new QLabel(QString::fromLocal8Bit("�ͼ����:"));
    QLabel* departmentData = new QLabel(QString::fromLocal8Bit("�ڿ� "));
    rowLayout7->addWidget(departmentLabel);
    rowLayout7->addWidget(departmentData);

    QLabel* doctorLabel = new QLabel(QString::fromLocal8Bit("�ͼ�ҽ��:"));
    QLabel* doctorData = new QLabel(QString::fromLocal8Bit("��ҽ��"));
    rowLayout8->addWidget(doctorLabel);
    rowLayout8->addWidget(doctorData);

    QLabel* reportDateLabel = new QLabel(QString::fromLocal8Bit("��������:"));
    QLabel* reportDateData = new QLabel(QString::fromLocal8Bit("2024-12-17"));
    rowLayout9->addWidget(reportDateLabel);
    rowLayout9->addWidget(reportDateData);

    QTextEdit* macroscopicData = new QTextEdit();
    macroscopicData->setText(QString::fromLocal8Bit("�������ҷ���Ҷ�ɼ����߽�������ֱ��Լ3cm��"));
    macroscopicData->setReadOnly(true);
    macroscopicData->setFixedHeight(100);
    macroscopicData->setStyleSheet("QTextEdit { border: 2px solid #3498db; border-radius: 8px; padding: 10px; background-color: #ffffff; font-size: 14px; }");
    QLabel* macroscopicLabel = new QLabel(QString::fromLocal8Bit("��������:"));
    rowLayout10->addWidget(macroscopicLabel);
    rowLayout10->addWidget(macroscopicData);

    QTextEdit* diagnosisData = new QTextEdit();
    diagnosisData->setText(QString::fromLocal8Bit("�ҷΰ����ֲ���չ��"));
    diagnosisData->setReadOnly(true);
    diagnosisData->setFixedHeight(120);
    diagnosisData->setStyleSheet("QTextEdit { border: 2px solid #3498db; border-radius: 8px; padding: 10px; background-color: #ffffff; font-size: 14px; }");
    QLabel* diagnosisLabel = new QLabel(QString::fromLocal8Bit("�������:"));
    rowLayout11->addWidget(diagnosisLabel);
    rowLayout11->addWidget(diagnosisData);

    QLabel* reportDoctorLabel = new QLabel(QString::fromLocal8Bit("����ҽ��:"));
    QLabel* reportDoctorData = new QLabel(QString::fromLocal8Bit("��ҽ��"));
    rowLayout12->addWidget(reportDoctorLabel);
    rowLayout12->addWidget(reportDoctorData);

    QLabel* reviewDoctorLabel = new QLabel(QString::fromLocal8Bit("���ҽ��:"));
    QLabel* reviewDoctorData = new QLabel(QString::fromLocal8Bit("��ҽ��"));
    rowLayout13->addWidget(reviewDoctorLabel);
    rowLayout13->addWidget(reviewDoctorData);


    setStyleSheet("background-color: #f8f9fa; "
        "border: 2px solid #gray; "    // ���ñ߿�
        "border-radius: 10px; "          // ����Բ��
    );

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(3, 3);
    shadowEffect->setColor(Qt::gray);

    // ����һ���ⲿ���� QWidget ��Ӧ����Ӱ
    QWidget* outerWidget = new QWidget(this);
    outerWidget->setLayout(mainLayout);  // �����е� mainLayout ��ӵ� outerWidget

    // ������ӰЧ�����ⲿ����
    outerWidget->setGraphicsEffect(shadowEffect);

    // �� outerWidget ��Ϊ�����ؼ�
    setLayout(new QVBoxLayout());
    layout()->addWidget(outerWidget);  // ��� outerWidget Ϊ��ǰ�ؼ����ӿؼ�


    // ��Ӹ��в��ֵ���������
    mainLayout->addLayout(rowLayout1);
    mainLayout->addLayout(rowLayout2);
    mainLayout->addLayout(rowLayout3);
    mainLayout->addLayout(rowLayout4);
    mainLayout->addLayout(rowLayout5);
    mainLayout->addLayout(rowLayout6);
    mainLayout->addLayout(rowLayout7);
    mainLayout->addLayout(rowLayout8);
    mainLayout->addLayout(rowLayout9);
    mainLayout->addLayout(rowLayout10);
    mainLayout->addLayout(rowLayout11);
    mainLayout->addLayout(rowLayout12);
    mainLayout->addLayout(rowLayout13);

    // ���ô��ڲ���
    setLayout(mainLayout);

    // ���ô��ڱ���ʹ�С
    setWindowTitle("������ϸ��Ϣ");
    // setFixedSize(800, 700);
}

PatientInfoWidget::~PatientInfoWidget()
{
	delete ui;
}
