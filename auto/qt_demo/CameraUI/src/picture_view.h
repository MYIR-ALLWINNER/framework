#ifndef PICTURE_VIEW_H
#define PICTURE_VIEW_H

#include <QDialog>
#include <QDebug>
#include <QModelIndex>
#include <QDirIterator>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QScrollArea>
#include <QBoxLayout>
#include "cprojectionpicture.h"
#include <QFileInfo>
namespace Ui {
class Picture_view;
}

class Picture_view : public QDialog
{
    Q_OBJECT

public:
    explicit Picture_view(QWidget *parent = 0);
    ~Picture_view();
    void show_image(QFileInfo fileInfo_to_show);

private slots:
    void on_btnMenu_Min_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Close_clicked();

    void on_prePicButton_clicked();

    void on_nextPicButton_clicked();

    void on_largerButton_clicked();

    void on_smallerButton_clicked();

private:
    Ui::Picture_view *ui;

    CProjectionPicture* pic_view;
    int current_pic;
    QString current_path;
    QDir dir;
    QFileInfoList file_list;
    QFileInfoList all_file_list;
    QFileInfoList GetFileList(QDir dir);
    void show_title();
    void FormInCenter();

};

#endif // PICTURE_VIEW_H
