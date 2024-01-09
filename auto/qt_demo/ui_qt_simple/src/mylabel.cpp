#include "mylabel.h"

myLabel::myLabel(QWidget * parent) : QLabel(parent)
{ }

void myLabel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked();
}
