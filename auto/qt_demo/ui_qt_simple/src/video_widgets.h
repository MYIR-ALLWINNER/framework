#ifndef VIDEO_WIDGETS_H
#define VIDEO_WIDGETS_H


#include <QVideoWidget>
#include <QKeyEvent>

class video_widgets : public QVideoWidget
{
    Q_OBJECT

public:
    video_widgets(QWidget *parent = 0);

protected:
//    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};



#endif // VIDEO_WIDGETS_H
