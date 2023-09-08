#include "main_desktop.h"
#include "ui_main_desktop.h"
#include <QDesktopWidget>
#include "frmmessagebox.h"
#include "reverseline_setting.h"
#include "midwindow.h"
#include <dirent.h>
#include<iostream>
#include <QTime>
#include <QDebug>

#include "AutoMount.h"//mod lss
#include "DvrRecordManager.h"

using namespace std;

QFileInfo fileInfo_to_show;
QFileInfo fileInfo_music_to_play;
int g_RecordStatus = 0;
dvr_factory **g_ppDvr = NULL;

int g_iRecordTime = 1; //set record time
bool isTrue = true;
//read config.ini get resolution
int g_iCameraHeight = 0;
int g_iCameraWidth = 0;
//update voice value
int g_iNowVoiceValue = 50;
#if 0
extern int startA, startB, widthA, heightA;
#endif
int g_iRotateAngle = 15;
//read config.ini get settings
int open_recordVideo_front, open_recordVideo_rear;
int open_recordAudio_front, open_recordAudio_rear;
int open_reverseLine_front = 1, open_reverseLine_rear;
int open_adas_front, open_adas_rear;
main_desktop *g_pStaticMaindesktop = NULL;
extern ReverseLine_Setting *pStatic_reverseLine;
QString linux_usb_path = "/mnt/usb/sda4/"; //usb path init;
QString linux_sdcard_path;//sdcard
MidWindow *g_MidWindow = NULL;
SetFirst *g_pStaticSetfirst = NULL;

#ifdef EVE_TEST
#include "EveHandle.h"
sp < EveHandle > pEveHandleThread;
#endif

#if defined(os_test)
extern int is_dir_exist(const char *dir_path);
using namespace android;
void usernotifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void* user)
{
    LOGE("msgType =%d-----data=%p-----%d)", msgType, user);
    RecordCamera *p_dvr = (RecordCamera*) user;
#ifdef CAMERA_TEST
    if ((msgType & CAMERA_MSG_ERROR) == CAMERA_MSG_ERROR) {
        LOGE("(msgType =CAMERA_MSG_ERROR)");
    }
    if ((msgType & CAMERA_MSG_DVR_NEW_FILE) == CAMERA_MSG_DVR_NEW_FILE) {
        LOGE("(msgType =CAMERA_MSG_DVR_NEW_FILE camera %d idx =%d)", p_dvr->mCameraId, ext1);
    }

    if ((msgType & CAMERA_MSG_DVR_STORE_ERR) == CAMERA_MSG_DVR_STORE_ERR) {
        LOGE("msgType =CAMERA_MSG_DVR_STORE_ERR)");
        if(p_dvr){
            p_dvr->storage_state=0;
            m_pDvrs[p_dev->mCameraId]->stopRecord();
        }
    }
#endif
}
void userdataCallback(int32_t msgType, char* dataPtr, camera_frame_metadata_t *metadata, void* user)
{
    dvr_factory *p_dvr = (dvr_factory *) user;
    V4L2BUF_t *pv4l2_buf = (V4L2BUF_t *) dataPtr;

    if(CAMERA_MSG_PREVIEW_FRAME == msgType){
        #ifdef EVE_TEST
        if(0 == p_dvr->mCameraId){   //only use eve in camera0
            dma_mem_des_t* pEveMem = pEveHandleThread->getEveAllocMem();
            if(pEveMem->phy){
                pEveHandleThread->EveG2dScale((unsigned char *) pv4l2_buf->addrPhyY,pv4l2_buf->width, pv4l2_buf->height,
                            (unsigned char *) pEveMem->phy, 640, 360);

                pEveHandleThread->loadPhyAddr(pEveMem->phy);
            }
            pEveHandleThread->DrawDetectRect((char*)pv4l2_buf->addrVirY, (char*)(pv4l2_buf->addrVirY+1280*720), 1280, 720);

            pthread_mutex_lock(&pEveHandleThread->mEvehandleMutex);
            pthread_cond_signal(&pEveHandleThread->mEvehandleCond);
            pthread_mutex_unlock(&pEveHandleThread->mEvehandleMutex);
        }
        #endif
    }
}

