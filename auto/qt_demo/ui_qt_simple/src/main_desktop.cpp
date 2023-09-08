#include "main_desktop.h"
#include "ui_main_desktop.h"
#include <QDesktopWidget>
#include "frmmessagebox.h"
#include "videowidget.h"
#include "reverseline_setting.h"
#include "midwindow.h"
#include <dirent.h>
#include<iostream>
#include "EveHandle.h"
#include "AutoMount.h"//mod lss

#if defined(os_test)
#ifdef CAMERA_TEST
dvr_factory* pdvr;
#ifdef ANTHOR_CAMERA
dvr_factory* pdvr1;
#endif
#endif
#endif


using namespace std;

QFileInfo fileInfo_to_play;
QFileInfo fileInfo_to_show;
QFileInfo fileInfo_music_to_play;
int g_recordstatus=0;


int recordTime=1;//set record time
bool isTrue=true;
//read config.ini get resolution
int cameraHeight=0;
int cameraWidth=0;
//update voice value
int now_voice_value=50;
#if 0
extern int startA,startB,widthA,heightA;
#endif
int rotate_angle=15;
//read config.ini get settings
int open_recordVideo_front,open_recordVideo_rear;
int open_recordAudio_front,open_recordAudio_rear;
int open_reverseLine_front=1,open_reverseLine_rear;
int open_adas_front,open_adas_rear;
main_desktop* pStaticMaindesktop=NULL;
extern ReverseLine_Setting *pStatic_reverseLine;
QString linux_usb_path="/mnt/usb/sda4/";//usb path init;
QString linux_sdcard_path;//sdcard
MidWindow* midwindow=NULL;
SetFirst* pStaticSetfirst=NULL;

#if defined(os_test)
extern int is_dir_exist(const char *dir_path);
using namespace android;
void usernotifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void* user){
    LOGE("msgType =%d-----data=%p-----%d)",msgType,user);
#ifdef CAMERA_TEST
    if ((msgType&CAMERA_MSG_ERROR) ==CAMERA_MSG_ERROR)
    {
        LOGE("(msgType =CAMERA_MSG_ERROR)");
    }
    if ((msgType&CAMERA_MSG_DVR_NEW_FILE) ==CAMERA_MSG_DVR_NEW_FILE)
    {
        dvr_factory *p_dvr=(dvr_factory *)user;
        LOGE("(msgType =CAMERA_MSG_DVR_NEW_FILE camera %d idx =%d)",p_dvr->mCameraId,ext1);
    }

    if ((msgType&CAMERA_MSG_DVR_STORE_ERR) ==CAMERA_MSG_DVR_STORE_ERR)
    {
        LOGE("msgType =CAMERA_MSG_DVR_STORE_ERR)");
        dvr_factory *p_dvr=(dvr_factory *)user;
        //p_dvr->storage_state=0;//tmp mod lss
        p_dvr->stopRecord();
    }
#endif
}
void userdataCallback(int32_t msgType,char* dataPtr, camera_frame_metadata_t *metadata, void* user)
{
    //LOGE("userdataCallback=-----------)");
}

void userdataCallbackTimestamp(nsecs_t timestamp, int32_t msgType, char* dataPtr, void* user){
    char *ptp=(char *)dataPtr;
    VencInputBuffer *p=(VencInputBuffer *)(ptp+4);
    // memcpy(inputBuffer.pAddrVirY,(unsigned char*)p->pAddrVirY,encode_param.src_width*encode_param.src_height);
    // memcpy(inputBuffer.pAddrVirC,(unsigned char*)p->pAddrVirY+encode_param.src_width*encode_param.src_height,encode_param.src_width*encode_param.src_height/2);
}

status_t usr_datacb(int32_t msgType, char *dataPtr,int dalen, void *user){
    return 0;
}

#endif


