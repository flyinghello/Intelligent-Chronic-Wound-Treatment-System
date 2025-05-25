/********************************************************************************
** Form generated from reading UI file 'CardWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDWIDGET_H
#define UI_CARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardWidgetClass
{
public:

    void setupUi(QWidget *CardWidgetClass)
    {
        if (CardWidgetClass->objectName().isEmpty())
            CardWidgetClass->setObjectName("CardWidgetClass");
        CardWidgetClass->resize(600, 400);

        retranslateUi(CardWidgetClass);

        QMetaObject::connectSlotsByName(CardWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *CardWidgetClass)
    {
        CardWidgetClass->setWindowTitle(QCoreApplication::translate("CardWidgetClass", "CardWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CardWidgetClass: public Ui_CardWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDWIDGET_H
