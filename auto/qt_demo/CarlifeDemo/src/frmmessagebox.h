#ifndef FRMMESSAGEBOX_H
#define FRMMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class frmMessageBox;
}

class frmMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmMessageBox(QWidget *parent = 0);
    ~frmMessageBox();

    void SetMessage(const QString &msg, int type);
//    void close();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void show_title();
private slots:
    void on_btnOk_clicked();

    void on_btnMenu_Close_clicked();

private:
    Ui::frmMessageBox *ui;

    QPoint mousePoint;
    bool mousePressed;
    void FormInCenter();
};

#endif // FRMMESSAGEBOX_H