main_desktop::main_desktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_desktop)
{
#if defined(os_test)
    //if start record when machine is start
    //read config.ini
    open_recordVideo_front=config_get_startup(0);
    open_recordAudio_front=config_get_sound(0);
    open_adas_front=config_get_adas(0);
    open_reverseLine_front=1;
    cameraWidth=config_get_weith(0);
    cameraHeight=config_get_heigth(0);
    recordTime=config_get_cyctime(0);
    qDebug()<<"---------cameraHeight is:"<<cameraHeight<<"cameraWidth is:"<<cameraWidth;
    if(open_recordVideo_front==1)
    {
        isRecording=true;
    }else{
        isRecording=false;
    }

    HwDisplay* mcd=NULL;
    int i;
    int tvmode=3;//0 disable ,1 tvout pal ;2 tvout ntsc;3 hdmi 1280x720;4 hdmi 1920x1080
    cur_camera = 0 ;

    //test screen mode
    //0 disable
    //config_set_tvout(0,tvmode);
    int rt=0;
//    sdk_log_setlevel(3);
    mcd=HwDisplay::getInstance();
    
    #ifdef CAMERA_TEST
    pdvr=new dvr_factory(0);
    #ifdef ANTHOR_CAMERA
    pdvr1=new dvr_factory(1);
    #endif
    #ifdef AUDIO_TEST //defined
        //AudioCapThread audiocap;
        sp<AudioCapThread> audiocap=new AudioCapThread();
		int hdl = audiocap->reqAudioSource(pdvr->__dvr_audio_data_cb_timestamp,(void *)pdvr);
		pdvr->setAudioOps(audiocap, hdl);
        #ifdef ANTHOR_CAMERA
        sp<AudioCapThread> audiocap1=new AudioCapThread();
		int hdl1 = audiocap->reqAudioSource(pdvr1->__dvr_audio_data_cb_timestamp,(void *)pdvr1);
		pdvr1->setAudioOps(audiocap1, hdl1);
        #endif
         printf("--------------------------------AudioCapThread done\n");
    #endif
    #endif

	AutoMountInit(pdvr);// only can regisister "ONLY ONE"  function   

    tvmode=config_get_tvout(TEST_CAMERA_ID);
    printf("--------------tvmode =%d \r\n",tvmode);
    mcd->hwd_screen1_mode(tvmode);
    printf("------------------------------------camera initial done\n");

#endif
    ui->setupUi(this);
    pStaticMaindesktop=this;

    connect(midwindow,SIGNAL(sdcard_delete()),this,SLOT(on_sdcard_delete()));
    connect(midwindow,SIGNAL(sdcard_insert()),this,SLOT(on_sdcard_insert()));
    FormInCenter();
    setAttribute(Qt::WA_TranslucentBackground, true);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    ft.setFamily("Microft YaHei");
    ui->time_Label->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->time_Label->setPalette(pa);
//    ui->cameraView->setHidden(true);
    cameraState=true;

    setButtonVisible();
    setMouseTracking(true);
    mouseMoveTime = new QTimer();
    connect(mouseMoveTime,SIGNAL(timeout()),this,SLOT(on_mouse_no_active_10_second()));
    mouseMoveTime->start(8000);

//    setProperty("noinput",true);
#if !defined(os_test)
    open_reverseLine_front=1;
#endif
    reverseLinewidget=new reverseLineWidget();
    if(open_reverseLine_front)
    {
        qDebug()<<"reversline--------------"<<ui->widget->size();
        reverseLinewidget->resize(990,430);
         reverseLinewidget->setParent(ui->widget);
    }

    printf("main_desktop----------%p----\r\n",this);
    printf("-------------------------------------construction function done\n");
    midwindow=new MidWindow();
    setting_desktop=new SetFirst(this);
    moviedesk=new movieDesk1(this);

    setting_desktop->FormInCenter();
    moviedesk->FormInCenter();

}

void main_desktop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 10, 90));
}

void main_desktop::startRecord()
{
#if defined(os_test)
#ifdef CAMERA_TEST
    printf("startRecord--------------\r\n");
    Mutex::Autolock locker(&mObjectLock);
    char bufname[512];
    int rt=0;
    qDebug()<<"-------------------------------initing";
    rt=pdvr->recordInit();//init the record mod lss

    pdvr->SetDataCB(usr_datacb,pdvr);
    pdvr->setCallbacks(usernotifyCallback,userdataCallback,userdataCallbackTimestamp,pdvr /*dump*/);
    //pdvr->start(); //mod lss
    #ifdef ANTHOR_CAMERA
    rt=pdvr1->recordInit();//mod lss
    pdvr1->SetDataCB(usr_datacb,pdvr1);
    F_LOG;
    pdvr1->setCallbacks(usernotifyCallback,userdataCallback,userdataCallbackTimestamp,pdvr1 /*dump*/);
    F_LOG;
    //pdvr1->start(); //mod lss
    #endif
    qDebug()<<"-----------------------------initing done";
    pdvr->enableWaterMark();
    sprintf(bufname,"64,64,0,64,250,T3L SDK,64,450,ASTEROID V1 alpha");
    pdvr->setWaterMarkMultiple(bufname);
    if(isRecording)
    {
        DIR* dir;
        dir=opendir("/mnt/sdcard/mmcblk1p1/");

        if(dir!=NULL){
            closedir(dir);
            qDebug()<<"start up with record";
            int ret=0;
            ret=pdvr->startRecord();
            if(ret!=0)
            {
                qDebug()<<"startRecord error! pls insert sdcard";
                isRecording=false;
            }else{
                isRecording=true;
            }
            #ifdef ANTHOR_CAMERA
            ret=pdvr1->startRecord();
            if(ret!=0){
                qDebug()<<"startRecord error! pls insert sdcard";
                isRecording=false;
            }else{
                isRecording=true;
            }
            #endif

        }else{
            qDebug()<<"can't find sdcard";
            isRecording=false;
        }

    }
#endif
#endif
}
int main_desktop::startAllCameraWithPreview(int camera_no /* nouse now*/)
{
#if defined(os_test)
   startRecord();
   printf("startAllCameraWithPreview play %d\r\n",cur_camera);
#if 0
   startA=0;startB=150;widthA=1024;heightA=300;
#endif
   #ifdef CAMERA_TEST
   ui->pushButton->setStyleSheet("border-image:url(:/icon/switchButton_1)");
   struct view_info vv= {0,0,1024,600};
   if(cur_camera==0){
        pdvr->startPriview(vv);
        cur_camera=0;
   }else{
    #ifdef ANTHOR_CAMERA
          pdvr1->startPriview(vv);
          cur_camera=1;
     #endif

   }
    #endif
#endif
    return 0;
}


