/*!
 * @file searchfiledialog.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef SEARCHFILEDIALOG_H
#define SEARCHFILEDIALOG_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class searchFileDialog;
}

class searchFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchFileDialog(int Type, QWidget *parent = 0);
    ~searchFileDialog();

    void showD();

public slots:
    void onGetFileName();

    void onCancel();
signals:
    void notifyMusicPlayerAddFile(QString);

    void notifyVideoPlayerAddFile(QString);

    void notifyGalleryAddFile(QString);

	void notifyMusicCancelSearch();

	void notifyVideoCancelSearch();

	void notifyGalleryCancelSearch();


private:
    void createFileDialog();

    Ui::searchFileDialog *ui;

    QFileDialog *m_pFileDialog;

    int m_FileType;//0: musicplayer;1:videoplayer;2:gallery
    QStringList m_filter;
    QString m_Path;
};

#endif // SEARCHFILEDIALOG_H
