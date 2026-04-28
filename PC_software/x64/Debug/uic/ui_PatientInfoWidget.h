/********************************************************************************
** Form generated from reading UI file 'PatientInfoWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTINFOWIDGET_H
#define UI_PATIENTINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientInfoWidgetClass
{
public:

    void setupUi(QWidget *PatientInfoWidgetClass)
    {
        if (PatientInfoWidgetClass->objectName().isEmpty())
            PatientInfoWidgetClass->setObjectName("PatientInfoWidgetClass");
        PatientInfoWidgetClass->resize(600, 400);

        retranslateUi(PatientInfoWidgetClass);

        QMetaObject::connectSlotsByName(PatientInfoWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *PatientInfoWidgetClass)
    {
        PatientInfoWidgetClass->setWindowTitle(QCoreApplication::translate("PatientInfoWidgetClass", "PatientInfoWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientInfoWidgetClass: public Ui_PatientInfoWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTINFOWIDGET_H
