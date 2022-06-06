#ifndef FRONT_CAMERA_SETTING_H
#define FRONT_CAMERA_SETTING_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class Front_camera_setting;
}

class Front_camera_setting : public QDialog
{
    Q_OBJECT

public:
    explicit Front_camera_setting(QWidget *parent = 0);
    ~Front_camera_setting();
public slots:
    void on_returnButton_clicked();
    void on_sureButton_clicked();
    void on_upperButton_clicked();
    void on_downButton_clicked();
signals:
    void unHideSettings();
private:
    Ui::Front_camera_setting *ui;
    void FormInCenter();
};

#endif // FRONT_CAMERA_SETTING_H
