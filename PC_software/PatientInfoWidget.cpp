#include "PatientInfoWidget.h"
#include <QGraphicsDropShadowEffect>
PatientInfoWidget::PatientInfoWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PatientInfoWidgetClass())
{
    // 设置窗口背景色和整体字体样式
    setStyleSheet("background-color: #f8f9fa; font-family: 'Arial', sans-serif; font-size: 14px; color: #333;");

    // 创建垂直布局，用于排列各行
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // 创建每一行的布局，左右布局
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

    // 创建左侧标签和右侧数据
    QLabel* pathologyLabel = new QLabel(QString::fromLocal8Bit("病理号:"));
    QLabel* pathologyData = new QLabel(QString::fromLocal8Bit("12345"));
    rowLayout1->addWidget(pathologyLabel);
    rowLayout1->addWidget(pathologyData);

    QLabel* patientIDLabel = new QLabel(QString::fromLocal8Bit("病人编号:"));
    QLabel* patientIDData = new QLabel(QString::fromLocal8Bit("P001"));
    rowLayout2->addWidget(patientIDLabel);
    rowLayout2->addWidget(patientIDData);

    QLabel* reportStatusLabel = new QLabel(QString::fromLocal8Bit("报告状态:"));
    QLabel* reportStatusData = new QLabel(QString::fromLocal8Bit("已完成 "));
    rowLayout3->addWidget(reportStatusLabel);
    rowLayout3->addWidget(reportStatusData);

    QLabel* nameLabel = new QLabel(QString::fromLocal8Bit("姓名:"));
    QLabel* nameData = new QLabel(QString::fromLocal8Bit("张三"));
    rowLayout4->addWidget(nameLabel);
    rowLayout4->addWidget(nameData);

    QLabel* genderLabel = new QLabel(QString::fromLocal8Bit("性别:  "));
    QLabel* genderData = new QLabel(QString::fromLocal8Bit("男  "));
    rowLayout5->addWidget(genderLabel);
    rowLayout5->addWidget(genderData);

    QLabel* ageLabel = new QLabel(QString::fromLocal8Bit("年龄:"));
    QLabel* ageData = new QLabel(QString::fromLocal8Bit("45"));
    rowLayout6->addWidget(ageLabel);
    rowLayout6->addWidget(ageData);

    QLabel* departmentLabel = new QLabel(QString::fromLocal8Bit("送检科室:"));
    QLabel* departmentData = new QLabel(QString::fromLocal8Bit("内科 "));
    rowLayout7->addWidget(departmentLabel);
    rowLayout7->addWidget(departmentData);

    QLabel* doctorLabel = new QLabel(QString::fromLocal8Bit("送检医生:"));
    QLabel* doctorData = new QLabel(QString::fromLocal8Bit("李医生"));
    rowLayout8->addWidget(doctorLabel);
    rowLayout8->addWidget(doctorData);

    QLabel* reportDateLabel = new QLabel(QString::fromLocal8Bit("报告日期:"));
    QLabel* reportDateData = new QLabel(QString::fromLocal8Bit("2024-12-17"));
    rowLayout9->addWidget(reportDateLabel);
    rowLayout9->addWidget(reportDateData);

    QTextEdit* macroscopicData = new QTextEdit();
    macroscopicData->setText(QString::fromLocal8Bit("肿瘤在右肺上叶可见，边界清晰，直径约3cm。"));
    macroscopicData->setReadOnly(true);
    macroscopicData->setFixedHeight(100);
    macroscopicData->setStyleSheet("QTextEdit { border: 2px solid #3498db; border-radius: 8px; padding: 10px; background-color: #ffffff; font-size: 14px; }");
    QLabel* macroscopicLabel = new QLabel(QString::fromLocal8Bit("肉眼所见:"));
    rowLayout10->addWidget(macroscopicLabel);
    rowLayout10->addWidget(macroscopicData);

    QTextEdit* diagnosisData = new QTextEdit();
    diagnosisData->setText(QString::fromLocal8Bit("右肺癌，局部扩展。"));
    diagnosisData->setReadOnly(true);
    diagnosisData->setFixedHeight(120);
    diagnosisData->setStyleSheet("QTextEdit { border: 2px solid #3498db; border-radius: 8px; padding: 10px; background-color: #ffffff; font-size: 14px; }");
    QLabel* diagnosisLabel = new QLabel(QString::fromLocal8Bit("病理诊断:"));
    rowLayout11->addWidget(diagnosisLabel);
    rowLayout11->addWidget(diagnosisData);

    QLabel* reportDoctorLabel = new QLabel(QString::fromLocal8Bit("报告医生:"));
    QLabel* reportDoctorData = new QLabel(QString::fromLocal8Bit("王医生"));
    rowLayout12->addWidget(reportDoctorLabel);
    rowLayout12->addWidget(reportDoctorData);

    QLabel* reviewDoctorLabel = new QLabel(QString::fromLocal8Bit("审核医生:"));
    QLabel* reviewDoctorData = new QLabel(QString::fromLocal8Bit("赵医生"));
    rowLayout13->addWidget(reviewDoctorLabel);
    rowLayout13->addWidget(reviewDoctorData);


    setStyleSheet("background-color: #f8f9fa; "
        "border: 2px solid #gray; "    // 设置边框
        "border-radius: 10px; "          // 设置圆角
    );

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(3, 3);
    shadowEffect->setColor(Qt::gray);

    // 创建一个外部容器 QWidget 来应用阴影
    QWidget* outerWidget = new QWidget(this);
    outerWidget->setLayout(mainLayout);  // 将现有的 mainLayout 添加到 outerWidget

    // 设置阴影效果到外部容器
    outerWidget->setGraphicsEffect(shadowEffect);

    // 将 outerWidget 作为父级控件
    setLayout(new QVBoxLayout());
    layout()->addWidget(outerWidget);  // 添加 outerWidget 为当前控件的子控件


    // 添加各行布局到主布局中
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

    // 设置窗口布局
    setLayout(mainLayout);

    // 设置窗口标题和大小
    setWindowTitle("病人详细信息");
    // setFixedSize(800, 700);
}

PatientInfoWidget::~PatientInfoWidget()
{
	delete ui;
}
