#include "adas.h"
#include "ui_adas.h"
#include "settings.h"
extern Settings* pStatic_settings;
ADAS::ADAS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADAS)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    front_ADAS_label=new myLabel(ui->widget_2);
    qDebug()<<ui->widget_2->size();
    front_ADAS_label->resize(ui->widget_2->size());
    front_ADAS_label->setStyleSheet(tr("background-image: url(:/frontCamera.png);"));
    front_ADAS_label->setParent(ui->widget_2);

    connect(front_ADAS_label,SIGNAL(clicked()),this,SLOT(on_pictureLabel2_clicked()));
    rear_ADAS_label=new myLabel(ui->widget);
    rear_ADAS_label->resize(ui->widget->size());
    rear_ADAS_label->setStyleSheet(tr("background-image: url(:/rearCamera.png);"));
    rear_ADAS_label->setParent(ui->widget);
    qDebug()<<ui->widget->size();
    connect(rear_ADAS_label,SIGNAL(clicked()),this,SLOT(on_pictureLabel1_clicked()));
}

ADAS::~ADAS()
{
    delete ui;
}
void ADAS::on_pictureLabel1_clicked()
{
    qDebug()<<"open adas ";
    rear_adas_settings=new rear_ADAS_setting(this);
    pStatic_settings->setHidden(true);
    rear_adas_settings->showNormal();
}
void ADAS::on_pictureLabel2_clicked()
{
    qDebug()<<"open front adas";
    front_adas_settings=new front_ADAS_setting(this);
    pStatic_settings->setHidden(true);
    front_adas_settings->showNormal();
}
