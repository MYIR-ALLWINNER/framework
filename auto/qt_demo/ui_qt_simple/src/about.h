#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QTime>
#if defined(Q_OS_LINUX)
#include "sdklog.h"
#include "Fat.h"
#include <unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#define PATH_SDCARD  "/mnt/sdcard/mmcblk1p1/"
#define PATH_SD_DEV  "/dev/mmcblk1p1"
#define PATH_USB "/mnt/usb/sda4/"
#define PATH_USB_DEV "/dev/sda4/"

#endif
namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
public slots:
    void on_formatButton_clicked();
    void set_pro_value();
private slots:
    void on_logLevelComboBox_currentIndexChanged(int index);

private:
    Ui::About *ui;
    int test;//for test
    QTimer *timer;
    #if defined(Q_OS_LINUX)
        Fat *pfat;
    #endif
    int dev_type;
};

#endif // ABOUT_H
