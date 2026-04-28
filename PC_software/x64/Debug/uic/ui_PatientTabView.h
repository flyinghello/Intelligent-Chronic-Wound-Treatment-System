/********************************************************************************
** Form generated from reading UI file 'PatientTabView.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTTABVIEW_H
#define UI_PATIENTTABVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "T_Basepage.h"

QT_BEGIN_NAMESPACE

class Ui_PatientTabViewClass
{
public:

    void setupUi(T_BasePage *PatientTabViewClass)
    {
        if (PatientTabViewClass->objectName().isEmpty())
            PatientTabViewClass->setObjectName("PatientTabViewClass");
        PatientTabViewClass->resize(600, 400);

        retranslateUi(PatientTabViewClass);

        QMetaObject::connectSlotsByName(PatientTabViewClass);
    } // setupUi

    void retranslateUi(T_BasePage *PatientTabViewClass)
    {
        PatientTabViewClass->setWindowTitle(QCoreApplication::translate("PatientTabViewClass", "PatientTabView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientTabViewClass: public Ui_PatientTabViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTTABVIEW_H
