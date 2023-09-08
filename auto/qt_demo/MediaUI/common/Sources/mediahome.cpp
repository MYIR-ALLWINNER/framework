#include "ui_mediahome.h"
#include "common/Header/mediahome.h"
#include "musicplayer/Header/musicplayer.h"
#include "videoplayer/Header/videoplayer.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QDateTime>
#include <QPropertyAnimation>


MediaHome* pGlobalMediaHome = NULL;


MediaHome::MediaHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaHome)
{
    ui->setupUi(this);
	distype=0;
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);//the ~CameraSetting will be call when func close() run
    setAttribute(Qt::WA_TranslucentBackground, true);

    connect(ui->return_btn,SIGNAL(clicked()),this,SLOT(on_return_btn_clicked()));
    connect(ui->video_btn,SIGNAL(clicked()),this,SLOT(on_video_btn_clicked()));
    connect(ui->music_btn,SIGNAL(clicked()),this,SLOT(on_music_btn_clickeds()));

    pGlobalMediaHome = this;
}

MediaHome::~MediaHome()
{
    delete ui;
    pGlobalMediaHome = NULL;
}

void MediaHome::on_video_btn_clicked()
{
    qDebug()<<"on_video_btn_clicked1";
    VideoPlayer::Instance()->show();
    this->setHidden(true);
	distype=1;
}

void MediaHome::on_music_btn_clicked()
{
    qDebug()<<"on_music_btn_clicked1";
    MusicPlayer::Instance()->show();
    this->setHidden(true);
	distype=2;
}

void MediaHome::on_return_btn_clicked()
{
    qDebug()<<"on_return_2_clicked";
    //this->close();
    //system("fbinit");

    system("echo 0,0 > /sys/class/disp/disp/attr/fb2ui");
    system("echo Launcher, > /sys/inputFocus/write");
}
