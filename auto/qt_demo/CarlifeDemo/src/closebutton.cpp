/*!
 * @file closebutton.cpp
 * Copyright (c) 2018
 * @brief des this is a button which software can make connection break
 *
 * @date 2018
 * @author lee
 */
#include "closebutton.h"
#include "ui_closebutton.h"
#include <QDesktopWidget>
#include <QDebug>
closeButton::closeButton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::closeButton)
{
    ui->setupUi(this);
	adaptPosition();
}

closeButton::~closeButton()
{
    delete ui;
}

void closeButton::adaptPosition()
{
    qDebug()<<"adaptPostion";
    QDesktopWidget w;
    int deskWidth = w.width();
    QPoint movePoint(deskWidth - ui->pushButton->width(), 0);
    qDebug()<<"move to "<< movePoint;
    this->move(movePoint);
}

void closeButton::on_pushButton_clicked()
{
    qDebug()<<"tell carlifeWindow to break connect";
    emit forceBreak();
}
