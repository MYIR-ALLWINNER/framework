#include "pmmain.h"
#include "ui_pmmain.h"

#include "dbusmirrorclient.h"

enum ECTransportType
{
    EC_TRANSPORT_ANDROID_USB_ADB = 0,            ///< android usb adb, system screen
    EC_TRANSPORT_ANDORID_USB_AOA,                ///< android usb aoa, app screen
    EC_TRANSPORT_ANDROID_WIFI,                   ///< android wifi, app screen
    EC_TRANSPORT_IOS_USB_EAP,                    ///< iphone usb eap, app screen
    EC_TRANSPORT_IOS_USB_MUX,                    ///< iphone usb mux, app screen
    EC_TRANSPORT_IOS_USB_AIRPLAY,                ///< iphone usb airplay, system screen
    EC_TRANSPORT_IOS_WIFI_APP,                   ///< iphone wifi app, app screen
    EC_TRANSPORT_IOS_WIFI_AIRPLAY,               ///< iphone wifi airplay, system screen
    EC_TRANSPORT_MAX,                            ///< reserve
};


pmMain* pmMain::mAPP_instance = NULL;
pmMain *pmMain::getInstance(QWidget *parent)
{
    if(mAPP_instance == NULL)
    {
        mAPP_instance = new pmMain(parent);
        atexit(release);
    }
    return mAPP_instance;
}

void pmMain::release()
{
    if(mAPP_instance)
    {
        delete mAPP_instance;
        mAPP_instance = NULL;
    }
}

pmMain::pmMain(QWidget *parent) :
    CustomWidget(parent),
    ui(new Ui::pmMain),
    btnIsPressed(false),
    btnMoved(false)
{
    ui->setupUi(this);
    this->setObjectName("pmMain");
    this->setStyleSheet("QWidget#pmMain {border-image:url(:/pmc_image/bg.png);}");

    connectstatus =0;
    mirrorstate = false;

    connect(&mbgthread,SIGNAL(bgnotify(int, int)),this,SLOT(OnNotify(int, int)));
    mbgthread.bg_handlestart();

    //qDebug()<<"pmMain transparen---------------------------------->>>t";

    ui->btnFloat->hide();
    ui->btnYL->hide();
    ui->btnQuit->hide();
    ui->btnBack->hide();
    ui->btnMirror->hide();

    failPrompt = new FailPrompt(this);
    failPrompt->hide();
    int out;

    int ret = mbgthread.dbusrpc_mirror_set_cmd(CMD_SYNC_PHONE_STAT, 0, 0,2/* 0 up;1 down;2 move*/, &out);
    if(ret>=0){
        if(out==PHONE_CONED)
        {
            connectstatus =1;
             qDebug()<<"pmMain get phone connect---------------------------------->>>t";
        }
    }
    mPhoneModeType = EC_TRANSPORT_ANDORID_USB_AOA;
    qDebug()<<"\n\n\n------------------connectstatus ----------------"<<connectstatus<<"out:"<<out;

}

pmMain::~pmMain()
{
    delete ui;
}
void pmMain::showMainWidget()
{
    if(mirrorstate)
        return;
    qDebug()<<"\n\n\n"<<__FUNCTION__<<"in"<<endl;
    this->setStyleSheet("QWidget#pmMain {border-image:url(:/pmc_image/bg.png);}");
    setStyleSheet("background-color:rgb(0,0,0);");
    ui->welcome->hide();
    if(0){
        int out;
        mbgthread.dbusrpc_mirror_set_cmd(CMD_START_MIRROR, 0, 0,2/* 0 up;1 down;2 move*/, &out);
        ui->label->setText("正在连接...");
        hideCurrentWidget();
    }else
    {
        ui->label->setVisible(true);
        ui->label->setText("请使用USB线插入手机");
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_3->setVisible(true);
        ui->btnFloat->hide();

        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
    }

}
void pmMain::showPhoneMachineConnect()
{
    //Q_EMIT Navigation::getInstance(this)->hideNavigationBar();
    qDebug()<<"\n\n\n"<<__FUNCTION__<<"in"<<endl;
    this->show();
    ui->welcome->show();
    ui->label->show();
    ui->label_2->show();
    ui->btnFloat->hide();

    welcomeTimer = new QTimer(this);
    welcomeTimer->singleShot(2000,this,SLOT(showMainWidget()));

    if(connectstatus){
        int out;
        int ret = mbgthread.dbusrpc_mirror_set_cmd(CMD_START_MIRROR, 0, 0,2/* 0 up;1 down;2 move*/, &out);
        if(ret<0){
             connectstatus =0;
        }
    }
}

