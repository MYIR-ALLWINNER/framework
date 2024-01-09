#ifndef SLAVE_VIDEOWIDGET_H
#define SLAVE_VIDEOWIDGET_H

#include <QDialog>

namespace Ui {
class slave_VideoWidget;
}

class slave_VideoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit slave_VideoWidget(QWidget *parent = 0);
    ~slave_VideoWidget();

//public slots:
//    void deal_picture_views_signal();
private:
    Ui::slave_VideoWidget *ui;
};

#endif // SLAVE_VIDEOWIDGET_H
