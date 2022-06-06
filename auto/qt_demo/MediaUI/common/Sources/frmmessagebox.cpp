/*!
 * @class frmMessageBox
 * @brief des
 * this is class which is a information widget
 * this widget provide, three types, by func frmMessageBox::SetMessage:
 * (1)information dialog
 * (2)question dialog
 * (3)error dialog
 * @author lee
 */
#include "common/Header/frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include <QFontDatabase>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);
    show_title();//title settting
    FormInCenter();//make this widget is center in desktop
    this->mousePressed = false;//for widget drag move
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);//this widget will delete when close

    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));

}

frmMessageBox::~frmMessageBox()
{
    delete ui;
}
void frmMessageBox::show_title()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    iconFont.setPointSize(10);
    ui->btnMenu_Close->setFont(iconFont);
    ui->btnMenu_Close->setText(QChar(0xf00d));
    iconFont.setPointSize(12);
    ui->lab_Ico->setFont(iconFont);
    ui->lab_Ico->setText(QChar(0xf015));
    ui->lab_Title->setFont(iconFont);
}

void frmMessageBox::FormInCenter()
{
    int frmX = this->width();
    int frmY = this->height();
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    this->move(movePoint);
}
void frmMessageBox::SetMessage(const QString &msg, int type)
{
    if (type == 0) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/messageBoxIcons/info.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("提示");
    } else if (type == 1) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/messageBoxIcons/question.png);");
        ui->lab_Title->setText("询问");
    } else if (type == 2) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/messageBoxIcons/error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("错误");
    }

    ui->labInfo->setText(msg);
}

void frmMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}

void frmMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
