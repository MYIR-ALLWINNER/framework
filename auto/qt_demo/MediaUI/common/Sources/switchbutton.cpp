/*!
 * @file switchbutton.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "common/Header/switchbutton.h"


#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
SwitchButton::SwitchButton(QWidget *parent)
    : QWidget(parent),
      m_nHeight(36),
      m_bChecked(false),
      m_radius(5.0),
      m_nMargin(0),
      m_CheckedColor(0, 0, 150),
      m_thumbColorOn(127,170,255),
      m_thumbColorOff(Qt::white),
      m_disableColor(190, 190, 190),
      m_backgroundColor(Qt::black)
{
    setCursor(Qt::PointingHandCursor);

    connect(&m_timer,SIGNAL(timeout()),this, SLOT(onTimeout()));
}
/*!
 * @function
 * @brief des this func is paint the switch button
 */
void SwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    QColor background;
    QColor thumbColor;
    qreal dOpacity;
    if(isEnabled()){//switchbutton is enabled
        if(m_bChecked){//switchbutton is open
            background = m_CheckedColor;
            thumbColor = m_thumbColorOn;
            dOpacity = 0.6;
        } else {   //switchbutton is close
            background = m_backgroundColor;
            thumbColor = m_thumbColorOff;
            dOpacity = 0.8;
        }
    } else {//switchbutton is disable
        background = m_backgroundColor;
        dOpacity = 0.26;
        thumbColor = m_disableColor;
    }
    //paint the big rect
    painter.setBrush(background);
    painter.setOpacity(dOpacity);
    path.addRoundedRect(QRectF(m_nMargin,m_nMargin,width() - 2 * m_nMargin, \
                               height() - 2 * m_nMargin), m_radius, m_radius);
    painter.drawPath(path.simplified());

    //paint the small rect
    painter.setBrush(thumbColor);
    painter.setOpacity(1.0);
    painter.drawRoundedRect(QRectF(m_nX - (m_nHeight / 2),m_nY - (m_nHeight / 2),\
                               height(), height()),m_radius,m_radius);// ellipse center poiont and x & y radius
    //painter.drawEllipse(QRectF(72,0,42,42));// ellipse center poiont and x & y radius
}

void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if (event->buttons() & Qt::LeftButton) {
            event->accept();
        } else {
            event->ignore();
        }
    }
}

void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if ((event->type() == QMouseEvent::MouseButtonRelease) && \
                (event->button() == Qt::LeftButton)) {
            event->accept();
            m_bChecked = !m_bChecked;
            emit toggled(m_bChecked);
            m_timer.start(10);
        } else {
            event->ignore();
        }
    }
}

void SwitchButton::resizeEvent(QResizeEvent *event)
{
    m_nX = m_nHeight / 2;
    m_nY = m_nHeight / 2;
    QWidget::resizeEvent(event);
}

QSize SwitchButton::sizeHint() const
{
    return minimumSizeHint();
}

QSize SwitchButton::minimumSizeHint() const
{
    return QSize(2 * (m_nHeight + m_nMargin), m_nHeight + 2 * m_nMargin);
}

void SwitchButton::onTimeout()
{
    if (m_bChecked) {
        m_nX += 1;
        if (m_nX >= width() - m_nHeight / 2)
            m_timer.stop();
    } else {
        m_nX -= 1;
        if (m_nX <= m_nHeight / 2)
            m_timer.stop();
    }
    update();
}

bool SwitchButton::isToggled() const
{
    return m_bChecked;
}

void SwitchButton::setToggled(bool checked)
{
    m_bChecked = checked;
    m_timer.start(10);
}

void SwitchButton::setBackgroundColor(QColor color)
{
    m_backgroundColor = color;
}

void SwitchButton::setCheckedColor(QColor color)
{
    m_CheckedColor = color;
}

void SwitchButton::setDisabledColor(QColor color)
{
    m_disableColor = color;
}
