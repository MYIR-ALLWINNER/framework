#ifndef SLAVE_PICTUREWIDGET_H
#define SLAVE_PICTUREWIDGET_H

#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QRect>
#include <QListWidgetItem>
#include <QModelIndex>
#include "picture_view.h"


namespace Ui {
class slave_PictureWidget;
}

class slave_PictureWidget : public QDialog
{
    Q_OBJECT

public:
    explicit slave_PictureWidget(QWidget *parent = 0);
    ~slave_PictureWidget();


public slots:
    void show_big_picture(QModelIndex);

private:
    Ui::slave_PictureWidget *ui;
    Picture_view *picture_views;
};

#endif // SLAVE_PICTUREWIDGET_H
