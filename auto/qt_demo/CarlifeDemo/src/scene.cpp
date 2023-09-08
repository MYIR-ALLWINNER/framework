/*!
 * @file scene.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "scene.h"
#include "ui_scene.h"

#include <QTouchEvent>
#include <QDebug>

Scene::Scene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scene)
{
    ui->setupUi(this);
#ifdef USE_GRAPHICSVIEW
    graphicsview = new graphicsView(this);
    graphicsview->setMaximumSize(QSize(1024,300));
    graphicsview->setMinimumSize(QSize(1024,300));
    graphicsview->setStyleSheet("background-color:rgba(60,60,60,255)");
    graphicsview->mapToParent(QPoint(0,0));
#endif
#ifdef USE_QML
    view = new QQuickWidget(this);
    view->resize(this->width(),this->height());
    view->setSource(QUrl(QStringLiteral("qrc:/multiTouch.qml")));
    view->show();

    //QObject::connect(view->engine(), SIGNAL(quit()), view, SLOT(close()));
#endif
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_AcceptTouchEvents,true);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, true);
}

Scene::~Scene()
{
    delete ui;
#ifdef USE_GRAPHICSVIEW
    delete graphicsview;
#endif
#ifdef USE_QML
    delete view;
#endif
}

bool Scene::event(QEvent* event)
{
    switch(event->type()){
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        qDebug()<<"--lee, scene get touch event";
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        event->accept();
        return true;
    }

    case QEvent::KeyPress:
        qDebug()<<"--lee, get keypress event";
        break;
    case QEvent::Hide:
        qDebug()<<"---lee, get hide event";
        break;
    default:
        break;
    }
    return QDialog::event(event);
}
#ifdef USE_MOUSEEVENT
void Scene::mousePressEvent(QMouseEvent* event)
{
     qDebug()<<"--lee, get mousePressEvent event";
     m_x = event->globalX();
     m_y = event->globalY();
     qDebug()<<QString("touch positon:(%1,%2)").arg(m_x).arg(m_y);
     emit reverseControl_Down(m_x, m_y);
}

void Scene::mouseMoveEvent(QMouseEvent* event)
{
    qDebug()<<"--lee, get mouseMoveEvent event";
    m_x = event->globalX();
    m_y = event->globalY();
    qDebug()<<QString("re positon:(%1,%2)").arg(m_x).arg(m_y);
    emit reverseControl_Move(m_x, m_y);
}

void Scene::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug()<<"--lee, get mouseReleaseEvent event";
    m_x = event->globalX();
    m_y = event->globalY();
    qDebug()<<QString("re positon:(%1,%2)").arg(m_x).arg(m_y);
    emit reverseControl_Up(m_x, m_y);
}
#endif
