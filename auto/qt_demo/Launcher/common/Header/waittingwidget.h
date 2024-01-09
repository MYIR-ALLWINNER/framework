/*!
 * @file waittingwidget.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef WAITTINGWIDGET_H
#define WAITTINGWIDGET_H

#include <QWidget>
#include <QRect>
#include <QMovie>
namespace Ui {
class WaittingWidget;
}

class WaittingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaittingWidget(QWidget *parent = 0);
    ~WaittingWidget();
    void user_setGeometry(const QRect&);
    void startMovie();
public slots:
    void onStopMovie();
private slots:

private:
    Ui::WaittingWidget *ui;
    QMovie* m_pMovie;
};

#endif // WAITTINGWIDGET_H
