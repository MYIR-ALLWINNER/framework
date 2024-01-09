#ifndef MIDWINDOW_H
#define MIDWINDOW_H
#include <QObject>

class MidWindow:public QObject
{
    Q_OBJECT
public:
    MidWindow();
    void mount_usb();
    void umount_usb();
    void mount_sdcard();
    void umount_sdcard();
    void on_voice_change(int value);
    void on_video_complete();
signals:
    void usb_insert();
    void usb_delete();
    void sdcard_insert();
    void sdcard_delete();
    void voice_change(int value);
    void video_complete();

};

#endif // MIDWINDOW_H
