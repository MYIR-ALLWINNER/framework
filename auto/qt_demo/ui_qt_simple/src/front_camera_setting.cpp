#include "front_camera_setting.h"
#include "ui_front_camera_setting.h"
#include "preview.h"
#include "ui_preview.h"
#include <QDesktopWidget>
#include "settings.h"
extern Settings* pStatic_settings;
#if 0
extern int startA,startB,widthA,heightA;
#endif
static int interval=50;
Front_camera_setting::Front_camera_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Front_camera_setting)
{
    ui->setupUi(this);
    FormInCenter();
    connect(ui->returnButton,SIGNAL(clicked()),this,SLOT(on_returnButton_clicked()));
    connect(ui->upperButton,SIGNAL(clicked()),this,SLOT(on_upperButton_clicked()),Qt::UniqueConnection);
    connect(ui->downButton,SIGNAL(clicked()),this,SLOT(on_downButton_clicked()),Qt::UniqueConnection);
    connect(ui->sureButton,SIGNAL(clicked()),this,SLOT(on_sureButton_clicked()),Qt::UniqueConnection);
}
void Front_camera_setting::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth*3/4,deskHeight*3/4);
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}
Front_camera_setting::~Front_camera_setting()
{
    delete ui;
}
void Front_camera_setting::on_returnButton_clicked()
{
    this->close();
    pStatic_settings->setHidden(false);
}
void Front_camera_setting::on_upperButton_clicked()
{
    qDebug()<<"camer upper";
    connect(ui->downButton,SIGNAL(clicked()),this,SLOT(on_downButton_clicked()),Qt::UniqueConnection);
    ui->downButton->setEnabled(true);
    #if defined(Q_OS_LINUX)
        printf("camera upper view\n");
#if 0
        startA=0;widthA=1024;heightA=300;


        if(startB>0){
//            interval+=50;
            startB-=interval;
            printf("now startB is %d \n",startB);

        }else{
            disconnect(ui->upperButton,SIGNAL(clicked()),this,SLOT(on_upperButton_clicked()));
            ui->upperButton->setEnabled(false);
        }
#endif
    #endif
}
void Front_camera_setting::on_downButton_clicked()
{
    qDebug()<<"camera down";
    connect(ui->upperButton,SIGNAL(clicked()),this,SLOT(on_upperButton_clicked()),Qt::UniqueConnection);
    ui->upperButton->setEnabled(true);
    #if defined(Q_OS_LINUX)
        printf("camera down view\n");
#if 0
//        interval-=50;
//        printf("now interval is %d \n",interval);
        startA=0;widthA=1024;heightA=300;
        if( startB<300){
            startB+=interval;
            printf("now startB is %d \n",startB);
        }else{
            disconnect(ui->downButton,SIGNAL(clicked()),this,SLOT(on_downButton_clicked()));
            ui->downButton->setEnabled(false);
        }
#endif
    #endif
}
void Front_camera_setting::on_sureButton_clicked()
{
    qDebug()<<"sure camera adjust";
    this->close();
    pStatic_settings->setHidden(false);
}
