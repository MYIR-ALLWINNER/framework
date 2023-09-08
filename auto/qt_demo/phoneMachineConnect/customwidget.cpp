#include "customwidget.h"
#include <QStyleOption>
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}
