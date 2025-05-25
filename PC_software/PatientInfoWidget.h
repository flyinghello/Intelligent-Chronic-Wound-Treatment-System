#pragma once

#include <QWidget>
#include "ui_PatientInfoWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDateEdit>
#include <QPushButton>
#include <QStyleFactory>
#include <QTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class PatientInfoWidgetClass; };
QT_END_NAMESPACE

class PatientInfoWidget : public QWidget
{
	Q_OBJECT

public:
	PatientInfoWidget(QWidget *parent = nullptr);
	~PatientInfoWidget();

private:
	Ui::PatientInfoWidgetClass *ui;
};
