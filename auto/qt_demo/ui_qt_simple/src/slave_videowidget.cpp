#include "slave_videowidget.h"
#include "ui_slave_videowidget.h"

slave_VideoWidget::slave_VideoWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::slave_VideoWidget)
{
    ui->setupUi(this);
}

slave_VideoWidget::~slave_VideoWidget()
{
    delete ui;
}

