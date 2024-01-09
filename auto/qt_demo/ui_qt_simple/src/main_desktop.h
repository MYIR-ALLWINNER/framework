#ifndef MAIN_DESKTOP_H
#define MAIN_DESKTOP_H

#include <QWidget>
#include <QDebug>
#include <QPixmap>
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <QPalette>
#include <QPixmap>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include "setfirst.h"
#include "dashboard.h"
#include "moviedesk1.h"
#include "reverselinewidget.h"
#define os_test Q_OS_LINUX

#if defined(Q_OS_LINUX)
#define PATH_SDCARD  "/mnt/sdcard/mmcblk1p1/"
#define PATH_SD_DEV  "/dev/mmcblk1p1"
#define HAVA_TWO_CAMERA 1  //While move to cfg
#define CAMERA_FONT 0  //While move to cfg
#define CAMERA_BACK 1 //While move to cfg
#define LOG_BUF_SIZE	1024
#define VIEW_WEITH 1024
#define VIEW_HEIGHT 600
#define TEST_CAMERA_ID 0
#define CAMERA_TEST 1
#define ANTHOR_CAMERA 1
#define  Double_Camera_Test 0;

#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>

#include "hwdisp2.h"
#include "aw_ini_parser.h"
#include <sdklog.h>
#include "CameraDebug.h"
#include "hwdisp2.h"

#include "V4L2CameraDevice2.h"
#include "CallbackNotifier.h"
#include "PreviewWindow.h"
#include "CameraHardware2.h"
#include "audio_hal.h"
#ifdef REC_ENCODE
#include "awrecorder.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/time.h>
#ifndef CDX_V27
#include "log.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vencoder.h"
#include "CdxMuxer.h"
#include <time.h>

#include "Rtc.h"
#include "StorageManager.h"
#include "DvrFactory.h"
#include "CameraFileCfg.h"
#include <sys/socket.h>
#include <sys/un.h>
#include "Fat.h"
#include "DebugLevelThread.h"
#include "DvrRecordManager.h"
using namespace android;

#define RECORD_TEST 1
#define AUDIO_TEST

#include "NetlinkManager.h"
#include "NetlinkHandler.h"
#include "NetlinkEvent.h"
void testaut_event_cb_func(NetlinkEvent *evt,void *usrdata);
extern "C" int aut_adb_main(int argc, char **argv);

#endif
namespace Ui {
class main_desktop;
}

class main_desktop : public QWidget
{
    Q_OBJECT

public:
    explicit main_desktop(QWidget *parent = 0);
    ~main_desktop();
protected:
    void paintEvent(QPaintEvent *event);
private://用于检测是否有动作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event) ;

    void on_mouse_active();
private:
    Ui::main_desktop *ui;
    bool cameraState;//camera state：true=front,false=rear
    bool isRecording;
    QTimer *mouseMoveTime;
    QPixmap screenshot_pic;
    void accept();
public slots:
    void timerUpdate(void);
//    void cameraChange();
public slots:
    void on_mouse_no_active_10_second();
    void on_main_desktop_disvisible();
    void on_main_desktop_visible();
    void on_pushButton_clicked();

public slots:
    void on_recordButton_clicked();

    void on_camera_change_Button_clicked();

    void on_setFirstButton_clicked();

    void on_movieButton_clicked();

    void on_cameraButton_clicked();

    void on_reverseLine_repaint();

    void on_sdcard_delete();

    void on_sdcard_insert();

private:
    SetFirst *setting_desktop;
//    dashBoard *dashboards;
    movieDesk1 *moviedesk;
    reverseLineWidget* reverseLinewidget;

private:
    void setButtonVisible();
    void setButtonDisvisible();
    void FormInCenter();
public:


    int  startAllCameraWithPreview(int camera_no /* nouse now*/);
    int cur_camera;
    void videoshow()
    {
        //on_pushButton_play_clicked();
        startAllCameraWithPreview(0);
    }
#ifdef AUTEVENT
signals:
    void usb_is_mount();
    void usb_is_umount();
//    static void  testaut_event_cb_func1(NetlinkEvent *evt,void *usrdata);
#endif
    #if defined(Q_OS_LINUX)
    Mutex                           mObjectLock;
    #endif
    void startRecord();
    void stopRecord(){
        //on_pushButton_stop_clicked();
    }

};

#endif // MAIN_DESKTOP_H

