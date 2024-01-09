#include "timesetting.h"
#include "ui_timesetting.h"
#include <QDebug>
TimeSetting::TimeSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSetting)
{
    ui->setupUi(this);
    ui->dateEdit->setCalendarPopup(true);
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(setDatesTimes()));
    connect(ui->timeEdit,SIGNAL(timeChanged(QTime)),this,SLOT(setDatesTimes()));
    QDate nowDate=QDate::currentDate();
    ui->label->setText("当前日期："+nowDate.toString("yyyy-MM-dd"));
}

TimeSetting::~TimeSetting()
{
    delete ui;
}
void TimeSetting::setDatesTimes()
{
    QObject* sender = QObject::sender();
    if(sender==ui->dateEdit){
        qDebug()<<"date changed";
        QDate datesetting=ui->dateEdit->date();
        qDebug()<<datesetting;
    }
    else if(sender==ui->timeEdit){
        qDebug()<<"time changed";
        QTime timesetting=ui->timeEdit->time();
        qDebug()<<timesetting;
    }
    else{
        qDebug()<<"no signal sender";
    }

}


void TimeSetting::on_setButton_clicked()
{
    QString date=ui->dateEdit->text();
    QString time=ui->timeEdit->text();
    qDebug()<<date<<time;
    QString temp=QString(tr("当前时间为："))+date+"  "+time;
    ui->label->setText(temp);
    setDateAndTime();
}
void TimeSetting::setDateAndTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    dt.setDate(ui->dateEdit->date());
    dt.setTime(ui->timeEdit->time());
    time_t tt = (time_t)dt.toTime_t();
#if defined(Q_OS_LINUX)
    stime(&tt);
#endif
}
