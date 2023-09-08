#ifndef TIMESETTING_H
#define TIMESETTING_H

#include <QDialog>
#include <QObject>
#include <QDate>
#include <QTime>
namespace Ui {
class TimeSetting;
}
//设定主屏幕时间
//class results{
//public:
//    QDate date_sets;
//    QTime time_sets;
//    QString testString;
//};
class TimeSetting : public QDialog
{
    Q_OBJECT

public:
    friend class results;
    explicit TimeSetting(QWidget *parent = 0);
    ~TimeSetting();
    void setDateAndTime();
private:
    Ui::TimeSetting *ui;
//    void accept();
public slots:
    void setDatesTimes();
//signals:
//    void send_data_to_main(results);
private slots:
    void on_setButton_clicked();
};

#endif // TIMESETTING_H
