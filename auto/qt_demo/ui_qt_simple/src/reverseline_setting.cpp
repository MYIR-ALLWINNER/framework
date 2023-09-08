#include "reverseline_setting.h"
#include "ui_reverseline_setting.h"
#include <QDesktopWidget>
#include <QDebug>
#include "settings.h"
#include "main_desktop.h"

extern Settings* pStatic_settings;
ReverseLine_Setting *pStatic_reverseLine=NULL;
extern main_desktop* pStaticMaindesktop;
extern int rotate_angle;
const int interval=5;
ReverseLine_Setting::ReverseLine_Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReverseLine_Setting)
{
    ui->setupUi(this);
    FormInCenter();
    setAttribute(Qt::WA_TranslucentBackground, true);
    reverLinewidget=new reverseLineWidget();
    qDebug()<<"reverLineWidget size:"<<ui->widget->size();
    reverLinewidget->resize(ui->widget->size());
    reverLinewidget->setParent(ui->widget);
    connect(this,SIGNAL(reverseLine_repaint()),pStaticMaindesktop,SLOT(on_reverseLine_repaint()));
    pStatic_reverseLine=this;
}

ReverseLine_Setting::~ReverseLine_Setting()
{
    delete ui;
}

void ReverseLine_Setting::on_pushButton_2_clicked()
{
    ui->pushButton_3->setEnabled(true);
    if(rotate_angle<30){
        qDebug()<<"now rotate_angle is :"<<rotate_angle;
        rotate_angle+=interval;
        reverLinewidget->update();
        emit reverseLine_repaint();
    }else{
        ui->pushButton_2->setEnabled(false);
    }

}

void ReverseLine_Setting::on_pushButton_3_clicked()
{
    ui->pushButton_2->setEnabled(true);
    if(rotate_angle>=5){
        qDebug()<<"now rotate_angle is :"<<rotate_angle;
        rotate_angle-=interval;
        reverLinewidget->update();
        emit reverseLine_repaint();
    }else{
        ui->pushButton_3->setEnabled(false);
    }

}

void ReverseLine_Setting::on_pushButton_4_clicked()
{
    //save need to save in the config ini
}

void ReverseLine_Setting::on_pushButton_clicked()
{
    this->close();
    pStatic_settings->setHidden(false);
}
//窗体居中显示
void ReverseLine_Setting::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
       this->resize(1024,550);
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}
