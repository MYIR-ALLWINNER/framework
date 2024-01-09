#ifndef REAR_CAMERA_SETTING_H
#define REAR_CAMERA_SETTING_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class Rear_Camera_Setting;
}

class Rear_Camera_Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Rear_Camera_Setting(QWidget *parent = 0);
    ~Rear_Camera_Setting();
public slots:
    void on_returnButton_clicked(bool);
    void on_sureButton_clicked(bool);
    void on_upperButton_clicked(bool);
    void on_downButton_clicked(bool);

private:
    Ui::Rear_Camera_Setting *ui;
    void FormInCenter();
};

#endif // REAR_CAMERA_SETTING_H
