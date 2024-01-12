#ifndef CLEARCACHE_H
#define CLEARCACHE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
class ClearCache : public QObject
{
    Q_OBJECT
public:
    explicit ClearCache(QObject *parent = nullptr);
    QTimer *t1;
    QDateTime last_time = QDateTime::currentDateTime();
    void clear_memory();

};

#endif // CLEARCACHE_H