main_desktop::~main_desktop()
{
    delete ui;
    delete setting_desktop;
    delete moviedesk;
    delete reverseLinewidget;
    #if defined(os_test)
#ifdef CAMERA_TEST
    //delete dvr;
    //pdvr->enc_de_init();//mod lss
    F_LOG;
    pdvr->uninitializeDev();
    F_LOG;
    #ifdef ANTHOR_CAMERA
    //pdvr1->enc_de_init();
    F_LOG;
    pdvr1->uninitializeDev();
    F_LOG;
    delete pdvr1;
    #endif
    delete pdvr;
#endif
   // delete pgEmulatedCameraFactory;
    #endif
}
void main_desktop::on_sdcard_delete()
{
    qDebug()<<"sdcard is out";
    if(isRecording)
    {
        qDebug()<<"sdcard is out,stopRecord";
#if defined(os_test)
    #ifdef CAMERA_TEST
    int retrec=pdvr->stopRecord();
    #ifdef ANTHOR_CAMERA
    retrec=pdvr1->stopRecord();
    #endif
    #endif
#endif
    isRecording=false;
    }
}

void main_desktop::on_sdcard_insert()
{
    qDebug()<<"sdcard is insert";
}

void main_desktop::timerUpdate(void)
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString time= current_time.toString("hh:mm:ss ddd");
    ui->time_Label->setText(time);
}

void main_desktop::on_mouse_no_active_10_second()
{
    setButtonDisvisible();
    ui->widget->move(QPoint(10,71));
}

void main_desktop::on_mouse_active()
{
    mouseMoveTime->stop();
    mouseMoveTime->start();

    setButtonVisible();
}

void main_desktop::mouseDoubleClickEvent(QMouseEvent *)
{
    on_mouse_active();
}
void main_desktop::mouseMoveEvent(QMouseEvent *)
{
    on_mouse_active();
}
void main_desktop::mousePressEvent(QMouseEvent *)
{
    on_mouse_active();
}
void main_desktop::mouseReleaseEvent(QMouseEvent *)
{
    on_mouse_active();
}
void main_desktop::on_main_desktop_disvisible()
{
    qDebug()<<"main_desktop will hidden";
//    this->setHidden(true);
    #if defined(os_test)
#ifdef CAMERA_TEST
        pdvr->stopPriview();
        #ifdef ANTHOR_CAMERA
        pdvr1->stopPriview();
        #endif
#endif
    #endif
}
void main_desktop::on_main_desktop_visible()
{
    qDebug()<<"camera preview restart";
//    this->setHidden(false);
//    this->moviedesk->activateWindow();
    #if defined(os_test)
    #ifdef CAMERA_TEST
        struct view_info vv= {0,0,1024,600};
        if(cur_camera==0){
             pdvr->startPriview(vv);
             cur_camera=0;
        }else{
     #ifdef ANTHOR_CAMERA
           pdvr1->startPriview(vv);
           cur_camera=1;
      #endif

        }
    #endif
    #endif
}

void main_desktop::on_cameraButton_clicked()
{
    if(cameraState)
    {
        qDebug()<<"now is front camera";
    #if defined(os_test)
        printf("----------------------front camera take pic\n");
        Mutex::Autolock locker(&mObjectLock);
        status_t rt;
        #ifdef CAMERA_TEST
        rt=pdvr->takePicture();
        #endif
        if(0!=rt){
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("take pic fail!")),2);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        }
        else
        {
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("take pic success!")),0);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        }
    #endif
    }else{
        qDebug()<<"now is rear camera";
    #if defined(os_test)
        printf("----------------------rear camera take pic\n");
        #ifdef ANTHOR_CAMERA
        Mutex::Autolock locker(&mObjectLock);
        status_t rt;
        #ifdef CAMERA_TEST
        rt=pdvr1->takePicture();
        #endif
        if(0!=rt){
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("take pic fail!")),2);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        }else{
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("take pic success!")),0);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        }
        #endif
    #endif
    }

}

