/*!
 * @file switchbutton.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QTimer>
class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);
    //return status -- open: true  close: false
    bool isToggled() const;
    //set switch status
    void setToggled(bool checked);
    //set background color
    void setBackgroundColor(QColor color);
    //set checked color
    void setCheckedColor(QColor color);
    //set disable color
    void setDisabledColor(QColor color);
protected:
    //paintevent
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    //mouseEvents
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //size change event
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    //default size
    QSize sizeHint() const Q_DECL_OVERRIDE;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    //status change signal
    void toggled(bool checked);

public slots:
    //for switch animation
    void onTimeout();
private:
    bool              m_bChecked;   //checked or not
    QColor            m_backgroundColor; //background color
    QColor            m_CheckedColor;    //checed color
    QColor            m_disableColor;    //disabled color
    QColor            m_thumbColorOn;      //
    QColor            m_thumbColorOff;
    qreal             m_radius;          //
    qreal             m_nX;              // x
    qreal             m_nY;              // y
    qint16            m_nHeight;         //height
    qint16            m_nMargin;         //margin
    QTimer            m_timer;           //timer
};

#endif // SWITCHBUTTON_H
