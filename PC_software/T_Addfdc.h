#pragma once
#include "T_BasePage.h"
#include "ui_T_Addfdc.h"
#include "Imagethread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class T_AddfdcClass; };
QT_END_NAMESPACE
#pragma execution_character_set("UTF-8")
class ElaPromotionCard;
class ElaPromotionView;
class T_Addfdc : public T_BasePage, public std::enable_shared_from_this<T_Addfdc>
{
	Q_OBJECT

public:
	T_Addfdc(QWidget *parent = nullptr);
	~T_Addfdc();
	template <typename T>
	T* createwidget(QString name, QWidget* parent)
	{
		T* widget = new T(parent);
		widget->setObjectName(name);
		return widget;
	}
public slots:
	void slot_addfdc_mod_finish(ReqId id, QString res, ErrorCodes err);
	void getimage64list(QStringList* imagebase64list);
	void addsqldata();
	void addimage();
private:
	Ui::T_AddfdcClass *ui;
	ElaPromotionCard* _promotionCard;
	ElaPromotionView* _promotionView;
	ElaPromotionView* _tv;
	QVBoxLayout* _centerLayout;
	QStringList nowcardlist;
	std::shared_ptr<Imagethread> imagethread;
signals:
	void addtablesqldata();
};
