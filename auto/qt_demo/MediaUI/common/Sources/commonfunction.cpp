/*!
 * @file src/commonfunction.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "common/Header/commonfunction.h"
#include "common/Header/frmmessagebox.h"
#include <QDebug>
#include "videoplayer/Header/videoplayer.h"
#include "musicplayer/Header/musicplayer.h"
#include "common/Header/mediahome.h"
#include <QTextCodec>
/**************************************
Function:
Description:
***************************************/
CommonFunction::CommonFunction()
{

}

/**************************************
Function:
Description:
***************************************/
bool CommonFunction::fileExistOrNot(QString path)
{
    if(path.isEmpty()){
        qDebug()<<"path is empty, please check";
        return false;
    }
    if((access((char*)path.toLatin1().data(),F_OK)) != -1){
        qDebug()<<"file exist";
        return true;
    }else{
        qDebug()<<"this file is not exist";
        return false;
    }
}

/**************************************
Function:
Description:
***************************************/
bool CommonFunction::video_support_or_not(QWidget* parent_widget,QString path)
{
    AUTPlayer *ap = NULL;
    if(ap == NULL){
        qDebug()<<"video_support_or_not"<<path;
        ap = new AUTPlayer();
        int ret = ap->setUrl((char*)path.toLatin1().data());
        if (ret < 0){
            qDebug()<<"setUrl is error-------------------";
            frmMessageBox *msg = new frmMessageBox(parent_widget);
            msg->SetMessage(QString("媒体不支持！"),0);
            msg->exec();
            if(ap != NULL){
                delete ap;
                 ap = NULL;
            }
            return false;
        }else{
            if(ap != NULL){
                delete ap;
                 ap = NULL;
            }
            qDebug()<<"this video is support";
            return true;
        }
    }
    return true;
}

/**************************************
Function:
Description:
***************************************/
QString CommonFunction::print_info(unsigned char tmp[],int tmp2)
{
    //tmp
    QString str = "";
    for(int i = 0;i < tmp2 && i < 64;i++)
    {
        if(tmp[i] == 0)
            continue;
        str += tmp[i];
    }
    return QObject::trUtf8(str.toLatin1().data());
}



/**************************************
Function:
Description:
***************************************/
QString getTimeStr(qint64 x,qint64 range)
{
    QString tStr = "";
    QString format = "mm:ss";
    if(range >  3600) format = "hh:mm:ss";

    QTime currentTime((x / 3600) % 60, (x / 60) % 60, \
                      x % 60, (x * 1000) % 1000);


    tStr = currentTime.toString(format);

    return tStr;
}

/**************************************
Function:
Description:
***************************************/
int autCb_func(int msgType, void *user,void* data,int len)
{

    if(pGlobalMediaHome->distype==1){
        //emit pStaticVideoPlayer->msgSignal(msgType,user,data,len);
    }
    else if(pGlobalMediaHome->distype==2){
        //emit pStaticMusicPlayer->msgSignal(msgType,user,data,len);
    }


}

/**************************************
Function:
Description:
***************************************/
QString UTF82GBK(const QString &inStr)
{

    QString str;

    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    str = utf8->toUnicode(inStr.toLocal8Bit());

    qDebug()<<"UTF82GBK " << str;

    QString utf2gbk = QString(gbk->fromUnicode(str));

    qDebug()<<"UTF82GBK " << utf2gbk;

    return utf2gbk;
}
