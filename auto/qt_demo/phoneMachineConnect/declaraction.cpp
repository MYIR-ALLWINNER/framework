#include "declaraction.h"
#include "ui_declaraction.h"
#include <QScrollBar>
#include <QScroller>

Declaraction::Declaraction(QWidget *parent) :
    CustomWidget(parent),
    ui(new Ui::Declaraction)
{
    ui->setupUi(this);
    ui->textBrowser->setProperty("noinput",true);
    this->setObjectName("declaraction");
    this->setStyleSheet("QWidget#declaraction {border-image:url(:/pmc_image/bg.png);}");

    ui->textBrowser->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {margin: 13px 0px 23px 0px;background-color: rgb(255, 255, 255, 50); width: 5px;}\
                                   QScrollBar::handle:vertical {background-color: #FFbc28; width: 15px; height:20px;}\
                                   QScrollBar::add-page:vertical {background-color: transparent; }\
                                   QScrollBar::sub-page:vertical {background-color: transparent; }\
                                   QScrollBar::sub-line:vertical {subcontrol-origin: margin; border: 1px solid transparent; height:0px}\
                                   QScrollBar::up-arrow:vertical { subcontrol-origin: margin; background-color: blue; height:0px}\
                                   QScrollBar::add-line:vertical {subcontrol-origin: margin; border: 1px solid transparent; height:6px}");
//    ui->textBrowser->setStyleSheet("font: 10 14pt \"Ubuntu\";");

   QScroller* scroller = QScroller::scroller(ui->textBrowser);
   scroller->grabGesture(ui->textBrowser,QScroller::LeftMouseButtonGesture);
    this->setObjectName("declaraction");
    this->setStyleSheet("QWidget#declaraction {border-image:url(:/pmc_image/bg.png);}");
}

Declaraction::~Declaraction()
{
    delete ui;
}

void Declaraction::on_btnBack_clicked()
{
    this->close();
}
