#ifndef REVERSELINE_H
#define REVERSELINE_H

#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include "mylabel.h"
#include "reverseline_setting.h"
namespace Ui {
class ReverseLine;
}

class ReverseLine : public QDialog
{
    Q_OBJECT

public:
    explicit ReverseLine(QWidget *parent = 0);
    ~ReverseLine();
public slots:
    void on_pictureLabel2_clicked();
    void on_pictureLabel1_clicked();
private:
    Ui::ReverseLine *ui;
    myLabel *reverse_setting_label;
    myLabel *rearVision_setting_label;
    ReverseLine_Setting* reverseline_setting;

};

#endif // REVERSELINE_H
