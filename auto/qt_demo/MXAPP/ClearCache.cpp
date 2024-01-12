#include "ClearCache.h"
#include <QDebug>
ClearCache::ClearCache(QObject *parent) : QObject(parent)
{
    t1=new QTimer;
    connect(t1,&QTimer::timeout,this,&ClearCache::clear_memory);
    t1->start(10000);
}

void ClearCache::clear_memory()
{
    if(last_time.secsTo(QDateTime::currentDateTime()) >= 3600){
        system("echo 3 > /proc/sys/vm/drop_caches");
		qDebug()<<"echo 3 > /proc/sys/vm/drop_caches";
        last_time=QDateTime::currentDateTime();
    }
}
