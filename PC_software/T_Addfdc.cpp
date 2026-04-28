#include "T_Addfdc.h"
#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaMessageButton.h"
#include "ElaMultiSelectComboBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaProgressBar.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaSlider.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"
#include "ElaMessageBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include  <QLineEdit>
#include "ElaToolButton.h"
#include<QFileDialog>
#include <QStringList>
#include <functional>
#include <iostream>
#include <QLineEdit>
#include <memory>
#include <mutex>
#include <QBuffer>
#include "HttpMgr.h"
#include "UserMgr.h"
#include <QThreadPool>
T_Addfdc::T_Addfdc(QWidget *parent)
	: T_BasePage(parent)
	, ui(new Ui::T_AddfdcClass())
{
	setWindowTitle(QString::fromLocal8Bit("添加数据库数据 "));
	createCustomWidget(QString::fromLocal8Bit(" "));
	ElaToolButton* confirmButton = new ElaToolButton(this);
	confirmButton->setFixedHeight(35);
	confirmButton->setIsTransparent(false);
	confirmButton->setText(QString::fromLocal8Bit(" 确认添加为数据库数据 "));
	this->addtopbutton(confirmButton);

	ElaToolButton* addimageButton = new ElaToolButton(this);
	addimageButton->setFixedHeight(35);
	addimageButton->setIsTransparent(false);
	addimageButton->setText(QString::fromLocal8Bit(" 添加图片 "));
	this->addtopbutton(addimageButton);

	connect(addimageButton, &QPushButton::clicked, this, &T_Addfdc::addimage);
	connect(confirmButton, &QPushButton::clicked, this, &T_Addfdc::addsqldata);

	connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_addfdc_mod_finish, this, &T_Addfdc::slot_addfdc_mod_finish);
	ElaScrollPageArea* LoacteArea = new ElaScrollPageArea(this);
	QHBoxLayout* LoacteLayout = new QHBoxLayout(LoacteArea);
	ElaText* LoacteText = new ElaText(QString::fromLocal8Bit("房源位置: "), this);
	ElaText* dongText = new ElaText(QString::fromLocal8Bit("栋: "), this);
	ElaText* unitText = new ElaText(QString::fromLocal8Bit("单元: "), this);
	ElaText* housenumText = new ElaText(QString::fromLocal8Bit("房号: "), this);
	ElaText* school_districtText = new ElaText(QString::fromLocal8Bit("学区: "), this);
	ElaText* typeText = new ElaText(QString::fromLocal8Bit("类型"), this);
	ElaText* salesmanText = new ElaText(QString::fromLocal8Bit("销售员: "), this);
	QLineEdit* Loacteedit = createwidget<QLineEdit>(QString("Loacteedit"), this);
	QLineEdit* dongedit = createwidget<QLineEdit>(QString("dongedit"), this);
	QLineEdit* unitedit = createwidget<QLineEdit>(QString("unitedit"), this);
	QLineEdit* housenumedit = createwidget<QLineEdit>(QString("housenumedit"), this);
	QLineEdit* school_districedit = createwidget<QLineEdit>(QString("school_districedit"), this);


	ElaComboBox* typeComboBox = createwidget<ElaComboBox>(QString("typeComboBox"), this);
	QStringList typecomboList{
	QString::fromLocal8Bit("一手房 "),
	QString::fromLocal8Bit("二手房 "),
	QString::fromLocal8Bit("急售房 "),
	QString::fromLocal8Bit("商铺 "),
	QString::fromLocal8Bit("租房 ") };
	typeComboBox->addItems(typecomboList);

	ElaComboBox* salesmanBox = createwidget<ElaComboBox>(QString("salesmanBox"), this);
	QStringList salesmancomboList{
	QString::fromLocal8Bit("1 "),
	QString::fromLocal8Bit("2 "),
	QString::fromLocal8Bit("3 "),
	QString::fromLocal8Bit("4 "),
	QString::fromLocal8Bit("5 ") };
	salesmanBox->addItems(salesmancomboList);

	LoacteText->setTextPixelSize(15);
	dongText->setTextPixelSize(15);
	unitText ->setTextPixelSize(15);
	housenumText ->setTextPixelSize(15);
	school_districtText->setTextPixelSize(15);
	typeText->setTextPixelSize(15);
	salesmanText->setTextPixelSize(15);

	LoacteLayout->addWidget(LoacteText);
	LoacteLayout->addWidget(Loacteedit);
	LoacteLayout->addWidget(dongText);
	LoacteLayout->addWidget(dongedit);
	LoacteLayout->addWidget(unitText);
	LoacteLayout->addWidget(unitedit);
	LoacteLayout->addWidget(housenumText);
	LoacteLayout->addWidget(housenumedit);
	LoacteLayout->addWidget(school_districtText);
	LoacteLayout->addWidget(school_districedit);
	LoacteLayout->addWidget(typeText);
	LoacteLayout->addWidget(typeComboBox);
	LoacteLayout->addWidget(salesmanText);
	LoacteLayout->addWidget(salesmanBox);
	LoacteLayout->addStretch();

	ElaScrollPageArea* ConditonArea = new ElaScrollPageArea(this);
	QHBoxLayout* ConditonLayout = new QHBoxLayout(ConditonArea);
	ElaText* valueText = new ElaText(QString::fromLocal8Bit("价位(W): "), this);
	ElaText* areaText = new ElaText(QString::fromLocal8Bit("面积(m^2): "), this);
	ElaText* house_typeText = new ElaText(QString::fromLocal8Bit("户型: "), this);
	ElaText* vr_linkText = new ElaText(QString::fromLocal8Bit("如视vr链接: "), this);
	ElaText* sph_linkText = new ElaText(QString::fromLocal8Bit("视频号链接: "), this);

	QLineEdit* valueedit = createwidget<QLineEdit>(QString("valueedit"), this);
	QLineEdit* areaedit = createwidget<QLineEdit>(QString("areaedit"), this);
	QLineEdit* house_typeedit = createwidget<QLineEdit>(QString("house_typeedit"), this);
	QLineEdit* vr_linkedit = createwidget<QLineEdit>(QString("vr_linkedit"), this);
	QLineEdit* sph_linkedit = createwidget<QLineEdit>(QString("sph_linkedit"), this);

	valueText->setTextPixelSize(15);
	areaText->setTextPixelSize(15);
	house_typeText->setTextPixelSize(15);
	vr_linkText->setTextPixelSize(15);
	sph_linkText->setTextPixelSize(15);
	ConditonLayout->addWidget(valueText);
	ConditonLayout->addWidget(valueedit);
	ConditonLayout->addWidget(areaText);
	ConditonLayout->addWidget(areaedit);
	ConditonLayout->addWidget(house_typeText);
	ConditonLayout->addWidget(house_typeedit);
	ConditonLayout->addWidget(vr_linkText);
	ConditonLayout->addWidget(vr_linkedit);
	ConditonLayout->addWidget(sph_linkText);
	ConditonLayout->addWidget(sph_linkedit);
	ConditonLayout->addWidget(salesmanText);
	ConditonLayout->addWidget(salesmanBox);

	ElaScrollPageArea* brief_introductionArea = new ElaScrollPageArea(this);
	brief_introductionArea->setFixedHeight(180);
	QHBoxLayout* brief_introductionLayout = new QHBoxLayout(brief_introductionArea);
	ElaText* brief_introductionText = new ElaText(QString::fromLocal8Bit("简介: "), this);
	brief_introductionText->setFixedWidth(100);
	ElaPlainTextEdit* brief_introductionedit = createwidget<ElaPlainTextEdit>(QString("brief_introductionedit"), this);
	brief_introductionedit->setFixedHeight(150);

	//// supporting_facility
	ElaText* supporting_facilityText = new ElaText(QString::fromLocal8Bit("基础设施情况:  "), this);
	supporting_facilityText->setFixedWidth(100);
	ElaPlainTextEdit* supporting_facilityedit = createwidget<ElaPlainTextEdit>(QString("supporting_facilityedit"), this);
	supporting_facilityedit->setFixedHeight(150);

	brief_introductionLayout->addWidget(brief_introductionText);
	brief_introductionLayout->addWidget(brief_introductionedit);;
	brief_introductionLayout->addWidget(supporting_facilityText);
	brief_introductionLayout->addWidget(supporting_facilityedit);

	////life_convenience
	ElaText* life_convenienceText = new ElaText(QString::fromLocal8Bit("生活便利情况:  "), this);
	life_convenienceText->setFixedWidth(100);
	ElaPlainTextEdit* life_convenienceedit = createwidget<ElaPlainTextEdit>(QString("life_convenienceedit"), this);
	life_convenienceedit->setFixedHeight(150);
	brief_introductionLayout->addWidget(life_convenienceText);
	brief_introductionLayout ->addWidget(life_convenienceedit);


	_promotionView = new ElaPromotionView(this);


	QWidget* centralWidget = new QWidget(this);
	centralWidget->setWindowTitle(QString::fromLocal8Bit("添加数据库数据 "));
	QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
	this->_centerLayout = centerLayout;
	centerLayout->addWidget(LoacteArea);
	centerLayout->addWidget(ConditonArea);
	centerLayout->addWidget(brief_introductionArea);
	centerLayout->addSpacing(20);
	centerLayout->addStretch();
	centerLayout->setContentsMargins(0, 0, 0, 0);
	addCentralWidget(centralWidget, true, true, 0);
	//// 初始化提示
	ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", QString::fromLocal8Bit("初始化成功!"), 2000);
	qDebug() << "初始化成功";
}

