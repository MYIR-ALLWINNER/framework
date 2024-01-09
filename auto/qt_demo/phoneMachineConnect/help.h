#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include "customwidget.h"
#include "declaraction.h"

namespace Ui {
class Help;
}

class Help : public CustomWidget
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

private slots:
    void on_btnBack_clicked();

    void on_pushButton_clicked();

private:
    Ui::Help *ui;
    Declaraction *declaraction;
};

#endif // HELP_H
