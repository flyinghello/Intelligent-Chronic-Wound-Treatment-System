#pragma once

#include "T_BasePage.h"
#include "ui_PatientTabView.h"
#include "global.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PatientTabViewClass; };
QT_END_NAMESPACE
class ElaTabWidget;
class PatientTabView : public T_BasePage
{
	Q_OBJECT

public:
	PatientTabView(QWidget *parent = nullptr);
	~PatientTabView();

	void AddPatientTabView(std::shared_ptr<PatientData> patientdata);
private:
	Ui::PatientTabViewClass *ui;
	ElaTabWidget* _tabWidget{ nullptr };
};
