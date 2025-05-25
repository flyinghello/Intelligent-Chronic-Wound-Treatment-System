#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include "ui_CardWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class CardWidgetClass; };
QT_END_NAMESPACE

class CardWidget : public QWidget
{
public:
    CardWidget(QWidget* parent = nullptr);

    ~CardWidget();

    void AddButton();
    void AddImage(QString path);
    void ChangetempLabel(double text, QString title);

public slots:
    void onButtonClicked();
private:
    Ui::CardWidgetClass* ui;
    QHBoxLayout* _mainLayout;
    QVBoxLayout* _textLayout;
    QLabel* _imageLabel;
    QLabel* _tempLabel;
    QLabel* _maxtempLabel;
    QPushButton* _button;
    double maxv=-1;
    double maxt=-1;
};