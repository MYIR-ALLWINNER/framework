#include "front_adas_setting.h"
#include "ui_front_adas_setting.h"
#include "adas.h"
#include "ui_adas.h"
#include <QDesktopWidget>
#include "settings.h"
extern Settings* pStatic_settings;
front_ADAS_setting::front_ADAS_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::front_ADAS_setting)
{
    ui->setupUi(this);

    this->horizontal_values=0;
    this->model=0;
    this->vertical_values=0;
    FormInCenter();
    ui->VerticelLine->setLineWidth(1);
    ui->HorizontalLine->setLineWidth(1);
    ui->left_right_Slider->setRange(0,80);
    ui->high_low_Slider->setRange(0,60);
//    ui->HorizontalLine->setStyleSheet(tr("background-color:red"));
    connect(ui->left_right_Slider,SIGNAL(valueChanged(int)),this,SLOT(change_line_value(int)));
    connect(ui->high_low_Slider,SIGNAL(valueChanged(int)),this,SLOT(change_line_value(int)));
    ui->high_low_Slider->setStyleSheet("QSlider::groove:vertical{background: #cbcbcb;width: 6px;border-radius: 1px;padding-left:-1px;padding-right:-1px;padding-top:-1px;padding-bottom:-1px; }"
                                   "QSlider::sub-page:vertical{background: #cbcbcb;border-radius: 2px;}"
                                   "QSlider::add-page:vertical{background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #439cf4, stop:1 #439cf4);\
                                   background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\
                                   width: 10px;border-radius: 2px;}"
                                   "QSlider::handle:vertical{border-image: url(:/icon/circle-white.png);margin: -2px -7px -2px -7px; height: 17px;}"
                                    "QSlider{border-color: #cbcbcb;}"  );
//    ui->left_right_Slider->setStyleSheet("QSlider::groove:horizontal{border: 1px solid #999999;height: 1px;margin: 0px 0;left: 5px; right: 5px; }"
//                           "QSlider::sub-page:horizontal{background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);"
//                           "QSlider::add-page:horizontal{background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);"
//                           "QSlider::handle:horizontal{border: 0px ;border-image: url(:/icon/circle-white.png);margin: -7px -7px -7px -7px; width: 15px;}"
//                            "QSlider{border-color: #cbcbcb;}"  );
    ui->left_right_Slider->setStyleSheet("QSlider::groove:horizontal{background: #cbcbcb;height: 6px;border-radius: 1px;padding-left:-1px;padding-right:-1px;padding-top:-1px;padding-bottom:-1px; }"
                                   "QSlider::add-page:horizontal{background: #cbcbcb;border-radius: 2px;}"
                                   "QSlider::sub-page:horizontal{background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);\
                                   background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\
                                   height: 10px;border-radius: 2px;}"
                                   "QSlider::handle:horizontal{border-image: url(:/icon/circle-white.png);margin: -2px -7px -2px -7px; width: 17px;}"
                                    "QSlider{border-color: #cbcbcb;}"  );
}
    void front_ADAS_setting::FormInCenter()
    {
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        this->resize(deskWidth*3/4,deskHeight*3/4);
        QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
        this->move(movePoint);
    }
front_ADAS_setting::~front_ADAS_setting()
{
    delete ui;
}
void front_ADAS_setting::on_returnButton_clicked()
{
    this->close();
    pStatic_settings->setHidden(false);

}
void front_ADAS_setting::on_nextButton_clicked()
{

    this->close();
    pStatic_settings->setHidden(false);
}
void front_ADAS_setting::change_line_value(int value)
{
    qDebug()<<"the values is:"<<value;
    QObject* sender=QObject::sender();
    if(sender==ui->left_right_Slider){

        this->horizontal_values=3*value;
        ui->VerticelLine->move(10+this->horizontal_values,40);
        this->model=2;
//        update();
    }else if(sender==ui->high_low_Slider){

        this->vertical_values=3*value;
        this->model=1;
        ui->HorizontalLine->move(0,260-this->vertical_values);
//        update();
    }else{
        qDebug()<<"no signal";
    }

}
