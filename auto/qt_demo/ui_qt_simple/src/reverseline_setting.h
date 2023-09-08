#ifndef REVERSELINE_SETTING_H
#define REVERSELINE_SETTING_H

#include <QDialog>
#include "reverselinewidget.h"
namespace Ui {
class ReverseLine_Setting;
}

class ReverseLine_Setting : public QDialog
{
    Q_OBJECT

public:
    explicit ReverseLine_Setting(QWidget *parent = 0);
    ~ReverseLine_Setting();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::ReverseLine_Setting *ui;
    void FormInCenter();
    reverseLineWidget* reverLinewidget;
signals:
    void reverseLine_repaint();
};

#endif // REVERSELINE_SETTING_H
