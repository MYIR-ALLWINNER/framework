#ifndef MYLABEL_H
#define MYLABEL_H
#include <QWidget>
#include <QLabel>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget * parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void clicked(void);
};

#endif // MYLABEL_H