void userdataCallbackTimestamp(nsecs_t timestamp, int32_t msgType, char* dataPtr, void* user)
{
    char *ptp = (char *)dataPtr;
    VencInputBuffer *p = (VencInputBuffer *)(ptp + 4);
    // memcpy(inputBuffer.pAddrVirY,(unsigned char*)p->pAddrVirY,encode_param.src_width*encode_param.src_height);
    // memcpy(inputBuffer.pAddrVirC,(unsigned char*)p->pAddrVirY+encode_param.src_width*encode_param.src_height,encode_param.src_width*encode_param.src_height/2);
}

status_t usr_datacb(int32_t msgType, char *dataPtr, int dalen, void *user)
{
    return 0;
}

int  RecordInit(dvr_factory *pdvr)
{
	int rt=0;

	rt = pdvr->recordInit();
	if (0 != rt) {
		ALOGE("pdvr->recordInit error\n");
		return -1;
	}
	else {
		ALOGD("pdvr->recordInit success,CameraId:%d\n", pdvr->mCameraId);
	}	
	
	pdvr->startRecord();

	return 0;
}

#endif


main_desktop::main_desktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_desktop)
{
	QTime time;
	time.start();

    //if start record when machine is start
    //read config.ini
    open_recordVideo_front = config_get_startup(0);
    open_recordAudio_front = config_get_sound(0);
    open_adas_front = config_get_adas(0);
    open_reverseLine_front = 1;
    g_iCameraWidth = config_get_width(0);
    g_iCameraHeight = config_get_heigth(0);
    g_iRecordTime = config_get_cyctime(0);
    qDebug() << "---------cameraHeight is:" << g_iCameraHeight << "cameraWidth is:" << g_iCameraWidth;
    if(open_recordVideo_front == 1) {
        isRecording = true;
    } else {
        isRecording = false;
    }

    m_iCurCamera = 0 ;
    m_bPreview = false;
    //sdk_log_setlevel(6);

	//preview for camera init
	int cameraId[MAX_TEST_CAMERA] = {0};
	for(int i = 0; i < MAX_TEST_CAMERA; i++)
	{
		cameraId[i] = i;
	}

	for(int i=0;i<MAX_TEST_CAMERA;i++){
		m_pDvrs[i] = new dvr_factory(cameraId[i]);		
	}

    g_ppDvr = m_pDvrs;
	for(int i=0;i<MAX_TEST_CAMERA;i++){
		int rt = m_pDvrs[i]->start();
		if (rt < 0) {
			ALOGE("dvrs[%d]->start() error\n",i);
		}
	}

    #ifdef EVE_TEST
    pEveHandleThread = new EveHandle(1280,720);
    pEveHandleThread->EveInit(640,360);
    pEveHandleThread->EveG2dInit();
    pEveHandleThread->EveAllocMem(640*360*3/2);
    #endif

#if 0
	//start audio capture thread
	sp < AudioCapThread >audiocap = new AudioCapThread();
	DvrRecordManagerInit(); 
	//only support six cameras to record at the same time
	int iRedVideo = 0;
	int iRedVideoState[MAX_TEST_CAMERA];
	int iRedAudioState[MAX_TEST_CAMERA];
	memset(m_iRedCameraState, 0xff, sizeof(m_iRedCameraState));
	memset(iRedVideoState, 0x00, sizeof(iRedVideoState));
	memset(iRedAudioState, 0x00, sizeof(iRedAudioState));
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		if(iRedVideo >= MAX_RED_VIDEOS)
		{
			m_iRedCameraState[iCnt] = 0xff;
			continue;
		}
		iRedVideoState[iCnt] = config_get_startup(iCnt);
		iRedAudioState[iCnt] = config_get_sound(iCnt);
		if(iRedVideoState[iCnt] == 1)
		{
			m_iRedCameraState[iCnt] = 1;
			iRedVideo++;
		}
		else
		{
			m_iRedCameraState[iCnt] = 0xff;
		}
		printf("===g_iRedAudioState[%d]:%d,g_iRedVideoState[%d]:%d\n",iCnt,iRedAudioState[iCnt],iCnt,iRedVideoState[iCnt]);
	}
	
	for(int i=0;i<MAX_TEST_CAMERA;i++){
		if(iRedAudioState[i] == 1)
		{
			int hdl = audiocap->reqAudioSource(m_pDvrs[i]->__dvr_audio_data_cb_timestamp,(void *)m_pDvrs[i]);
			m_pDvrs[i]->setAudioOps(audiocap, hdl);
		}

		if(iRedVideoState[i] == 1)
		{
			m_pDvrs[i]->SetDataCB(usr_datacb, m_pDvrs[i]);
			m_pDvrs[i]->setCallbacks(usernotifyCallback, userdataCallback, userdataCallbackTimestamp, m_pDvrs[i]);
		}

		if(iRedVideoState[i] == 1)
		{
			int ret = RecordInit(m_pDvrs[i]);
			if(ret < 0){
				LOGE("error:RecordInit video%d failed",cameraId[i]);
			}
		}
	}
