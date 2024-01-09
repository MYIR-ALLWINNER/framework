/*!
 * @file graphicsview.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "graphicsview.h"
#include <QDebug>
#include <QTouchEvent>

graphicsView::graphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
}

graphicsView::~graphicsView()
{

}

bool graphicsView::event(QEvent* event)
{
    switch(event->type()){
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        qDebug()<<"--lee, get touch event";
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        return true;
    }
    case QEvent::KeyPress:
        qDebug()<<"--lee, get keypress event";
        break;
    case QEvent::Hide:
        qDebug()<<"---lee, get hide event";
        break;
    case QEvent::MouseButtonPress:
        qDebug()<<"--lee, get keypress event";
        break;
    default:
        break;
    }
    return QGraphicsView::event(event);
}
#if 0
void graphicsView::mousePressEvent(QMouseEvent* event)
{
     qDebug()<<"--lee,graphicsView get QMouseEvent event";

}
#endif
