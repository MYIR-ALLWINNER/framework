#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QPainter>
#include <QColor>
#include <QPalette>
#include "myspeed.h"

namespace Ui {
class dashBoard;
}

class dashBoard : public QDialog
{
    Q_OBJECT

public:
    explicit dashBoard(QWidget *parent = 0);
    ~dashBoard();
public slots:
    void on_returnButton_clicked();
private:
    Ui::dashBoard *ui;
    mySpeed *myspeed;
    void FormInCenter();
};

#endif // DASHBOARD_H
