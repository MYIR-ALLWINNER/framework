/*!
 * @file musicplayer.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPixmap>
#include "musicplayer/Header/playlist.h"
#include "common/Header/commonfunction.h"
#include "common/Header/searchfiledialog.h"
#include "xmetadataretriever.h"



extern int autCb_func(int32_t msgType, void *user,void* data,int len);

class MusicInfoThread : public QThread
{
    Q_OBJECT
public:
    explicit MusicInfoThread(QString path,QObject *parent = 0);
    ~MusicInfoThread();
protected:
    virtual void run();
signals:
    void complete(QString,QString,QString,QPixmap);
private:
    QString m_filepath;
    QString m_albumName;
    QString m_musicName;
    QString m_singerName;
    QPixmap m_poster;
    CommonFunction* commonfunc;
};


namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    static MusicPlayer *Instance(QWidget *parent = 0);//create window by this interface
    ~MusicPlayer();
    void initAutPlayer();
    void startPlay();
    void stopPlay();
    void updateDurationInfo(qint64 currentInfo);
    void getMusicInfo(QString path);

	static int autMusicCb_func(int msgType, void* user,void* data,int len);


private slots:
	void on_return_btn_clicked();
	
    void on_preMusicButton_clicked();

    void on_playButton_clicked();

    void on_nextMusicButton_clicked();

    void on_searchButton_clicked();

    void on_playListButton_clicked();

    void on_playOrderButton_clicked();

    void on_setttingButton_clicked();

    void on_pushButton_clicked();

    void on_notifyMusicPlayerToPlay(QList<QFileInfo>,int,int listType);

    void on_notifyMusicPlayerListChanged(QList<QFileInfo>,int listType);

    void timerUpdate();

    void onProgressSliderMoved(int);

    void onProgressSliderReleased();

    void setMusicInfo(QString,QString,QString,QPixmap);

    void on_notifyMusicPlayerAddFile(QString);

    void on_notifyMusicCancelSearch();

    void doMsgCmd(int msgType,void* user,void* data,int len);

signals:
    void msgSignal(int msgType,void* user,void* data,int len);

    void hidePlayList();

    void showPlayList();

    void hideSearchFileDialog();

    void showSearchFileDialog();

protected:
    void focusInEvent(QFocusEvent *e);
private:
    Ui::MusicPlayer *ui;

    static MusicPlayer* self;//this  is for single instance
    explicit MusicPlayer(QWidget *parent = 0);

    CommonFunction* m_commonFunction;
    PlayList *m_pPlayList;
    searchFileDialog *m_pSearchDialog;

    PLAYSTATE m_bPlayState;//ENUM of state
    bool m_bMusicListOpen;//for open is 1;close is 0
    bool m_bSearchDialogOpen;//for open is 1;close is 0

    QList<QFileInfo> m_playList;//this is the list now play
    QList<QFileInfo> m_playList_udisk;//this is the list from udisk
    QList<QFileInfo> m_playList_favorite;//this is the list from favorite file

    QString m_curMusicFilePath;
    int m_curMusicFileCount;

    AUTPlayer* ap;
    qint64 m_totalDuration;
    qint64 m_curDuration;
    QTimer* progressSliderTimer;

    QString m_albumName;
    QString m_musicName;
    QString m_singerName;
    QPixmap m_poster;

    int m_curPlayOrderState;//0:sequences;1:random;2:single one
    int m_nextPlayOrderState;

};

static MusicPlayer *pStaticMusicPlayer=NULL;

#endif // MUSICPLAYER_H
