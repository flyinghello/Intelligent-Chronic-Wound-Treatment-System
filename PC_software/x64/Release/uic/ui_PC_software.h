/********************************************************************************
** Form generated from reading UI file 'PC_software.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PC_SOFTWARE_H
#define UI_PC_SOFTWARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PC_softwareClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PC_softwareClass)
    {
        if (PC_softwareClass->objectName().isEmpty())
            PC_softwareClass->setObjectName("PC_softwareClass");
        PC_softwareClass->resize(600, 400);
        menuBar = new QMenuBar(PC_softwareClass);
        menuBar->setObjectName("menuBar");
        PC_softwareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PC_softwareClass);
        mainToolBar->setObjectName("mainToolBar");
        PC_softwareClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PC_softwareClass);
        centralWidget->setObjectName("centralWidget");
        PC_softwareClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PC_softwareClass);
        statusBar->setObjectName("statusBar");
        PC_softwareClass->setStatusBar(statusBar);

        retranslateUi(PC_softwareClass);

        QMetaObject::connectSlotsByName(PC_softwareClass);
    } // setupUi

    void retranslateUi(QMainWindow *PC_softwareClass)
    {
        PC_softwareClass->setWindowTitle(QCoreApplication::translate("PC_softwareClass", "PC_software", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PC_softwareClass: public Ui_PC_softwareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PC_SOFTWARE_H