#else
	//start audio capture thread
	sp < AudioCapThread >audiocap = new AudioCapThread();
	DvrRecordManagerInit(); 
	//only support six cameras to record at the same time
	int iRedVideo = 0;
	// m_iVideoStateCfg[MAX_TEST_CAMERA];
	int iRedAudioState[MAX_TEST_CAMERA];
	memset(m_iRedCameraState, 0xff, sizeof(m_iRedCameraState));
	memset(m_iVideoStateCfg, 0x00, sizeof(m_iVideoStateCfg));
	memset(iRedAudioState, 0x00, sizeof(iRedAudioState));
	for(int iCnt = 0; iCnt < MAX_RED_VIDEOS; iCnt++)
	{
		m_iVideoStateCfg[iCnt] = config_get_startup(iCnt);
		m_iRedCameraState[iCnt] = (m_iVideoStateCfg[iCnt]==1)?1:0;
		iRedAudioState[iCnt] = config_get_sound(iCnt);
		printf("===g_iRedAudioState[%d]:%d,g_iRedVideoState[%d]:%d\n",iCnt,iRedAudioState[iCnt],iCnt,m_iVideoStateCfg[iCnt]);
	}

	for(int i=0;i<MAX_RED_VIDEOS;i++){
		int hdl = audiocap->reqAudioSource(m_pDvrs[i]->__dvr_audio_data_cb_timestamp,(void *)m_pDvrs[i]);
		m_pDvrs[i]->setAudioOps(audiocap, hdl);
		m_pDvrs[i]->SetDataCB(usr_datacb, m_pDvrs[i]);
		m_pDvrs[i]->setCallbacks(usernotifyCallback, userdataCallback, userdataCallbackTimestamp, m_pDvrs[i]);

		if(m_iVideoStateCfg[i] == 1)
		{
			int ret = RecordInit(m_pDvrs[i]);
			if(ret < 0){
				LOGE("error:RecordInit video%d failed",cameraId[i]);
			}
		}
	}