void pmMain::closePhoneMachineConnect()
{
    ui->btnYL->hide();
    ui->btnQuit->hide();
    ui->btnBack->hide();
    ui->btnMirror->hide();
    this->close();
    emit quitPmconnect();
}

void pmMain::OnNotify(int msg,int val)
{
    qDebug()<<"OnNotify : msg= "<<msg<<"val="<<val;
    switch(msg)
    {
    case ON_PHONE_CONED:
    //连接成功  -----背景设置透明
        if(connectstatus== 0){
            ui->label->setText("正在连接...");
            int out;
            mbgthread.dbusrpc_mirror_set_cmd(CMD_START_MIRROR, 0, 0,2/* 0 up;1 down;2 move*/, &out);
            connectstatus=1;
            mPhoneModeType = val;

        }
        break;
    case ON_PHONE_DISCONED:
     //手机拔掉
        qDebug()<<"拔掉手机";
        //failPrompt->show();
        connectstatus=0;
        break;
    case ON_MIRROR_DISCONED:


        break;
    case ON_MIRROR_START:
        if(mirrorstate!=true)
        {
            mirrorstate=true;
            if(isVisible()){
                hideCurrentWidget();
            }
        }
        break;
    case ON_MIRROR_STOP:
        if(mirrorstate!=false)
        {
            mirrorstate=false;
            showMainWidget();
        }
        break;

    case ON_ECStatusMessage:


        break;
    case ON_PhoneAppHUD:


        break;
    case ON_PhoneAppInfo:


        break;
    case ON_CallAction:

        break;
    case ON_LicenseAuthFail:
        //认证失败

        break;
    case ON_PhoneAppExited:
        //手机app退出

        break;
    case ON_SyncPhoneStat:
        if(val==PHONE_CONED)
        {
            connectstatus =1;
             qDebug()<<"pmMain get ON_SyncPhoneStat-----------";
        }else
             connectstatus =0;
        break;
    }
}
void pmMain::hideCurrentWidget()
{
    ui->welcome->hide();
    setAttribute(Qt::WA_TranslucentBackground,true);
    setStyleSheet("background-color: transparent");
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->btnFloat->show();
    ui->btnYL->hide();
    ui->btnQuit->hide();
    ui->btnBack->hide();
    ui->btnMirror->hide();
    qDebug()<<"hideCurrentWidget";

}
void pmMain::on_pushButton_clicked()
{
//    this->close();
    closePhoneMachineConnect();
}

void pmMain::on_pushButton_3_clicked()
{
    help = new Help(this);
    help->show();
}

void pmMain::on_btnFloat_clicked()
{
    qDebug()<<"pmMain::on_btnFloat_clicked ---------->>>>>>>>>>>";
    if(btnMoved)
        return;
    if(mPhoneModeType==EC_TRANSPORT_ANDROID_USB_ADB)
    {
        if(!ui->btnQuit->isVisible()){

            ui->btnYL->show();
            ui->btnQuit->show();
            ui->btnBack->show();
            ui->btnMirror->show();
        }else
        {
            ui->btnYL->hide();
            ui->btnQuit->hide();
            ui->btnBack->hide();
            ui->btnMirror->hide();
        }
    }else
    if(mPhoneModeType==EC_TRANSPORT_ANDORID_USB_AOA)
    {
        if(!ui->btnQuit->isVisible()){

        ui->btnYL->show();
        ui->btnQuit->show();
        ui->btnMirror->show();
        ui->btnBack->hide();
        }else
        {
            ui->btnYL->hide();
            ui->btnQuit->hide();
            ui->btnBack->hide();
            ui->btnMirror->hide();
        }
    }else

    if((mPhoneModeType==EC_TRANSPORT_IOS_USB_EAP)\
           || (mPhoneModeType==EC_TRANSPORT_IOS_USB_MUX) \
           || (mPhoneModeType==EC_TRANSPORT_IOS_USB_AIRPLAY)\
           || (mPhoneModeType==EC_TRANSPORT_IOS_WIFI_AIRPLAY)\
           || (mPhoneModeType==EC_TRANSPORT_IOS_WIFI_APP))
    {
       if(!ui->btnQuit->isVisible()){

            ui->btnYL->hide();
            ui->btnQuit->show();
            ui->btnBack->hide();
            ui->btnMirror->show();
        }else
       {
           ui->btnYL->hide();
           ui->btnQuit->hide();
           ui->btnBack->hide();
           ui->btnMirror->hide();
       }
    }


}

