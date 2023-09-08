#ifndef ADAS_H
#define ADAS_H

#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include "mylabel.h"
#include "rear_adas_setting.h"
#include "front_adas_setting.h"
namespace Ui {
class ADAS;
}

class ADAS : public QDialog
{
    Q_OBJECT

public:
    explicit ADAS(QWidget *parent = 0);
    ~ADAS();
signals:
    void hideSettings();
    void unhideSettings_signal();
public slots:
    void on_pictureLabel2_clicked();
    void on_pictureLabel1_clicked();
private:
    Ui::ADAS *ui;
    rear_ADAS_setting* rear_adas_settings;
    front_ADAS_setting* front_adas_settings;
    myLabel* front_ADAS_label;
    myLabel* rear_ADAS_label;
};

#endif // ADAS_H
