#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PC_software.h"
#include "ElaWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PC_softwareClass; };
QT_END_NAMESPACE

class PC_software : public QMainWindow
{
    Q_OBJECT

public:
    PC_software(QWidget *parent = nullptr);
    ~PC_software();
private:
    Ui::PC_softwareClass *ui;
};