void main_desktop::on_recordButton_clicked()
{
    if(isRecording){
        qDebug()<<"isRecording sure to stop?";
        frmMessageBox *msg=new frmMessageBox;
        msg->SetMessage(QString(tr("sure to stop record?")),1);
        if(1==msg->exec())
        {
            qDebug()<<"ready to stop record";
        #if defined(os_test)
            #ifdef CAMERA_TEST
            int retrec=pdvr->stopRecord();
            #ifdef ANTHOR_CAMERA
            retrec=pdvr1->stopRecord();
            #endif
            #endif
        #endif
            isRecording=false;
        }else{

        }

    }else{
    #if defined(os_test)
        #if defined(os_test)
        recordTime=config_get_cyctime(0);
        #endif
        qDebug()<<"camera ready to start record";
        qDebug()<<"now record time is"<<recordTime<<"min";
        #ifdef CAMERA_TEST
        //pdvr->setDuration(recordTime*60);//mod lss
        int retrec=pdvr->startRecord();
        #ifdef ANTHOR_CAMERA
        //pdvr1->setDuration(recordTime*60);//mod lss
        retrec=pdvr1->startRecord();
        #endif
        if(retrec<0){
            ALOGE("!!start record fail pls insert tf card");
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("Please insert sdcard!")),2);
            QTimer::singleShot(5000, msg, SLOT(close()));
            msg->exec();
            g_recordstatus=0;
            isRecording=false;
        }else{
            g_recordstatus=1;
            frmMessageBox *msg=new frmMessageBox;
            msg->SetMessage(QString(tr("camera start record!")),0);
            QTimer::singleShot(5000, msg, SLOT(close()));
            msg->exec();
            isRecording=true;
        }
        #endif

    #endif
    }
}

void main_desktop::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth,deskHeight);
}
void main_desktop::setButtonVisible()
{
    ui->widget_2->setVisible(true);
}
void main_desktop::setButtonDisvisible()
{
    ui->widget_2->setVisible(false);
}

void main_desktop::on_camera_change_Button_clicked()
{
    if(!cameraState)
    {
    #if defined(os_test)
        #ifdef CAMERA_TEST
        #ifdef ANTHOR_CAMERA
        struct view_info vv= {0,0,1024,600};
        pdvr1->stopPriview();
        pdvr->startPriview(vv);
        cur_camera=0;
        #endif
        #endif
    #else
//        ui->cameraView->setStyleSheet(tr("background-image: url(:/picture.png);"));
    #endif
        cameraState=true;
    }
    else
    {
    #if defined(os_test)
        #ifdef CAMERA_TEST
        #ifdef ANTHOR_CAMERA
        struct view_info vv= {0,0,1024,600};
        pdvr->stopPriview();
        pdvr1->startPriview(vv);
        cur_camera=1;
        #endif
        #endif
    #else
//        ui->cameraView->setStyleSheet(tr("background-image: url(:/picture1.png);"));
    #endif
        cameraState=false;
    }
}

void main_desktop::on_setFirstButton_clicked()
{
    setting_desktop->show();
    this->setHidden(true);
}

void main_desktop::on_movieButton_clicked()
{
    qDebug()<<"open movie";
    moviedesk->show();
    this->setHidden(true);
}
void main_desktop::on_reverseLine_repaint()
{
    reverseLinewidget->update();
}

void main_desktop::on_pushButton_clicked()
{
    if(isTrue){
#if defined(os_test)
    #ifdef CAMERA_TEST
    pdvr->stopPriview();
    #ifdef ANTHOR_CAMERA
    pdvr1->stopPriview();
    #endif
    #endif
    ui->pushButton->setStyleSheet("border-image:url(:/icon/switchButton_2)");
#endif
    isTrue=false;
    }else{
#if defined(os_test)
    struct view_info vv= {0,0,1024,600};
    #ifdef CAMERA_TEST
    if(cur_camera==0){
         pdvr->startPriview(vv);
         cur_camera=0;
    }else{
 #ifdef ANTHOR_CAMERA
       pdvr1->startPriview(vv);
       cur_camera=1;
  #endif

    }
    #endif
     ui->pushButton->setStyleSheet("border-image:url(:/icon/switchButton_1)");
#endif
    isTrue=true;
    }
}
