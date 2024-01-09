/*!
 * @file graphicsview.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QEvent>

class graphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit graphicsView(QWidget *parent = 0);
    ~graphicsView();
protected:
    bool event(QEvent* event);
#if 0
    void mousePressEvent(QMouseEvent* event);
#endif
};

#endif // GRAPHICSVIEW_H
