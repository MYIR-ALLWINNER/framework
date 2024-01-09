/*!
 * @file carlifewindow.h
 * Copyright (c) 2018
 * @brief this is a demo for carlife in smart car
 * detailed  This demo program mainly provides visual mobile
 *           interconnect operations
 *
 * @date 2018
 * @author lee
 */
#ifndef CARLIFEWINDOW_H
#define CARLIFEWINDOW_H

#include <QWidget>
#include <QThread>

#include "closebutton.h"
#include "scene.h"
#define TEST 1
#define LCD_WIDTH 1024
#define LCD_HEIGHT 600
namespace Ui {
class CarlifeWindow;
class WorkerThread;
}

/*!
 * @WorkerThread
 * @brief: for carlife data show
 */
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = 0);
    ~WorkerThread();
protected:
    virtual void run();
signals:
    void connectSuccess();
    void connectBreak();
private:
    int m_curConnectStatus;//if 1 connected  else unconnected
    int m_oldConnectStatus;//if 1 connected  else unconnected
};


class CarlifeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CarlifeWindow(QWidget *parent = 0);
    ~CarlifeWindow();
    void test();
private slots:
    void on_closeButton_clicked();

    void on_AndroidButton_clicked();

    void on_IosButton_clicked();

    void on_UsbButton_clicked();

    void on_WifiButton_clicked();

    void on_sureButton_clicked();

    void on_connectSuccess();

    void on_connectBreak();

    void on_pushButton_clicked();

    void on_reverseControl_Down(int, int);

    void on_reverseControl_Move(int, int);

    void on_reverseControl_Up(int, int);

private:
    Ui::CarlifeWindow *ui;
    int m_platform;//android is 0, ios is 1, none is 3
    int m_connectWay;//usb is 0,ios is 1, none is 3
    int m_carlifeStatus;//make QUBE know app status on phone: 1 is connected;
    WorkerThread* workerthread;
    closeButton* clsButton;
    Scene* m_scene;//for get touch event
    QMovie *pMovie;
};

#endif // CARLIFEWINDOW_H
