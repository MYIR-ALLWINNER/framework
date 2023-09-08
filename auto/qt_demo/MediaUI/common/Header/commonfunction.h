/*!
 * @file src/commonfunction.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H
#include <QString>
#include <QWidget>
#include <QDebug>
//for linux operation
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//for media
#include "AutPlayer.h"
#include "outputCtrl.h"
#include "mediaInfo.h"
using namespace android;

enum PLAYSTATE{
    PLAYING = 1,
    PAUSEED = 2,
    STOPPED = 3,
    PREPARED = 4,
    PREPARING = 5,
    SEEKING = 6
};

class CommonFunction
{
public:
    CommonFunction();
    bool fileExistOrNot(QString path);
    bool video_support_or_not(QWidget* parent_widget,QString path);
    QString print_info(unsigned char tmp[],int tmp2);
    int autCb_func(int32_t msgType, void *user,void* data,int len);
};

QString getTimeStr(qint64 x,qint64 range);
int autCb_func(int msgType, void *user,void* data,int len);
QString UTF82GBK(const QString &inStr);

#endif // COMMONFUNCTION_H
