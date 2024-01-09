/*!
 * @file carlifewindow.cpp
 * Copyright (c) 2018
 * @brief this is a demo for carlife in smart car
 * detailed  This demo program mainly provides visual mobile
 *           interconnect operations
 *
 * @date 2018
 * @author lee
 */
#include "carlifewindow.h"
#include "ui_carlifewindow.h"
#include "frmmessagebox.h"
#include "CCarlifeService.h"
#include <QDebug>
#include <QMovie>



class WorkerThread;
/*!
 * @construct function
 */
CarlifeWindow::CarlifeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarlifeWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    m_platform = 0;
    m_connectWay = 0;
    m_carlifeStatus = 0;
    clsButton = new closeButton(this);
    m_scene = new Scene(this);
#if 1
    connect(m_scene,SIGNAL(reverseControl_Down(int,int)),this,SLOT(on_reverseControl_Down(int, int)));
    connect(m_scene,SIGNAL(reverseControl_Up(int,int)),this,SLOT(on_reverseControl_Up(int, int)));
    connect(m_scene,SIGNAL(reverseControl_Move(int,int)),this,SLOT(on_reverseControl_Move(int, int)));
#endif
}

CarlifeWindow::~CarlifeWindow()
{
    delete ui;
    delete workerthread;
    delete pMovie;
}

void CarlifeWindow::on_closeButton_clicked()
{
    qDebug()<<"close button is down";
    frmMessageBox* msg = new frmMessageBox();
    msg->SetMessage("确认退出Demo程序？",1);
    if(1 == msg->exec()){
        qDebug()<<"sure to close";
        this->close();
        system("fbinit");
    }else{
        return;
    }
}

void CarlifeWindow::on_AndroidButton_clicked()
{
    qDebug()<<"android button is down";
    qDebug()<<"this positon is "<<ui->AndroidButton->mapTo(this,QPoint(0,0));
    switch (m_platform) {
    case 0:
        ui->AndroidButton->setStyleSheet("\
                                         image:url(:/image/icon/android.png);\
                                         border:0px solid red;\
                                         ");
        m_platform = 3;
        return;
    case 1:
    case 3:
        ui->AndroidButton->setStyleSheet("\
                                         image:url(:/image/icon/android.png);\
                                         border:2px solid red;\
                                         ");
        ui->IosButton->setStyleSheet("\
                                         image:url(:/image/icon/mac.png);\
                                         border:0px solid red;\
                                         ");
        break;
    default:
        break;
    }
    m_platform = 0;
}

void CarlifeWindow::on_IosButton_clicked()
{
    qDebug()<<"ios button is down";
    switch (m_platform) {
    case 1:
        ui->IosButton->setStyleSheet("\
                                         image:url(:/image/icon/mac.png);\
                                         border:0px solid red;\
                                         ");
        m_platform = 3;
        return;
    case 0:
    case 3:
        ui->AndroidButton->setStyleSheet("\
                                         image:url(:/image/icon/android.png);\
                                         border:0px solid red;\
                                         ");
        ui->IosButton->setStyleSheet("\
                                         image:url(:/image/icon/mac.png);\
                                         border:2px solid red;\
                                         ");
        break;
    default:
        break;
    }
    m_platform = 1;
}

void CarlifeWindow::on_UsbButton_clicked()
{
    qDebug()<<"usb button is down";
    switch (m_connectWay) {
    case 0:
        ui->UsbButton->setStyleSheet("\
                                         image:url(:/image/icon/usb.png);\
                                         border:0px solid red;\
                                         ");
        m_connectWay = 3;
        return;
    case 1:
    case 3:
        ui->UsbButton->setStyleSheet("\
                                         image:url(:/image/icon/usb.png);\
                                         border:2px solid red;\
                                         ");
        ui->WifiButton->setStyleSheet("\
                                         image:url(:/image/icon/wifi.png);\
                                         border:0px solid red;\
                                         ");
        break;
    default:
        break;
    }
    m_connectWay = 0;
}

void CarlifeWindow::on_WifiButton_clicked()
{
    qDebug()<<"wifi button is down";
    switch (m_connectWay) {
    case 1:
        ui->WifiButton->setStyleSheet("\
                                         image:url(:/image/icon/wifi.png);\
                                         border:0px solid red;\
                                         ");
        m_connectWay = 3;
        return;
    case 0:
    case 3:
        ui->UsbButton->setStyleSheet("\
                                         image:url(:/image/icon/usb.png);\
                                         border:0px solid red;\
                                         ");
        ui->WifiButton->setStyleSheet("\
                                         image:url(:/image/icon/wifi.png);\
                                         border:2px solid red;\
                                         ");
        break;
    default:
        break;
    }
    m_connectWay = 1;
}

void CarlifeWindow::on_sureButton_clicked()
{
    qDebug()<<"sure button is down";
    if(m_platform == 3 || m_connectWay ==3 ){
        qDebug()<<"please select platform or connectway";
        frmMessageBox* msg = new frmMessageBox();
        msg->SetMessage("请选择手机系统和连接方式！",2);
        msg->exec();

    }else{
        qDebug()<<"connecting...";
        ui->stackedWidget->setCurrentIndex(1);
        pMovie = new QMovie(":/image/icon/waitting_3.gif");
        ui->waittingLabel->setScaledContents(false);
        ui->waittingLabel->setMovie(pMovie);
        pMovie->start();
#if 1
        workerthread = new WorkerThread(this);
        connect(workerthread,SIGNAL(connectSuccess()),this,SLOT(on_connectSuccess()));
        connect(workerthread,SIGNAL(connectBreak()),this,SLOT(on_connectBreak()));
        workerthread->start();
#endif
    }

}
void CarlifeWindow::test()
{
    qDebug()<<"begin test";
    int cnt = 1;
    while(cnt--)
    {
//        sleep(2);
        on_connectSuccess();
//        sleep(3);
//        on_connectBreak();
//        sleep(1);
    }

}
void CarlifeWindow::on_connectSuccess()
{
    //qDebug()<<"CarlifeWindow attach connectSuccess signal";
    //workerthread->terminate();
    m_carlifeStatus = 1;
    ui->statusLabel->setText("连接成功！");
    pMovie->setPaused(true);
    ui->statusIconLabel->setStyleSheet("border-image:url(:/image/icon/connect.png)");
    this->hide();

    m_scene->show();
//    clsButton->show();
}

