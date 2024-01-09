/*!
 * @file videoplayer.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QTimer>
#include "videoplayer/Header/videoplaylist.h"
#include "common/Header/commonfunction.h"
#include "common/Header/searchfiledialog.h"
#include "xmetadataretriever.h"


namespace Ui {
class VideoPlayer;
}
extern int autCb_func(int msgType, void *user,void* data,int len);

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    static VideoPlayer *Instance(QWidget *parent = 0);//create window by this interface

    ~VideoPlayer();

    void initAutPlayer();

    void startPlay();

    void updateDurationInfo(qint64 currentInfo);

    static int autVideoCb_func(int msgType, void* user,void* data,int len);

    void getNumOfAudioAndSubtitle(int&,int&);

private slots:
    void on_return_btn_clicked();

    void on_fullScreenButton_clicked();

    void on_preVideoButton_clicked();

    void on_subtitleListButton_clicked();

    void on_playListButton_clicked();

    void on_subtitleSelectButton_clicked();

    void on_searchButton_clicked();

    void on_playButton_clicked();

    void on_nextVideoButton_clicked();

    void on_notifyVideoPlayerToPlay(QList<QFileInfo>,int);

    void on_notifyVideoPlayerListChanged(QList<QFileInfo>);

    void timerUpdate();

    void onProgressSliderMoved(int);

    void onProgressSliderReleased();

    void on_UnFullscreenButton_clicked();

    void setSubtitleNum(QAction*);

    void setAudioNum(QAction*);

    void stopPlay();

    void doMsgCmd(int msgType,void* user,void* data,int len);

    void on_notifyVideoPlayerAddFile(QString strpath);

    void on_notifyVideoCancelSearch();

signals:
    void msgSignal(int msgType,void* user,void* data,int len);

    void hideSearchFileDialog();

    void showSearchFileDialog();

    void hidePlayList();

    void showPlayList();

private:

    Ui::VideoPlayer *ui;
    explicit VideoPlayer(QWidget *parent = 0);
    static VideoPlayer* self;//this  is for single instance

    CommonFunction* m_commonFunction;
    searchFileDialog *m_pSearchDialog;
    bool m_bSearchDialogOpen;//for open is 1;close is 0

    VideoPlayList* m_pVideoPlayList;
    bool m_bVideoListOpen;//for open is 1;close is 0

    QList<QFileInfo> m_playList;
    QString m_curVideoFilePath;
    QString m_curVideoFileName;
    QString str_SelectPath;
    int m_curVideoFileCount;

    AUTPlayer* ap;
    qint64 m_totalDuration;
    qint64 m_curDuration;
    qint64 m_pretime;
    QTimer* progressSliderTimer;
    PLAYSTATE m_bPlayState;//ENUM of state

    int m_subtitleNow;
    int m_audioNow;

};

static VideoPlayer *pStaticVideoPlayer=NULL;

#endif // VIDEOPLAYER_H
