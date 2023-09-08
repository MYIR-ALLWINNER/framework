void on_btnMirror_clicked();
#ifndef PMMAIN_H
#define PMMAIN_H

#include <QWidget>
#include "customwidget.h"
#include "help.h"
#include <QTimer>
#include<QThread>
#include<QDebug>
#include "connectmsg.h"
#include "msgq.h"
#include <QThread>
#include <QMouseEvent>
#include "failprompt.h"
#include "dbusmirrorclient.h"
namespace Ui {
class pmMain;
}
#if 0
typedef struct pmMsg{
   int msg;
   int val;
}pmMsg_t;

class bgPhoneMsghandleThread : public QThread  ///,public IECCallback
{
        Q_OBJECT
signals:
        void bgnotify(int msg,int val);  //
public:
        msgQ_t EconMsgQID;
        int mMsgQinit;
        int mMsgQerrcnt;
        int initEcmsgq(){
            mMsgQerrcnt =0;
            int ret = msgQCreateA(&EconMsgQID,ECON_MSGQ_NAME,10,sizeof(EconMsg_t),0);
            if(ret < 0 )
               mMsgQinit =0;
            else
               mMsgQinit =1;
            return ret;

        }
        static void  mirror_signal_handler (int type,int val,char *arg,void* pdat){
             EconMsg_t evt;
             bgPhoneMsghandleThread *pthis=(bgPhoneMsghandleThread *)pdat;
             evt.msg= type;
             evt.val = val;
             printf("mirror_signal_handler : msg= %d val= %d\r\n", type, val);
             int ret = msgQSend(pthis->EconMsgQID, (char * )&evt,sizeof(evt),1);
        }

        bgPhoneMsghandleThread(QObject *parent = 0): QThread(parent)
        {
            //pbgPhoneThis=this;
            initEcmsgq();
            cMirrorClientInit(this);
            cMirrorClientRegSingalHandl((void* )mirror_signal_handler);

        }
        void bg_handlestart()
        {
               start(HighestPriority);
        }
       // static bgPhoneMsghandleThread* pbgPhoneThis;

protected:
    void run()
        {
            //need a queue pop
            int ret;
            EconMsg_t evt;
            while(1){
                if(mMsgQinit == 0)
                {
                    QThread:msleep(300);
                    initEcmsgq();
                    continue;
                }
                int prio;
                ret = msgQReceive(EconMsgQID, (char *)&evt, sizeof(evt),(int)&prio);

                if(ret > 0)
                {
                    printf("msgQReceive : msg= %d val= %d\r\n",evt.msg,evt.val);
                    emit bgnotify(evt.msg,evt.val);
                }else
                {
                    mMsgQerrcnt++;
                    if(mMsgQerrcnt>5)
                        mMsgQinit =0;
                }

            }
        }
};
#endif
class bgPhoneMsghandleThread : public QThread  ///,public IECCallback
{
        Q_OBJECT
signals:
        void bgnotify(int msg,int val);  //
public:

        volatile bool  mirror_clientinit=false;
        static void  mirror_signal_handler (int type,int val,char *arg,void* pdat){

             bgPhoneMsghandleThread *pthis=(bgPhoneMsghandleThread *)pdat;
             printf("mirror_signal_handler : msg= %d val= %d\r\n", type, val);
             pthis->bgnotify(type, val);
        }
        int mirrorcom_client_init()
        {
            int ret;

            if(!mirror_clientinit)
            {
                ret=cMirrorClientInit(this);
                cMirrorClientRegSingalHandl((void* )mirror_signal_handler);

                if(ret>=0)
                   mirror_clientinit = true;
                return 1;
            }
            return 0;
        }

        int dbusrpc_mirror_set_cmd( int in_arg1, int in_arg2, int in_arg3, int in_arg4,  int *out_arg2)
        {
            int cnt=5;
            while(cnt--){
                if(!mirror_clientinit)
                    QThread::msleep(100);
                else
                    break;
            }
            if(!mirror_clientinit)
                return -1;

           int ret =cMirrorClientSetCmd( in_arg1, in_arg2, in_arg3,in_arg4, out_arg2);
            if(ret <0)
            {
                if(ret == -2)
                {
                    printf("dbus lost need reconnect %d \r\n",mirror_clientinit);
                    if(mirror_clientinit)
                        mirror_clientinit = false;

                }
            }
            return ret;

        }
        bgPhoneMsghandleThread(QObject *parent = 0): QThread(parent)
        {
            mirror_clientinit=false;
            mirrorcom_client_init();
        }
        void bg_handlestart()
        {
               start(HighestPriority);
        }

protected:
    void run()
        {
            while(1){
                    int ret = mirrorcom_client_init();
                    if(ret ==1){
                        int out;
                        ret = dbusrpc_mirror_set_cmd(CMD_SYNC_PHONE_STAT, 0, 0,0/* 0 up;1 down;2 move*/, &out);
                        if(ret>=0){
                            emit bgnotify(ON_SyncPhoneStat, out);
                        }
                    }
                    usleep(500000);
            }
        }
};
class pmMain : public CustomWidget
{
    Q_OBJECT

public:
    static pmMain* getInstance(QWidget *parent = 0);
    static void release();

    ~pmMain();
    bgPhoneMsghandleThread mbgthread;
signals:
    void quitPmconnect();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void on_btnFloat_clicked();

    void on_btnBack_clicked();

    void on_btnYL_clicked();

    void on_btnQuit_clicked();
    void on_btnMirror_clicked();
    void on_btnFloat_pressed();

    void on_btnFloat_released();

public slots:
    void OnNotify(int msg,int val);
    void showPhoneMachineConnect(void);
    void closePhoneMachineConnect(void);
    void hideCurrentWidget();
    void showMainWidget();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::pmMain *ui;
    Help* help;
    FailPrompt *failPrompt;
    int connectstatus;
    bool mirrorstate;
    int mPhoneModeType;
    bool mFloatBtnSubShow;
    QTimer* welcomeTimer;

    bool btnIsPressed;
    bool btnMoved;

    static pmMain *mAPP_instance;
    explicit pmMain(QWidget *parent);
};

#endif // PMMAIN_H
