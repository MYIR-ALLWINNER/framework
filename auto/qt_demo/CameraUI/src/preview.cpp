#include "preview.h"
#include "ui_preview.h"
#include "settings.h"
#include "ui_settings.h"
#include "settings.h"
extern Settings* pStatic_settings;
extern int g_iCameraHeight,g_iCameraWidth;

Preview::Preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    ui->pictureLabel1->setStyleSheet(tr("border-image: url(:/frontCamera.png);"));
    ui->pictureLabel2->setStyleSheet(tr("border-image: url(:/rearCamera.png);"));
    connect(ui->front_set_Button,SIGNAL(clicked(bool)),this,SLOT(on_frontButton_clicked(bool)));
    connect(ui->rear_set_Button,SIGNAL(clicked(bool)),this,SLOT(on_rearButton_clicked(bool)));
    if(720==g_iCameraHeight)
    {
        qDebug()<<"720p-----------------";
        ui->label->setText(tr("摄像头制式：720p"));
    }else if(1080==g_iCameraHeight)
    {
        qDebug()<<"1080p------------------";
        ui->label->setText(tr("摄像头制式：1080p"));
    }else if(576==g_iCameraHeight)
    {
        ui->label->setText(tr("摄像头制式：PAL制"));
    }else if(480==g_iCameraHeight)
    {
        ui->label->setText(tr("摄像头制式：NTSC制"));
    }else{
        ui->label->setText(tr("摄像头制式：unknow"));
    }
}

Preview::~Preview()
{
    delete ui;
}
void Preview::on_rearButton_clicked(bool)
{
    rear_camera_setting=new Rear_Camera_Setting(this);
    rear_camera_setting->showNormal();
    pStatic_settings->setHidden(true);


}

void Preview::on_frontButton_clicked(bool)
{
    front_camera_setting=new Front_camera_setting(this);
    pStatic_settings->setHidden(true);
    front_camera_setting->showNormal();;
}


