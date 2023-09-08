#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QDate>
#include "about.h"
#include "preview.h"
#include "adas.h"
#include "reverseline.h"
#include "timesetting.h"
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    void FormInCenter();
public slots:

private slots:
    void on_returnButton_clicked();

    void on_previewButton_clicked();

    void on_AdasButton_clicked();

    void on_reverseLineButton_clicked();

    void on_timeSetButton_clicked();

    void on_aboutButton_clicked();

private:
    About *abouts;
    Preview *previews;
    ADAS *adass;
    ReverseLine *reverselines;
    TimeSetting *timesettings;
private:
    Ui::Settings *ui;

};



class CustomTabStyle : public QProxyStyle
{
public:
    explicit CustomTabStyle(int x,int y):width(x),height(y){}
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = this->width;
            s.rheight() = this->height;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if(const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0xf8fcff);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
private:
    int width;
    int height;
};

#endif // SETTINGS_H
