#ifndef FLOATBUTTON_H
#define FLOATBUTTON_H

#include <QWidget>

class FloatButton : public QWidget
{
    Q_OBJECT
public:
    explicit FloatButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // FLOATBUTTON_H
