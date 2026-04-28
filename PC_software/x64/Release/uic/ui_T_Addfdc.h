/********************************************************************************
** Form generated from reading UI file 'T_Addfdc.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T_ADDFDC_H
#define UI_T_ADDFDC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "T_Basepage.h"

QT_BEGIN_NAMESPACE

class Ui_T_AddfdcClass
{
public:

    void setupUi(T_BasePage *T_AddfdcClass)
    {
        if (T_AddfdcClass->objectName().isEmpty())
            T_AddfdcClass->setObjectName("T_AddfdcClass");
        T_AddfdcClass->resize(600, 400);

        retranslateUi(T_AddfdcClass);

        QMetaObject::connectSlotsByName(T_AddfdcClass);
    } // setupUi

    void retranslateUi(T_BasePage *T_AddfdcClass)
    {
        T_AddfdcClass->setWindowTitle(QCoreApplication::translate("T_AddfdcClass", "T_Addfdc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class T_AddfdcClass: public Ui_T_AddfdcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T_ADDFDC_H