#endif
    AutoMountInit(m_pDvrs[0]);// only can regisister "ONLY ONE"  function

    int tvmode = config_get_tvout(TEST_CAMERA_ID);
    printf("--------------tvmode =%d \r\n", tvmode);
	HwDisplay* mcd = HwDisplay::getInstance();
    mcd->hwd_screen1_mode(tvmode);//0 disable ,1 tvout pal ;2 tvout ntsc;3 hdmi 1280x720;4 hdmi 1920x1080
    printf("------------------------------------camera initial done\n");

    ui->setupUi(this);
    g_pStaticMaindesktop = this;

    connect(g_MidWindow, SIGNAL(sdcard_delete()), this, SLOT(on_sdcard_delete()));
    connect(g_MidWindow, SIGNAL(sdcard_insert()), this, SLOT(on_sdcard_insert()));
    FormInCenter();
    setAttribute(Qt::WA_TranslucentBackground, true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    ft.setFamily("Microft YaHei");
    ui->time_Label->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::white);
    ui->time_Label->setPalette(pa);
//    ui->cameraView->setHidden(true);
    m_bCameraState = true;

    setButtonVisible();
    setMouseTracking(true);
    mouseMoveTime = new QTimer();
    connect(mouseMoveTime, SIGNAL(timeout()), this, SLOT(on_mouse_no_active_10_second()));
    mouseMoveTime->start(8000);

//    setProperty("noinput",true);
#if !defined(os_test)
    open_reverseLine_front = 1;
#endif
    reverseLinewidget = new reverseLineWidget();
    if(open_reverseLine_front) {
        qDebug() << "reversline--------------" << ui->widget->size();
        reverseLinewidget->resize(990, 430);
        reverseLinewidget->setParent(ui->widget);
    }

    printf("main_desktop----------%p----\r\n", this);
    printf("-------------------------------------construction function done\n");
    g_MidWindow = new MidWindow();
    m_pSettingDesktop = new SetFirst(this);
    m_pSettingDesktop->FormInCenter();
}

void main_desktop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 10, 90));
}

int main_desktop::startAllCameraWithPreview(int camera_no /* nouse now*/)
{
    struct view_info vv = {0, 0, 1024, 600};
    //m_pDvrs[camera_no]->startPriview(vv);
    m_iCurCamera = camera_no;
	qDebug() << "startAllCameraWithPreview camera"<<camera_no<<" start";
	m_pCamSelDlg = new CameraSelDlg(this);
	m_pRedselDlg = new RecordSelDlg(this);
    return 0;
}

void main_desktop::CameraSwitch(int iCameraId)
{
    if((m_iCurCamera != iCameraId) && (iCameraId != -1))
	{
		qDebug("===Video%d swtich to new Video%d", m_iCurCamera, iCameraId);
		m_pDvrs[m_iCurCamera]->stopPriview();
		struct view_info vv = {0, 0, 1024, 600};
		m_pDvrs[iCameraId]->startPriview(vv);
		m_iCurCamera = iCameraId;	
	}
}

void main_desktop::RecordCamSel(int *piCameraState)
{
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		//printf("===m_iRedCameraState:%d piCameraState:%d\n", m_iRedCameraState[iCnt],piCameraState[iCnt]);
		if((m_iRedCameraState[iCnt] != 0xff) && (piCameraState[iCnt] != 0xff) 
			&& (m_iRedCameraState[iCnt] != piCameraState[iCnt]))
		{
			//	¼��״̬�л�
			if(piCameraState[iCnt] == 1)
			{
				if(m_iVideoStateCfg[iCnt] == 0)  //��״̬Ϊ����δ����¼��
				{
					int ret = RecordInit(m_pDvrs[iCnt]);
					if(ret < 0){
						LOGE("error:RecordInit video%d failed",iCnt);
					}
				}
				else
				{
					printf("===Camera%d startRecord\n", iCnt);
					m_pDvrs[iCnt]->startRecord();
				}
			}
			else if(piCameraState[iCnt] == 0)
			{
				printf("===Camera%d StopRecord\n", iCnt);
				m_pDvrs[iCnt]->stopRecord();
			}
			m_iRedCameraState[iCnt] = piCameraState[iCnt];
		}
	}
}

