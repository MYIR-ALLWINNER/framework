#include "video_widgets.h"

#include <QKeyEvent>
#include <QMouseEvent>

video_widgets::video_widgets(QWidget *parent)
    : QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

//void video_widgets::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Escape && isFullScreen())
//    {
//        setFullScreen(false);
//        event->accept();
//    }
//    else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt)
//    {
//        setFullScreen(!isFullScreen());
//        event->accept();
//    }
//    else
//    {
//        QVideoWidget::keyPressEvent(event);
//    }
//}

void video_widgets::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());
    event->accept();
}

void video_widgets::mousePressEvent(QMouseEvent *event)
{
    QVideoWidget::mousePressEvent(event);
}
