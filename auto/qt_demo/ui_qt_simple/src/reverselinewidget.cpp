#include "reverselinewidget.h"
#include <QPainter>
#include <QTransform>
//extern qreal rotate_angle;
extern int rotate_angle;
reverseLineWidget::reverseLineWidget(QWidget *parent) : QWidget(parent)
{
//    this->setMaximumSize(1000,430);
//    this->setMinimumSize(1000,430);
}
void reverseLineWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


    QPainter painter(this);

    painter.setWorldTransform(QTransform().translate(0,430).rotate(rotate_angle,Qt::XAxis).translate(0,-430));

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor(231,255,15),5));

//    painter.rotate(20,Qt::XAxis);
//    painter.shear(0.5,0);
    static const QPointF point[4]={
        QPointF(350,10),
        QPointF(50,430),
        QPointF(950,430),
        QPointF(650,10)
    };

    painter.drawPolygon(point,4);
    painter.setPen(QPen(QColor(255,12,48),5));
    painter.drawLine(QPointF(250,150),QPointF(750,150));
//    painter.shear(0.5,0);

    painter.setPen(QPen(QColor(255,12,48),5));
    painter.drawLine(QPointF(150,290),QPointF(850,290));

//    painter.shear(0.5,0);
    painter.setPen(QPen(QColor(231,255,15),3));
    painter.drawText(QPoint(660,10),QString("3m"));

//    painter.shear(0.5,0);
    painter.setPen(QPen(QColor(231,255,15),3));
    painter.drawText(QPoint(760,150),QString("1.5m"));

//    painter.shear(0.5,0);
    painter.setPen(QPen(QColor(231,255,15),3));
    painter.drawText(QPoint(860,290),QString("0.5m"));



}
