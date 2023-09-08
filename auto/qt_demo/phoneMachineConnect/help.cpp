#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    CustomWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setObjectName("help");
    this->setStyleSheet("QWidget#help {border-image:url(:/pmc_image/bg.png);}");
}

Help::~Help()
{
    delete ui;
}

void Help::on_btnBack_clicked()
{
    this->close();
}

void Help::on_pushButton_clicked()
{
    declaraction = new Declaraction(this);
    declaraction->show();
}
