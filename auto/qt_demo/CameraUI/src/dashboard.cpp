#include "dashboard.h"
#include "ui_dashboard.h"
#include <QDesktopWidget>
dashBoard::dashBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dashBoard)
{
    ui->setupUi(this);
//    int w,h;
//    w=(1024-this->width())/2;
//    h=(600-this->height())/2;
//    this->mapToParent(QPoint(w,h));
    FormInCenter();
    myspeed=new mySpeed();
    ui->scrollArea->setWidget(myspeed);
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(on_returnButton_clicked()));
}
void dashBoard::FormInCenter()
{
    int frmX = this->width();
    int frmY = this->height();
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    this->move(movePoint);
}
dashBoard::~dashBoard()
{
    delete ui;
}
void dashBoard::on_returnButton_clicked()
{
    this->close();
}
