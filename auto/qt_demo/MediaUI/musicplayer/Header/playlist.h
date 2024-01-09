/*!
 * @file playlist.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QThread>
#include <QScrollBar>
#include <QDateTime>
#include <QTimer>
#include <QFileInfo>

#include "common/Header/waittingwidget.h"

namespace Ui {
class PlayList;
}

class ScanMusicFileThread : public QThread
{
    Q_OBJECT
public:
    explicit ScanMusicFileThread(QObject *parent = 0);
    ~ScanMusicFileThread();
protected:
    virtual void run();
signals:
    void scanComplete(QList<QFileInfo>*);
private:
    QList<QFileInfo>* fileInfoList;
};

class waittingWidgetThread : public QThread
{
    Q_OBJECT
public:
    explicit waittingWidgetThread(QObject *parent = 0);
    ~waittingWidgetThread();
protected:
    virtual void run();
private:
    WaittingWidget* m_pWaittingWidget;
};
class PlayList : public QWidget
{
    Q_OBJECT

public:
    static PlayList *Instance(QWidget *parent = 0);//create window by this interface
    ~PlayList();
public slots:
    void hidePlayList();

    void showPlayList();

    void updateStatusLabel();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void stopMovie();

    void notifyMusicPlayerToPlay(QList<QFileInfo> playlists, int cnt,int listType);

    void notifyMusicPlayerListChanged(QList<QFileInfo> playlists,int listType);

private slots:
    void on_UsbListButton_clicked();

    void on_favoriteListButton_clicked();

    void onScanComplete(QList<QFileInfo>* fileInfoList);

    void onBtnClicked();

    void on_refreshButton_clicked();

    void on_clearButton_clicked();

    void on_prePageButton_clicked();

    void on_notifyMusicListAddFile(QString);

private:
    static PlayList* self;
    explicit PlayList(QWidget *parent = 0);
    QList<QFileInfo> m_PlayList_Udisk;
    QList<QFileInfo> m_PlayList_Favorite;
    void scanMusicFileFromUdisk();
    void showWaittingDialog();
    Ui::PlayList *ui;

    QScrollBar *m_scrollBarV;
    QScrollBar *m_scrollBarV_2;

};

#endif // PLAYLIST_H
