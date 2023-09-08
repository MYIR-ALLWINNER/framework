#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QDirIterator>
#include <QRect>
#include <QProcess>
#include <QThread>
#include "video_player.h"
#if defined(Q_OS_LINUX)
#include "xmetadataretriever.h"
#if defined(Q_OS_LINUX)

#endif
#endif

namespace Ui {
class videoWidget;
}

class videoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit videoWidget(QWidget *parent = 0);
    ~videoWidget();
    void show_file_by_iconview(QFileInfoList file_list);
    void show_file_by_listview(QFileInfoList file_list);
    void gen_shot_picture(QString tempFileName_NoSuffix,QString file_path,QString tempFileName,QString ab_file_path,QPixmap pix,int pos);
    QFileInfoList GetFileList(QString dir_str);
    void show_file();

public slots:
    void play_video(QModelIndex pos);
    void showError(QString filename);
    void add_shot_pic(QPixmap pix,QString file_path,int pos);
    void deleteThread();
private slots:
//    void on_change_viewmode_clicked();
public slots:
    void on_usb_mount();
    void on_usb_umount();

private:
    Ui::videoWidget *ui;
    Video_Player* video_players;
    bool show_model;
    QFileInfoList file_list;

};
class ThumbnailThread: public QThread
{
Q_OBJECT
public:
    ThumbnailThread(QString tempFileName_NoSuffix_arg,QString file_path_arg,QString tempFileName_arg,QString ab_file_path_arg,QPixmap pix_arg,int pos_arg);

private:
    void run();
    QString tempFileName_NoSuffix;
    QString file_path;
    QString tempFileName;
    QString ab_file_path;
    QPixmap shot_pic;
    int pos;
signals:
    void thumbnailFinished(QPixmap shot_pic,QString file_path,int pos);
    void thumbnailFailed(const QString filename);
};
#endif // VIDEOWIDGET_H
