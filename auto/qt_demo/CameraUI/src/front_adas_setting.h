#ifndef FRONT_ADAS_SETTING_H
#define FRONT_ADAS_SETTING_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class front_ADAS_setting;
}

class front_ADAS_setting : public QDialog
{
    Q_OBJECT

public:
    explicit front_ADAS_setting(QWidget *parent = 0);
    ~front_ADAS_setting();
public slots:
    void on_nextButton_clicked();
    void on_returnButton_clicked();
    void change_line_value(int value);
signals:
    void unHideSettings();
private:
    Ui::front_ADAS_setting *ui;
    int horizontal_values,vertical_values;
    int model;
    void FormInCenter();
};

#endif // FRONT_ADAS_SETTING_H
