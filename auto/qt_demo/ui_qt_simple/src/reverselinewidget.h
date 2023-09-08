#ifndef REVERSELINEWIDGET_H
#define REVERSELINEWIDGET_H

#include <QWidget>

class reverseLineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit reverseLineWidget(QWidget *parent=0);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // REVERSELINEWIDGET_H
