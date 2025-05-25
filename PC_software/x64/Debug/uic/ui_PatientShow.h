/********************************************************************************
** Form generated from reading UI file 'PatientShow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTSHOW_H
#define UI_PATIENTSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "T_Basepage.h"

QT_BEGIN_NAMESPACE

class Ui_PatientShowClass
{
public:

    void setupUi(T_BasePage *PatientShowClass)
    {
        if (PatientShowClass->objectName().isEmpty())
            PatientShowClass->setObjectName("PatientShowClass");
        PatientShowClass->resize(600, 400);

        retranslateUi(PatientShowClass);

        QMetaObject::connectSlotsByName(PatientShowClass);
    } // setupUi

    void retranslateUi(T_BasePage *PatientShowClass)
    {
        PatientShowClass->setWindowTitle(QCoreApplication::translate("PatientShowClass", "PatientShow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientShowClass: public Ui_PatientShowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTSHOW_H
