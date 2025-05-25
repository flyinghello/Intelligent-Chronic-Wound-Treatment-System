/********************************************************************************
** Form generated from reading UI file 'VideoPlayerWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYERWIDGET_H
#define UI_VIDEOPLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayerWidgetClass
{
public:

    void setupUi(QWidget *VideoPlayerWidgetClass)
    {
        if (VideoPlayerWidgetClass->objectName().isEmpty())
            VideoPlayerWidgetClass->setObjectName("VideoPlayerWidgetClass");
        VideoPlayerWidgetClass->resize(600, 400);

        retranslateUi(VideoPlayerWidgetClass);

        QMetaObject::connectSlotsByName(VideoPlayerWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayerWidgetClass)
    {
        VideoPlayerWidgetClass->setWindowTitle(QCoreApplication::translate("VideoPlayerWidgetClass", "VideoPlayerWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayerWidgetClass: public Ui_VideoPlayerWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYERWIDGET_H
