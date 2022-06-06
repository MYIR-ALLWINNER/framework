#include "rear_camera_setting.h"
#include "ui_rear_camera_setting.h"
#include "preview.h"
#include "ui_preview.h"
#include <QDesktopWidget>
#include "settings.h"
extern Settings* pStatic_settings;
Rear_Camera_Setting::Rear_Camera_Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rear_Camera_Setting)
{
    ui->setupUi(this);
    FormInCenter();

}
//窗体居中显示
void Rear_Camera_Setting::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
        this->resize(deskWidth*3/4,deskHeight*3/4);
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}
Rear_Camera_Setting::~Rear_Camera_Setting()
{
    delete ui;
}
void Rear_Camera_Setting::on_returnButton_clicked(bool)
{
    pStatic_settings->setHidden(false);
    this->close();
}
void Rear_Camera_Setting::on_upperButton_clicked(bool)
{
    qDebug()<<"rear camera upper";
}
void Rear_Camera_Setting::on_downButton_clicked(bool)
{
    qDebug()<<"rear camera down";
}
void Rear_Camera_Setting::on_sureButton_clicked(bool)
{
    qDebug()<<"sure to adjust camera";
    pStatic_settings->setHidden(false);
    this->close();
}
