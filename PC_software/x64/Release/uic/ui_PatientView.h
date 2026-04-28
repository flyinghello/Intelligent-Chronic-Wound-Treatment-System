/********************************************************************************
** Form generated from reading UI file 'PatientView.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTVIEW_H
#define UI_PATIENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "T_Basepage.h"

QT_BEGIN_NAMESPACE

class Ui_PatientViewClass
{
public:

    void setupUi(T_BasePage *PatientViewClass)
    {
        if (PatientViewClass->objectName().isEmpty())
            PatientViewClass->setObjectName("PatientViewClass");
        PatientViewClass->resize(600, 400);

        retranslateUi(PatientViewClass);

        QMetaObject::connectSlotsByName(PatientViewClass);
    } // setupUi

    void retranslateUi(T_BasePage *PatientViewClass)
    {
        PatientViewClass->setWindowTitle(QCoreApplication::translate("PatientViewClass", "PatientView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientViewClass: public Ui_PatientViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTVIEW_H
