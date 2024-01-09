#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include <QFontDatabase>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDebug>
frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);
    show_title();
    FormInCenter();
    this->mousePressed = false;
    //this->setWindowOpacity(1.0);
   // setAttribute(Qt::WA_TranslucentBackground, false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));

}

frmMessageBox::~frmMessageBox()
{
    qDebug()<<"~frmMessageBox is called!!!";
    delete ui;
}
void frmMessageBox::show_title()
{
    int fontId = QFontDatabase::addApplicationFont(":/image/font/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    iconFont.setPointSize(10);
    ui->btnMenu_Close->setFont(iconFont);
    ui->btnMenu_Close->setText(QChar(0xf00d));
    iconFont.setPointSize(12);
    ui->lab_Ico->setFont(iconFont);
    ui->lab_Ico->setText( QChar(0xf015));
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
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/icon/info.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("提示");
    } else if (type == 1) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/icon/question.png);");
        ui->lab_Title->setText("询问");
    } else if (type == 2) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/icon/error.png);");
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

void frmMessageBox::on_btnMenu_Close_clicked()
{
    this->close();
}
