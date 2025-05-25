#include "PC_software.h"

PC_software::PC_software(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PC_softwareClass())
{
    ui->setupUi(this);
}

PC_software::~PC_software()
{
    delete ui;
}