#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include "customwidget.h"

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // CUSTOMWIDGET_H
