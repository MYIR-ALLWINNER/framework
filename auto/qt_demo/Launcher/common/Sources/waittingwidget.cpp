/*!
 * @file waittingwidget.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "common/Header/waittingwidget.h"
#include "ui_waittingwidget.h"

#include <QDebug>

WaittingWidget::WaittingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaittingWidget)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);//this widget will delete when close

    m_pMovie = new QMovie(":/images/playerIcons/loading.gif");
    if(m_pMovie->isValid()){
        qDebug()<<"movie is ok";
    }else{
        qDebug()<<"movie is not ok";
    }

}

WaittingWidget::~WaittingWidget()
{
    delete ui;
    delete m_pMovie;
}
void WaittingWidget::user_setGeometry(const QRect& rect)
{
    this->setGeometry(rect);
}
void WaittingWidget::startMovie()
{
    qDebug()<<"startMoview()";
    ui->waittingMovieLabel->setScaledContents(true);
    ui->waittingMovieLabel->setMovie(m_pMovie);
    m_pMovie->start();
}
void WaittingWidget::onStopMovie()
{
    qDebug()<<"waittingwidget get stop signal";
    this->close();
}
