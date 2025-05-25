/********************************************************************************
** Form generated from reading UI file 'T_Tablefdc.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T_TABLEFDC_H
#define UI_T_TABLEFDC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "T_Basepage.h"

QT_BEGIN_NAMESPACE

class Ui_T_TablefdcClass
{
public:

    void setupUi(T_BasePage *T_TablefdcClass)
    {
        if (T_TablefdcClass->objectName().isEmpty())
            T_TablefdcClass->setObjectName("T_TablefdcClass");
        T_TablefdcClass->resize(600, 400);

        retranslateUi(T_TablefdcClass);

        QMetaObject::connectSlotsByName(T_TablefdcClass);
    } // setupUi

    void retranslateUi(T_BasePage *T_TablefdcClass)
    {
        T_TablefdcClass->setWindowTitle(QCoreApplication::translate("T_TablefdcClass", "T_Tablefdc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class T_TablefdcClass: public Ui_T_TablefdcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T_TABLEFDC_H
