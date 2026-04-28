/********************************************************************************
** Form generated from reading UI file 'Appshow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPSHOW_H
#define UI_APPSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <elawindow.h>

QT_BEGIN_NAMESPACE

class Ui_AppshowClass
{
public:

    void setupUi(ElaWindow *AppshowClass)
    {
        if (AppshowClass->objectName().isEmpty())
            AppshowClass->setObjectName("AppshowClass");
        AppshowClass->resize(600, 400);

        retranslateUi(AppshowClass);

        QMetaObject::connectSlotsByName(AppshowClass);
    } // setupUi

    void retranslateUi(ElaWindow *AppshowClass)
    {
        AppshowClass->setWindowTitle(QCoreApplication::translate("AppshowClass", "Appshow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppshowClass: public Ui_AppshowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPSHOW_H
