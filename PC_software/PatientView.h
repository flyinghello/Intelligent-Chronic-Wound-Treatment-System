#pragma once

#include "T_BasePage.h"
#include "ui_PatientView.h"
#include "global.h"
#include "ChartWithHover.h"
#include "CardWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PatientViewClass; };
QT_END_NAMESPACE
class ElaPromotionCard;
class ElaPromotionView;

class PatientView : public T_BasePage
{
	Q_OBJECT

public:
	PatientView(std::shared_ptr<PatientData>patientdata, QWidget *parent = nullptr);
	~PatientView();
	void setpatient(std::shared_ptr<PatientData> patientdata) 
	{ 
		this->_patientdata = patientdata; 
	};
	void addimage(QByteArray res,QString titile,QString pyresult)
	{
		ElaPromotionCard* exampleCard = new ElaPromotionCard(this->_promotionView);
		qDebug() << exampleCard->size();
		QPixmap pixmap;
		pixmap.loadFromData(res);
		exampleCard->setMinimumSize(100, 100);
		exampleCard->setCardPixmap(pixmap);
		exampleCard->setCardTitle(titile);
		/*exampleCard->setPromotionTitle("~~~~");*/
		exampleCard->setTitle(pyresult);
		exampleCard->setSubTitle("STYX HELIX");
		exampleCard->setVisible(true);
		QMetaObject::invokeMethod(this, [=]() {
			this->_promotionView->appendPromotionCard(exampleCard);
			}, Qt::QueuedConnection);
		_cardnum++;
	};

	void slot_change_patient_data(QJsonObject obj);
public slots:
	void slot_getPatientViewWoundImage_mod_finish(ReqId id, QByteArray res, ErrorCodes err);
private:
	CardWidget* _c1;
	CardWidget* _c2;
	Ui::PatientViewClass *ui;
	std::shared_ptr<PatientData> _patientdata;
	ElaPromotionView* _promotionView;
	QStringList nowcardlist;
	ElaPopularCard* _userview;
	int _cardnum = 0;
	ChartWithHover* _charwithhover;

};
