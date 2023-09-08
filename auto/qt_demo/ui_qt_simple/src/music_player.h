#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <QDialog>
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
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTableWidget>
#if defined(Q_OS_LINUX)
#define USE_AUTPLAYER 1
#define AGEING_TEST_MUSIC 1
#endif
#if defined(USE_AUTPLAYER)
#include "AutPlayer.h"
#include "outputCtrl.h"
#include "mediaInfo.h"
#include "xmetadataretriever.h"
using namespace android;
#endif
namespace Ui {
class Music_Player;
}
struct myMediaInfo{
    long long filesize;
    int bitrate;
    bool bSeekable;
    QString compser_str;
    QString artist_str;
    QString writer_str;
    QString albumArtist_str;
};
class Music_Player : public QDialog
{
    Q_OBJECT

public:
    explicit Music_Player(QWidget *parent = 0);
    ~Music_Player();
    void FormInCenter();
    void show_title();
    void setMusicInfo(QFileInfo);
    void play_video(QFileInfo);
    void clean_window_for_other_music();
private slots:
    void on_preMovieButton_clicked();

    void on_nextMovieButton_clicked();

    void on_playButton_clicked();

    void on_muteButton_clicked();

    void on_btnMenu_Min_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Close_clicked();

    void durationChanged(qint64 duration);

    void positionChanged(qint64 progress);

    void updateDurationInfo(qint64 currentInfo);

    void setVolume(int);

    void timerUpdate();

    void on_timeout_mouserMoveTime();

    void seek(int seconds);

    void on_video_complete();

    void on_otherInfo_clicked();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event) ;
    QTableWidget* tablewidget;
    bool isOpen;
    void on_mouse_active();
    QTimer *mouseMoveTime;
private:
    Ui::Music_Player *ui;
    int current_video;
    QString current_path;
    bool isMuted;
    bool isPlaying;
    int seekto_is_ok;
    qint64 duration;
    QTimer *timer;
    QDir dir;
    QFileInfoList file_list;
    QFileInfoList all_file_list;
    #if defined(USE_AUTPLAYER)
    AUTPlayer *ap;
    XRetriever* demoRetriver;
    #else
    QVideoWidget* my_video_widget;
    QMediaPlayer *player;
    #endif
    int astatus;

    QFileInfoList GetFileList(QDir dir);
    struct myMediaInfo mediaInfo;
};

#endif // MUSIC_PLAYER_H
