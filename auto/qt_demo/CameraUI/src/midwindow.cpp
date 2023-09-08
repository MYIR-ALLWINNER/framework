#include "midwindow.h"
#include <QDebug>
#include "frmmessagebox.h"
#include <QTimer>
MidWindow::MidWindow()
{

}
void MidWindow::mount_usb()
{
    qDebug()<<"call midwindow";
    frmMessageBox *msg=new frmMessageBox(0);
    msg->SetMessage(QString(tr("usb is insert!")),0);
    QTimer::singleShot(2000, msg, SLOT(close()));
    msg->exec();
    emit usb_insert();

}
void MidWindow::umount_usb()
{
    qDebug()<<"call midwindow";
    frmMessageBox *msg=new frmMessageBox(0);
    msg->SetMessage(QString(tr("usb is out!")),0);
    QTimer::singleShot(2000, msg, SLOT(close()));
    msg->exec();
    emit usb_delete();
}
void MidWindow::mount_sdcard()
{
    emit sdcard_insert();
}
void MidWindow::umount_sdcard()
{
    emit sdcard_delete();
}
void MidWindow::on_voice_change(int value)
{
    qDebug()<<"midwindow get voice change";
    emit voice_change(value);
}
void MidWindow::on_video_complete()
{
    qDebug()<<"midwindow get video complete";
    emit video_complete();
}