//相当于手机的返回键,发送事件到手机
void pmMain::on_btnBack_clicked()
{
qDebug()<<"on_btnBack_clicked";
if(connectstatus){
    int out;
   mbgthread.dbusrpc_mirror_set_cmd(CMD_KEY_EVENT, 2/*EC_SYSTEM_KEYCODE_BACK*/, 0,2/* 0 up;1 down;2 move*/, &out);
   //connectstatus = 0;
}
}
//返回到亿连客户端
void pmMain::on_btnYL_clicked()
{
    qDebug()<<"on_btnYL_clicked";
    if(connectstatus){
        int out;
       mbgthread.dbusrpc_mirror_set_cmd(CMD_YL_OPEN_PAGE, 7/*EC_APP_PAGE_MAIN*/, 0,2/* 0 up;1 down;2 move*/, &out);
       //connectstatus = 0;
    }
}
//退出到亿联到车机主界面
void pmMain::on_btnQuit_clicked()
{
    closePhoneMachineConnect();
    if(connectstatus){
        int out;
       mbgthread.dbusrpc_mirror_set_cmd(CMD_STOP_MIRROR, 0, 0,2/* 0 up;1 down;2 move*/, &out);
       //connectstatus = 0;
    }

}
//悬浮按钮被按下
void pmMain::on_btnFloat_pressed()
{
    qDebug()<<"pmMain::on_btnFloat_pressed ---------->>>>>>>>>>> set btnIsPressed=true";
    btnIsPressed = true;
    btnMoved = false;
}
//悬浮按钮按下后释放
void pmMain::on_btnFloat_released()
{
    qDebug()<<"pmMain::on_btnFloat_released ---------->>>>>>>>>>>";

}
//
void pmMain::mouseMoveEvent(QMouseEvent *event)
{
       if(btnIsPressed)
       {
           //QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
           if(!btnMoved)
               btnMoved = true;
           ui->btnFloat->setGeometry(event->x(),event->y(),ui->btnFloat->width(),ui->btnFloat->height());
       }
       else
       {
           //qDebug()<<"pmMain::mouseMoveEvent ---------->>>>>>>>>>>parent handle";
           QWidget::mouseMoveEvent(event);
           int m_x = event->globalX();
           int m_y = event->globalY();
           //qDebug()<<QString("touch positon:(%1,%2)").arg(m_x).arg(m_y);
           int out;
           if((ui->btnFloat->isVisible()))
                mbgthread.dbusrpc_mirror_set_cmd(CMD_TOUCH_EVENT, m_x, m_y,2/* 0 up;1 down;2 move*/, &out);
       }

}
void pmMain::mousePressEvent(QMouseEvent* event)
{
    // qDebug()<<"--lee, get mousePressEvent event";
     int m_x = event->globalX();
     int m_y = event->globalY();
     //qDebug()<<QString("touch positon:(%1,%2)").arg(m_x).arg(m_y);
     int out;
     if((ui->btnFloat->isVisible()))
        mbgthread.dbusrpc_mirror_set_cmd(CMD_TOUCH_EVENT, m_x, m_y, 1/* 0 up;1 down;2 move*/, &out);
}

void pmMain::mouseReleaseEvent(QMouseEvent *event)
{

    //qDebug()<<"pmMain::mouseReleaseEvent ---------->>>>>>>>>>> set btnIsPressed=false";
    btnIsPressed = false;
    int m_x = event->globalX();
    int m_y = event->globalY();
    //qDebug()<<QString("touch positon:(%1,%2)").arg(m_x).arg(m_y);
    int out;
    if((ui->btnFloat->isVisible()))
        mbgthread.dbusrpc_mirror_set_cmd(CMD_TOUCH_EVENT, m_x, m_y, 0/* 0 up;1 down;2 move*/, &out);
}

void pmMain::on_btnMirror_clicked()
{
    qDebug()<<"on_btnMirror_clicked,connectstatus:"<<connectstatus<<"mirrorstate:"<<mirrorstate<<endl;
    if(connectstatus){
        int out;
        if(mirrorstate)
        {
            mbgthread.dbusrpc_mirror_set_cmd(CMD_STOP_MIRROR, 33, 0,2/* 0 up;1 down;2 move*/, &out);
            ui->btnMirror->setText("Mirror On");
        }
        else
        {
            mbgthread.dbusrpc_mirror_set_cmd(CMD_START_MIRROR, 44, 0,2/* 0 up;1 down;2 move*/, &out);
            ui->btnMirror->setText("Mirror Off");
        }
    }
}
