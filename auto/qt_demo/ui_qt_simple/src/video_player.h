#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include <QDialog>
#include <QDebug>
#include <QMediaPlayer>
#include "video_widgets.h"
#include <QMediaObject>
#include <QPainter>
#include <QTimer>
#include <QDirIterator>
#include <QFileInfoList>
#include <QDir>
#include <QThread>
#include <QLabel>
#include <QMenu>
#include <QAction>
#if defined(Q_OS_LINUX)
#define USE_AUTPLAYER 1
#endif
#if defined(USE_AUTPLAYER)
#include "AutPlayer.h"
#include "outputCtrl.h"
#include "mediaInfo.h"
using namespace android;
#endif
static const int ASTATUS_STOPPED   = 0;
static const int ASTATUS_PREPARING = 1;
static const int ASTATUS_PREPARED  = 2;
static const int ASTATUS_PLAYING   = 3;
static const int ASTATUS_PAUSED    = 4;
static const int ASTATUS_SEEKING   = 5;
#define AGEING_TEST_VIDEO 1
namespace Ui {
class Video_Player;
}

class Video_Player : public QDialog
{
    Q_OBJECT

public:
    explicit Video_Player(QWidget *parent = 0);
    ~Video_Player();
    QLabel* subtitle_label;
public slots:
    void seek(int seconds);
    void play_video(QFileInfo);

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event) ;

    void on_mouse_active();
    QTimer *mouseMoveTime;
private slots:
    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_muteButton_clicked();

    void on_btnMenu_Min_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Close_clicked();

    void durationChanged(qint64 duration);

    void positionChanged(qint64 progress);

    void updateDurationInfo(qint64 currentInfo);

    void setVolume(int);

    void timerUpdate();

    void on_preMovieButton_clicked();

    void on_fastBackButton_clicked();

    void on_fastFrontButton_clicked();

    void on_nextMovieButton_clicked();

    void on_timeout_mouserMoveTime();

    void on_video_complete();

    void find_correspond_subtitle_file(QFileInfo);

    void getAllSubtitle(int&);

    void getAllAudio(int&);

    void setSubtitleNum(QAction*);

    void setAudioNum(QAction*);
protected:
    void paintEvent(QPaintEvent *event);
public:
    Ui::Video_Player *ui;
    int current_video;
    QString current_path;
    bool isMuted;
    bool isPlaying;
    int seekto_is_ok;
    qint64 duration;
    QTimer *timer;
    QDir dir;
    QMenu *m_menu;
    QAction *m_subtitleSelect;
    QAction *m_audioFileSelect;
//    QDirIterator* m_DirIterator;
    QFileInfoList file_list;
    QFileInfoList all_file_list;

//    QMediaPlayer::State playerState;
//    video_widgets* my_video_widget;
    #if defined(USE_AUTPLAYER)
        AUTPlayer *ap;
    #else
        QVideoWidget* my_video_widget;
        QMediaPlayer *player;
    #endif
        int astatus;
     int isSeekable;
    QFileInfoList GetFileList(QDir dir);
    QFileInfoList GetAllFileList(QDir dir);
    QMap<QString,QFileInfo> get_subtitle_files(QFileInfo fileInfo);
    void show_subtitle_file_name(QMap<QString,QFileInfo> tmp_map);

private:
    void show_title();
    void FormInCenter();

};

#endif // VIDEO_PLAYER_H