main_desktop::~main_desktop()
{
	F_LOG;
    #ifdef EVE_TEST
    if(pEveHandleThread != NULL){
        pEveHandleThread->EveUnInit();
        pEveHandleThread->EveG2dUnInit();
        pEveHandleThread->EveFreeMem();
        pEveHandleThread = NULL;
    }
    #endif

    delete ui;
    delete m_pSettingDesktop;
    delete reverseLinewidget;
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		m_pDvrs[iCnt]->uninitializeDev();
		delete m_pDvrs[iCnt];
	}
}
void main_desktop::on_sdcard_delete()
{
    qDebug() << "sdcard is out";
}

void main_desktop::on_sdcard_insert()
{
    qDebug() << "sdcard is insert";
}

void main_desktop::timerUpdate(void)
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString time = current_time.toString("hh:mm:ss ddd");
    ui->time_Label->setText(time);
}

void main_desktop::on_mouse_no_active_10_second()
{
    setButtonDisvisible();
    ui->widget->move(QPoint(10, 71));
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
    qDebug() << "main_desktop will hidden";
    m_pDvrs[m_iCurCamera]->stopPriview();
}
void main_desktop::on_main_desktop_visible()
{
    qDebug() << "camera preview restart";
    struct view_info vv = {0, 0, 1024, 600};
    m_pDvrs[m_iCurCamera]->startPriview(vv);
}

void main_desktop::on_cameraButton_clicked()
{
	static int iCnt = 0;
	iCnt++;
	if(m_bCameraState)
	{
		qDebug()<<"Now take picture for camera"<<m_iCurCamera<<" "<< iCnt <<" times"<<endl;
		Mutex::Autolock locker(&mObjectLock);
		status_t rt = m_pDvrs[m_iCurCamera]->takePicture();
        if(0 != rt) {
            frmMessageBox *msg = new frmMessageBox;
			QString QStr = "Take Picture Fail for Video" + QString::number(m_iCurCamera, 10);
            msg->SetMessage(QString(tr(QStr.toStdString().data())), 2);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        } else {
            frmMessageBox *msg = new frmMessageBox;
			QString QStr = "Take Picture success for Video" + QString::number(m_iCurCamera, 10);
            msg->SetMessage(QString(tr(QStr.toStdString().data())), 0);
            QTimer::singleShot(2000, msg, SLOT(close()));
            msg->exec();
        }
	}
}

void main_desktop::on_recordButton_clicked()
{
    m_pRedselDlg->show();
	m_pRedselDlg->UpdateCurCamera(m_iCurCamera);
    this->setHidden(true);	
}

void main_desktop::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth, deskHeight);
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
    m_pCamSelDlg->show();
    this->setHidden(true);	
}

void main_desktop::on_setFirstButton_clicked()
{
    m_pSettingDesktop->show();
	m_pSettingDesktop->UpdateCurCameraState(m_iCurCamera);
    this->setHidden(true);
}

void main_desktop::on_movieButton_clicked()
{
    qDebug() << "open movie";
    this->setHidden(true);
}
void main_desktop::on_reverseLine_repaint()
{
    reverseLinewidget->update();
}


void main_desktop::on_pushButtonHome_clicked()
{
    qDebug() << "open Launcher";
	system("echo 0,0 > /sys/class/disp/disp/attr/fb2ui");
	system("echo Launcher, > /sys/inputFocus/write");
}

void main_desktop::on_pushButton_clicked()
{
    QString PreviewInfo;
    if(m_bPreview)
    {
        PreviewInfo = "打开预览";
        m_pDvrs[m_iCurCamera]->stopPriview();
        m_bPreview = false;

    }
    else
    {
        PreviewInfo = "关闭预览";
        struct view_info vv = {0, 0, 1024, 600};
        m_pDvrs[m_iCurCamera]->startPriview(vv);
        m_bPreview = true;
    }
    ui->pushButton->setText(tr(PreviewInfo.toStdString().data()));
}
