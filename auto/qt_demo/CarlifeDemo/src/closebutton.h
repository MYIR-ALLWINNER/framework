/*!
 * @file closebutton.h
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QDialog>

namespace Ui {
class closeButton;
}

class closeButton : public QDialog
{
    Q_OBJECT

public:
    explicit closeButton(QWidget *parent = 0);
    ~closeButton();
    void adaptPosition();
private slots:
	void on_pushButton_clicked();
signals:
    void forceBreak();
private:
    Ui::closeButton *ui;

};

#endif // CLOSEBUTTON_H
