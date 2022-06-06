#include "ui_mediahome.h"
#include "common/Header/mediahome.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QDateTime>
#include <QPropertyAnimation>


MediaHome::MediaHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaHome)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);//the ~CameraSetting will be call when func close() run
    //setAttribute(Qt::WA_TranslucentBackground, true);

//    connect(ui->return_btn,SIGNAL(clicked()),this,SLOT(on_return_btn_clicked()));
    connect(ui->media_btn,SIGNAL(clicked()),this,SLOT(on_media_btn_clicked()));
    connect(ui->camera_home_btn,SIGNAL(clicked()),this,SLOT(on_camera_home_btn_clicked()));//camera_home_btn
    system("echo Launcher, > /sys/inputFocus/write");

}

MediaHome::~MediaHome()
{
    delete ui;
}

void MediaHome::on_media_btn_clicked()
{
    qDebug()<<"menu:on_media_btn_clicked";

    system("echo 1,0 > /sys/class/disp/disp/attr/fb2ui");
    system("echo MediaUI, > /sys/inputFocus/write");
}

void MediaHome::on_camera_home_btn_clicked()
{
    qDebug()<<"menu:on_camera_home_btn_clicked";
    //MusicPlayer::Instance()->show();
    //this->setHidden(true);
    //system("echo 2,0 > /sys/class/disp/disp/attr/fb2ui");
    //system("echo CameraUI, > /sys/inputFocus/write");
}

