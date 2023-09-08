#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include "rear_camera_setting.h"
#include "front_camera_setting.h"
//#include "settings.h"
//#include "ui_settings.h"

namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();

public slots:
    void on_rearButton_clicked(bool);
    void on_frontButton_clicked(bool);

private:
    Ui::Preview *ui;
    Rear_Camera_Setting *rear_camera_setting;
    Front_camera_setting *front_camera_setting;
};

#endif // PREVIEW_H
