#include "qmlprocess.h"

#include <QProcess>
#include <QDebug>
#include <QString>
#include <QByteArray>

using namespace  MQP;

Private::Private(QmlProcess *parent)
    :QProcess(parent),q(parent)
{
    connect(this, SIGNAL(started()), q, SIGNAL(started()));
    connect(this, SIGNAL(finished()), q, SIGNAL(finished()));

    connect(this, SIGNAL(readyReadStandardOutput()), q, SIGNAL(readyReadStandardOutput()));
    connect(this, SIGNAL(readyReadStandardError()), q, SIGNAL(readyReadStandardError()));

}

QmlProcess::QmlProcess(QObject *parent)
    :QObject(parent)
    ,d(new Private(this))
{
    d->shell = "bash";
}

QmlProcess::~QmlProcess(){

}

const QString &QmlProcess::shell() const
{
    return d->shell;
}

void QmlProcess::setShell(const QString &shell){
    if(shell == d->shell) return;
    d->shell = shell;
    emit shellChanged(d->shell);
}
const QString &QmlProcess::command() const
{
    return d->command;
}

void QmlProcess::setCommand(const QString &command)
{
    if (command == d->command) return;
    d->command = command;
    emit commandChanged(d->command);
}

void QmlProcess::start()
{
    d->start(d->shell);

    d->write(d->command.toUtf8().constData());
    d->closeWriteChannel();

    //d->waitForStarted();
    //d->waitForFinished();

    /*
    sh.waitForFinished();
    QByteArray output = sh.readAll();
    sh.close();
    d->start(d->program, d->arguments);
    */
}

void QmlProcess::terminate()
{
    d->terminate();
}

void QmlProcess::kill()
{
    d->kill();
}

QString QmlProcess::readAllStandardError()
{
    QByteArray errData = d->readAllStandardError();
    QString errStr =  QString(errData);

    return errStr;
}

QString QmlProcess::readAllStandardOutput()
{
    QByteArray outData = d->readAllStandardOutput();
    QString outStr = QString(outData);
//    qDebug() << "readAllStandOutput: " << outStr;

    return outStr;
}