void CarlifeWindow::on_connectBreak()
{
    qDebug()<<"CarlifeWindow attach connectbreak signal";
    m_carlifeStatus = 0;
    ui->statusIconLabel->setStyleSheet("border-image:url(:/image/icon/disconnect.png)");
    ui->statusLabel->setText("连接中断,尝试重连中...");
    pMovie->start();
    clsButton->hide();
    this->show();
    m_scene->hide();
    ui->stackedWidget->setCurrentIndex(1);
}


WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent)
{
    qDebug() << "Worker Thread : " << QThread::currentThreadId();
    m_curConnectStatus = 0;
    m_oldConnectStatus = 0;
}
WorkerThread::~WorkerThread()
{
    qDebug()<<"~WorkerThread";
}

void WorkerThread::WorkerThread::run()
{
    //qDebug() << "Worker Run Thread : " << QThread::currentThreadId() ;
#if 1
    while(1){
        m_curConnectStatus = carlife_service_get_connection_status();

        switch (m_curConnectStatus) {
        case 1:
            if(m_oldConnectStatus == 1){//status is remain connected don't send mesg
                continue;
            }else{
                //qDebug()<<"connect success";
                m_oldConnectStatus = 1;
                emit connectSuccess();
                continue;
            }
        case 0:
        default://if not connect
            if (m_oldConnectStatus == 1){
                //send mesg the connection is break
                //qDebug()<<"connection is break! need destory";
                //carlife_service_destroy();//maybe error
                m_oldConnectStatus = 0;
                emit connectBreak();
            }else{
                //qDebug()<<"2 carlife_service_destroy";
                carlife_service_destroy();
                qDebug()<<"carlife_service_init";
                carlife_service_init();
                carlife_service_connect_to_mobile();
                continue;
            }//case 0
        }//switch
    }//while
#endif
}

void CarlifeWindow::on_pushButton_clicked()
{
    test();
}
void CarlifeWindow::on_reverseControl_Down(int pos_x, int pos_y)
{
#if 1
    int phone_width,phone_height,phone_frameRate;//phone will set these
    int real_x, real_y;//we will transfer these to phone
    if(m_carlifeStatus == 1){
        carlife_service_get_video_info(&phone_width, &phone_height, &phone_frameRate);
        //coordinate transform
        real_x = pos_x * phone_width / LCD_WIDTH;
        real_y = pos_y * phone_height / LCD_HEIGHT;
        qDebug()<<QString("on_reverseControl_Down after transform the positon is \
                     (%1,%2)").arg(real_x).arg(real_y);
        #if 1
        TouchActionPosition pos_send;
        pos_send.x = real_x;
        pos_send.y = real_y;
        carlife_service_send_touch_action(TOUCH_ACTION_DOWN, &pos_send);
        #endif
    }else{
        qDebug()<<"Oops, carlife is disconnected!!";
        return ;
    }
#endif
}

void CarlifeWindow::on_reverseControl_Move(int pos_x, int pos_y)
{
    int phone_width,phone_height,phone_frameRate;//phone will set these
    int real_x, real_y;//we will transfer these to phone
    if(m_carlifeStatus == 1){
        carlife_service_get_video_info(&phone_width, &phone_height, &phone_frameRate);
        //coordinate transform
        real_x = pos_x * phone_width / LCD_WIDTH;
        real_y = pos_y * phone_height / LCD_HEIGHT;
        qDebug()<<QString("on_reverseControl_Move after transform the positon is \
                    (%1,%2)").arg(real_x).arg(real_y);
         #if 1
        TouchActionPosition pos_send;
        pos_send.x = real_x;
        pos_send.y = real_y;
        carlife_service_send_touch_action(TOUCH_ACTION_MOVE, &pos_send);
        #endif

    }else{
        qDebug()<<"Oops, carlife is disconnected!!";
        return ;
    }
}

void CarlifeWindow::on_reverseControl_Up(int pos_x, int pos_y)
{
    int phone_width,phone_height,phone_frameRate;//phone will set these
    int real_x, real_y;//we will transfer these to phone
    if(m_carlifeStatus == 1){
        carlife_service_get_video_info(&phone_width, &phone_height, &phone_frameRate);
        //coordinate transform
        real_x = pos_x * phone_width / LCD_WIDTH;
        real_y = pos_y * phone_height / LCD_HEIGHT;
        qDebug()<<QString("on_reverseControl_Up after transform the positon is\
                     (%1,%2)").arg(real_x).arg(real_y);
        #if 1
        TouchActionPosition pos_send;
        pos_send.x = real_x;
        pos_send.y = real_y;
        carlife_service_send_touch_action(TOUCH_ACTION_UP, &pos_send);
        #endif
    }else{
        qDebug()<<"Oops, carlife is disconnected!!";
        return ;
    }
}
