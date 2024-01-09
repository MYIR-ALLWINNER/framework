/*!
 * @file scene.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef SCENE_H
#define SCENE_H

#include "graphicsview.h"
#include <QDialog>
#include <QEvent>
#include <QGraphicsView>
#include <QQuickWidget>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>

//#define USE_GRAPHICSVIEW 1
#define USE_MOUSEEVENT 1
//#define USE_QML 1
namespace Ui {
class Scene;
}
class Scene : public QDialog
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = 0);
    ~Scene();
protected:
    bool event(QEvent* event);
#ifdef USE_MOUSEEVENT
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
#endif
private:
    Ui::Scene *ui;
#ifdef USE_GRAPHICSVIEW
    graphicsView* graphicsview;
#endif
#ifdef USE_QML
    QQuickWidget *view;
#endif
    int m_x;
    int m_y;
signals:
    void reverseControl_Down(int pos_x,int pos_y);
    void reverseControl_Up(int pos_x,int pos_y);
    void reverseControl_Move(int pos_x,int pos_y);
};

#endif // SCENE_H
