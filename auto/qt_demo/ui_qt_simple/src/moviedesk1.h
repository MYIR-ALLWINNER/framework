#ifndef MOVIEDESK1_H
#define MOVIEDESK1_H

#include <QDialog>
#include <QDesktopWidget>
#include<QFileDialog>
//#include "editwidget.h"
#include "videowidget.h"
#include "picturewidget.h"
#include "settings.h"
#include "slave_picturewidget.h"
#include "slave_videowidget.h"
#include "video_player.h"
#include "music_player.h"
#include "musicwidget.h"
#include "picture_view.h"
#if defined(Q_OS_LINUX)
#define USE_AUTPLAYER 1
#endif
#if defined(USE_AUTPLAYER)
#include "AutPlayer.h"
#include "outputCtrl.h"
#include "mediaInfo.h"
using namespace android;
#endif
namespace Ui {
class movieDesk1;
}

class movieDesk1 : public QDialog
{
    Q_OBJECT

public:
    explicit movieDesk1(QWidget *parent = 0);
    ~movieDesk1();
    void FormInCenter();
public slots:
    void on_returnButton_clicked();
    void on_mainCameraButton_clicked();
    void on_viceButton_clicked();
    void deal_fileDialog(int a);
    void deal_fileDialog1();
public:
    Ui::movieDesk1 *ui;
    int cur_index;
private:
//    editWidget* editwidget;
    videoWidget* videowidget;
    pictureWidget* picturewidget;
    slave_PictureWidget* slave_picturewidget;
    slave_VideoWidget* slave_videowidget;
    QFileDialog *fileDialog;
    Video_Player* player;
    Music_Player* musicPlayer;
    MusicWidget* musicwidget;
    Picture_view* pic_view;
    bool isMainCamera;
    void on_usb_mount();
    void on_usb_umount();
public slots:
    void open_file(QString);
signals:
private slots:
    void on_videoButton_clicked();
    void on_picButton_clicked();
    void on_scanButton_clicked();
    void on_musicButton_clicked();
};


#endif // MOVIEDESK1_H
