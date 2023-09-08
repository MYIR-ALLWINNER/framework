#include "reverseline.h"
#include "ui_reverseline.h"
#include "settings.h"
extern Settings* pStatic_settings;
ReverseLine::ReverseLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReverseLine)
{
    ui->setupUi(this);
    reverse_setting_label=new myLabel(ui->widget_2);
    reverse_setting_label->resize(ui->widget_2->size());
    reverse_setting_label->setStyleSheet(tr("border-image: url(:/reverseline2.png);"));
    reverse_setting_label->setParent(ui->widget_2);

    connect(reverse_setting_label,SIGNAL(clicked()),this,SLOT(on_pictureLabel2_clicked()));
    rearVision_setting_label=new myLabel(ui->widget);
    rearVision_setting_label->resize(ui->widget->size());
    rearVision_setting_label->setStyleSheet(tr("border-image: url(:/reverseline1.png);"));
    rearVision_setting_label->setParent(ui->widget);
    connect(rearVision_setting_label,SIGNAL(clicked()),this,SLOT(on_pictureLabel1_clicked()));

    reverseline_setting=new ReverseLine_Setting();
}

ReverseLine::~ReverseLine()
{
    delete ui;
}
void ReverseLine::on_pictureLabel2_clicked()
{
    qDebug()<<"open reverseLine setting desk";
    reverseline_setting->showNormal();
    pStatic_settings->setHidden(true);
}
void ReverseLine::on_pictureLabel1_clicked()
{
    qDebug()<<"open rear mirro";
}