T_Addfdc::~T_Addfdc()
{
	delete ui;
}

void T_Addfdc::addimage()
{
	QStringList imagePaths = QFileDialog::getOpenFileNames(this, "select image", QString(), "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)");
	this->nowcardlist = imagePaths;
	if (!imagePaths.isEmpty())
	{
		for (QString imagepath : imagePaths)
		{
			qDebug() << imagepath;
			ElaPromotionCard* exampleCard = new ElaPromotionCard(this->_promotionView);
			QPixmap pixmap(imagepath);
			if (pixmap.isNull())
			{
				qDebug() << "Failed to load image:" << imagepath;
				continue; // 跳过这张图
			}
			exampleCard->setCardPixmap(pixmap);
			exampleCard->setCardTitle("Beach");
			exampleCard->setPromotionTitle("SONG~");
			exampleCard->setTitle("STYX HELIX");
			exampleCard->setSubTitle("Never close your eyes, Searching for a true fate");
			exampleCard->setVisible(true);
			qDebug() << exampleCard->isVisible();
			QMetaObject::invokeMethod(this, [=]() {
				this->_promotionView->appendPromotionCard(exampleCard);
				}, Qt::QueuedConnection);
			this->_promotionView->update();
			this->_promotionView->repaint();
			this->layout()->update();
			_centerLayout->update();
		}
	}
	if (this->nowcardlist.size() > 0)
	{
		std::once_flag s_flag;
		std::call_once(s_flag, [&]() {
			//第一次调用就addview进去
			addimageview(_promotionView);
			});
	}
}

