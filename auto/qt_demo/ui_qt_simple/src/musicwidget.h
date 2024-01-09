#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QDialog>
#include "music_player.h"
#include <QDebug>
#include <QListWidget>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QDirIterator>
#include <QRect>
#if defined(Q_OS_LINUX)
#include "xmetadataretriever.h"
#endif
namespace Ui {
class MusicWidget;
}

class MusicWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MusicWidget(QWidget *parent = 0);
    ~MusicWidget();
    void show_file_by_iconview(QFileInfoList file_list);
    void show_file_by_listview(QFileInfoList file_list);
    QFileInfoList GetFileList(QString dir_str);
    void show_file();
    void getMusicInfo(QFileInfo file_path_to_op);
private slots:
    void on_listWidget_clicked(const QModelIndex &index);

public slots:
    void on_usb_mount();
    void on_usb_umount();
private:
    Ui::MusicWidget *ui;
    Music_Player* music_player;
    bool show_model;
    QFileInfoList file_list;
#if defined(Q_OS_LINUX)
    XRetriever* demoRetriver;
#endif
};

#endif // MUSICWIDGET_H
