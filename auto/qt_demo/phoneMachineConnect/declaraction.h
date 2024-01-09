#ifndef DECLARACTION_H
#define DECLARACTION_H

#include <QWidget>
#include "customwidget.h"

namespace Ui {
class Declaraction;
}

class Declaraction : public CustomWidget
{
    Q_OBJECT

public:
    explicit Declaraction(QWidget *parent = 0);
    ~Declaraction();

private slots:
    void on_btnBack_clicked();

private:
    Ui::Declaraction *ui;
};

#endif // DECLARACTION_H