void T_Addfdc::slot_addfdc_mod_finish(ReqId id, QString res, ErrorCodes err)
{
	if (err != ErrorCodes::SUCCESS)
	{
		qDebug() << "err";
		ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", QString::fromLocal8Bit("网络错误导致添加数据库失败!"), 2000);
		return;
	}
	switch (id)
	{
	case ReqId::ReqTEST:
		break;
	case ReqId::AddSqlData:
	{
		qDebug() << "AddSql success";
		QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
		qDebug() << json;
		ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", QString::fromLocal8Bit("添加数据库数据成功!"), 2000);
	}
		break;
	default:
		break;
	}
}

void T_Addfdc::addsqldata()
{
	qDebug() << QString::fromLocal8Bit("确认添加数据 ");
	imagethread = std::make_shared<Imagethread>(this->nowcardlist, this);
	connect(imagethread.get(), &Imagethread::SigFinishImageSwitchBase64,this, &T_Addfdc::getimage64list, Qt::QueuedConnection);
	QThreadPool::globalInstance()->start(imagethread.get());
}

void T_Addfdc::getimage64list(QStringList* imagebase64list)
{
	//imagethread.reset();
	QJsonObject sql_add_json;
	QList<QLineEdit*> childrenedit = this->findChildren<QLineEdit*>();
	for (QLineEdit* edit : childrenedit)
	{
		sql_add_json[edit->objectName()] = edit->text();
		//qDebug() << edit->text() << edit->objectName();
	}

	QList< ElaComboBox*> childElaComboBox = this->findChildren<ElaComboBox*>();
	for (ElaComboBox* box : childElaComboBox)
	{
		sql_add_json[box->objectName()] = box->currentText();
		//qDebug() << box->currentText() << box->objectName();
	}

	QList< ElaPlainTextEdit*> childElaPlainTextEdit = this->findChildren<ElaPlainTextEdit*>();
	for (ElaPlainTextEdit* textedit : childElaPlainTextEdit)
	{
		sql_add_json[textedit->objectName()] = textedit->toPlainText();
		//qDebug() << textedit->toPlainText() << textedit->objectName();
	}
	qDebug() << "list size" << this->nowcardlist.size();
	if (imagebase64list == nullptr)
	{
		qDebug() << "image64baselist=nullptr";
		ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", QString::fromLocal8Bit("图片为空导致添加数据库失败!"), 2000);
		return;
	}
	else
	{
		QString head = "image";
		int index = 0;
		for (QString str : (*imagebase64list))
		{
			index++;
			QString nowhead = head + QString::number(index);
			sql_add_json[nowhead] = str;
		}
	}
	HttpMgr::GetInstance()->PostHttpReq(QUrl("http://127.0.0.1:4000/test"), sql_add_json, ReqId::AddSqlData, Modules::ReqAddfdc);
	emit addtablesqldata();
}